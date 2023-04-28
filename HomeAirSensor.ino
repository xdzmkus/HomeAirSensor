#define SERIAL_DEBUG
#include <SerialDebug.h>

#include "src/WiFiMQTT_Sensor.h"
WiFiMQTT_Sensor wifiMqtt;

#define BTN_PIN D0

#include <ArduinoDebounceButton.h>
ArduinoDebounceButton btn(BTN_PIN, BUTTON_CONNECTED::VCC, BUTTON_NORMAL::OPEN);

// MHZ-19 - CO2 sensor
#define ANALOGPIN A0
#define RX_PIN D6                                          // D6 - Rx pin which the MHZ19 Tx pin is attached to
#define TX_PIN D8                                          // D8 - Tx pin which the MHZ19 Rx pin is attached to
#define BAUDRATE 9600                                      // Native to the sensor (do not change)

#include <MHZ19.h>
#include <SoftwareSerial.h>
MHZ19 myMHZ19;
SoftwareSerial mySerial(RX_PIN, TX_PIN);
int CO2 = 0;

// I2C modules:
// D1 - SCL; 
// D2 - SDA

// Tiny RTC I2C Module
#include <RTClib.h>
RTC_DS1307 rtc;
DateTime displayedTime;

#define SEALEVELPRESSURE_HPA (1013.25)

// BME280 - humidity, temperature & pressure sensor 
#include <Adafruit_BME280.h>

Adafruit_BME280 sensor;

float temperature = 0;
float humidity = 0;
float pressure = 0;
float altitude = 0;

#include <Ticker.h>
Ticker tickerSensor;
Ticker tickerCO2;
Ticker tickerRTC;
Ticker tickerMQTT;

// Interrupts ---------------------------/

#define SENSOR_CHECK_INTERVAL	5.0F    // 5 seconds
#define CO2_CHECK_INTERVAL		60.0F   // 60 seconds
#define RTC_CHECK_INTERVAL		1000    // 500 ms
#define MQTT_PUBLISH_INTERVAL	30.0F   // 30 seconds

volatile bool checkSensor = false;
volatile bool checkCO2 = false;
volatile bool checkRTC = false;
volatile bool doPublish = false;

// *** TFT-1.4 *** 128 x 128 ***//

static const uint16_t screenWidth = 128;
static const uint16_t screenHeight = 128;

#include <Arduino_GFX_Library.h>

#define TFT_MISO GFX_NOT_DEFINED
#define TFT_MOSI D7
#define TFT_SCLK D5
#define TFT_CS   D4   // Chip select control pin
#define TFT_DC   D3   // Data Command control pin
#define TFT_RST  GFX_NOT_DEFINED // Reset pin (could connect to RST pin)

const uint8_t rotation = 0;

/* More data bus class: https://github.com/moononournation/Arduino_GFX/wiki/Data-Bus-Class */
Arduino_DataBus* bus = new Arduino_ESP8266SPI(TFT_DC /* DC */, TFT_CS /* CS */);

/* More display class: https://github.com/moononournation/Arduino_GFX/wiki/Display-Class */
Arduino_GFX* gfx = new Arduino_ST7735(bus, TFT_RST /* RST */, rotation /* rotation */, false /* IPS */, screenWidth /* width */, screenHeight /* height */, 2 /* col offset 1 */, 3 /* row offset 1 */, 2 /* col offset 2 */, 1 /* row offset 2 */);

#include <lvgl.h>

static lv_disp_draw_buf_t draw_buf;
static lv_color_t* disp_draw_buf;

#include "src/tft.h"

/* Display flushing */
static void tft_disp_flush(lv_disp_drv_t* disp, const lv_area_t* area, lv_color_t* color_p)
{
	uint32_t w = (area->x2 - area->x1 + 1);
	uint32_t h = (area->y2 - area->y1 + 1);

#if (LV_COLOR_16_SWAP != 0)
	gfx->draw16bitBeRGBBitmap(area->x1, area->y1, (uint16_t*)&color_p->full, w, h);
#else
	gfx->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t*)&color_p->full, w, h);
#endif

	lv_disp_flush_ready(disp);
}

void tft_init()
{
	// TFT init
	gfx->begin();
	gfx->fillScreen(WHITE);

	lv_init();

#ifdef ESP32
	disp_draw_buf = (lv_color_t*)heap_caps_malloc(sizeof(lv_color_t) * screenWidth * screenHeight / 10, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
#else
	disp_draw_buf = (lv_color_t*)malloc(sizeof(lv_color_t) * screenWidth * 5);
#endif
	if (!disp_draw_buf)
	{
		Serial.println("LVGL disp_draw_buf allocate failed!");
		ESP.restart();
	}

	lv_disp_draw_buf_init(&draw_buf, disp_draw_buf, NULL, screenWidth * 5);

	/*Initialize the display*/
	static lv_disp_drv_t disp_drv;
	lv_disp_drv_init(&disp_drv);
	/*Change the following line to your display resolution*/
	disp_drv.hor_res = screenWidth;
	disp_drv.ver_res = screenHeight;
	disp_drv.flush_cb = tft_disp_flush;
	disp_drv.draw_buf = &draw_buf;
	lv_disp_drv_register(&disp_drv);
}

void callback_checkSensor()
{
	checkSensor = true;
}

void callback_checkCO2()
{
	checkCO2 = true;
}

void callback_checkRTC()
{
	checkRTC = true;
}

void callback_publishMQTT()
{
	doPublish = true;
}

void handleButtonEvent(const DebounceButton* button, BUTTON_EVENT eventType)
{
	switch (eventType)
	{
	case BUTTON_EVENT::Clicked:
		SerialDebug::log(LOG_LEVEL::DEBUG, F("Clicked"));
		SerialDebug::log(LOG_LEVEL::INFO, F("Publish state..."));
		doPublish = true;
		break;
	case BUTTON_EVENT::LongPressed:
		SerialDebug::log(LOG_LEVEL::DEBUG, F("LongPressed"));
		SerialDebug::log(LOG_LEVEL::WARN, F("Rebooting..."));
		ESP.restart();
		break;
	default:
		break;
	}
}

// -------------------------------------------------------------------------------------------------------------
uint32_t getNTPTime()
{
	uint8_t attemps = 5;

	unsigned int localPort = 2390;  // local port to listen for UDP packets

	/* Don't hardwire the IP address or we won't get the benefits of the pool.
		Lookup the IP address for the host name instead */

	IPAddress timeServerIP;  // time.nist.gov NTP server address
	const char* ntpServerName = "time.nist.gov";

	const int NTP_PACKET_SIZE = 48;  // NTP time stamp is in the first 48 bytes of the message

	byte packetBuffer[NTP_PACKET_SIZE];  // buffer to hold incoming and outgoing packets

	// A UDP instance to let us send and receive packets over UDP
	WiFiUDP udp;

	udp.begin(localPort);

	do
	{
		// get a random server from the pool
		WiFi.hostByName(ntpServerName, timeServerIP);

		// set all bytes in the buffer to 0
		memset(packetBuffer, 0, NTP_PACKET_SIZE);

		// Initialize values needed to form NTP request
		// (see URL above for details on the packets)
		packetBuffer[0] = 0b11100011;  // LI, Version, Mode
		packetBuffer[1] = 0;           // Stratum, or type of clock
		packetBuffer[2] = 6;           // Polling Interval
		packetBuffer[3] = 0xEC;        // Peer Clock Precision
		// 8 bytes of zero for Root Delay & Root Dispersion
		packetBuffer[12] = 49;
		packetBuffer[13] = 0x4E;
		packetBuffer[14] = 49;
		packetBuffer[15] = 52;

		// all NTP fields have been given values, now
		// you can send a packet requesting a timestamp:
		udp.beginPacket(timeServerIP, 123);  // NTP requests are to port 123
		udp.write(packetBuffer, NTP_PACKET_SIZE);
		udp.endPacket();

		SerialDebug::log(LOG_LEVEL::DEBUG, F("Send NTP request"));

		delay(1000);
	} while (!udp.parsePacket() && --attemps > 0);

	if (attemps == 0) return 0;

	// We've received a packet, read the data from it
	udp.read(packetBuffer, NTP_PACKET_SIZE);  // read the packet into the buffer

	// the timestamp starts at byte 40 of the received packet and is four bytes,
	//  or two words, long. First, esxtract the two words:

	uint32_t highWord = word(packetBuffer[40], packetBuffer[41]);
	uint32_t lowWord = word(packetBuffer[42], packetBuffer[43]);
	// combine the four bytes (two words) into a long integer
	// this is NTP time (seconds since Jan 1 1900):
	uint32_t secsSince1900 = highWord << 16 | lowWord;
	SerialDebug::log(LOG_LEVEL::DEBUG, String(F("Seconds since Jan 1 1900 = ")) + secsSince1900);

	// now convert NTP time into everyday time
	// Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
	const uint32_t seventyYears = 2208988800UL;
	// subtract seventy years:
	uint32_t epoch = secsSince1900 - seventyYears + 3 * 3600; // UTC+3

	return epoch;
}


bool setup_RTC()
{
	SerialDebug::log(LOG_LEVEL::INFO, F("RTC init..."));

	if (!rtc.begin())
	{
		SerialDebug::log(LOG_LEVEL::ERROR, F("Couldn't find RTC"));
		return false;
	}

	uint32_t unixtime = getNTPTime();

	SerialDebug::log(LOG_LEVEL::DEBUG, String(F("Unix time since Jan 1 1970 = ")) + unixtime);

	if (unixtime != 0)
	{
		rtc.adjust(unixtime);
	}

	return true;
}

bool setup_Sensor()
{
	SerialDebug::log(LOG_LEVEL::INFO, F("BME280 init..."));

	unsigned status = sensor.begin(0x76);

	if (!status)
	{
		SerialDebug::log(LOG_LEVEL::ERROR, F("Could not find a valid sensor, check wiring, address, sensor ID!"));
		SerialDebug::log(LOG_LEVEL::INFO, String(F("SensorID was: 0x")) + String(sensor.sensorID(), 16));
		SerialDebug::log(LOG_LEVEL::INFO, F("   ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n"));
		SerialDebug::log(LOG_LEVEL::INFO, F("   ID of 0x56-0x58 represents a BMP 280,\n"));
		SerialDebug::log(LOG_LEVEL::INFO, F("   ID of 0x60 represents a BME 280.\n"));
		SerialDebug::log(LOG_LEVEL::INFO, F("   ID of 0x61 represents a BME 680.\n"));
		return false;
	}

	return true;
}

bool setup_MHZ19()
{
	SerialDebug::log(LOG_LEVEL::INFO, F("MHZ-19 init..."));

	mySerial.begin(BAUDRATE);

	myMHZ19.begin(mySerial);                                // Important, Pass your Stream reference 
	myMHZ19.autoCalibration(false);                         // Turn auto calibration OFF

	return myMHZ19.errorCode;
}

void setup()
{
	SerialDebug::begin(115200);

	SerialDebug::log(LOG_LEVEL::WARN, String(F("Device restarted")));

	tft_init();

	ui_show();

	btn.initPin();

	// wait for button to reconfigure WiFi
	delay(wifiMqtt.TIMEOUT);

	bool f_setupMode = btn.getCurrentState();

	btn.setEventHandler(handleButtonEvent);

	if (f_setupMode) SerialDebug::log(LOG_LEVEL::WARN, F("BUTTON PRESSED - RECONFIGURE WIFI"));

	wifiMqtt.init(f_setupMode);

	tickerMQTT.attach(MQTT_PUBLISH_INTERVAL, callback_publishMQTT);

	if (!setup_RTC())
	{
		SerialDebug::log(LOG_LEVEL::ERROR, String(F("RTC initialization failed")));
	}
	else
	{
		checkRTC = true;
		tickerRTC.attach_ms(RTC_CHECK_INTERVAL, callback_checkRTC); // 500ms period

		DateTime curTime = rtc.now();

		SerialDebug::log(LOG_LEVEL::DEBUG, String(F("Device time: ")) + curTime.day() + "/" + curTime.month() + "/" + curTime.year() + " " + curTime.hour() + ":" + curTime.minute() + ":" + curTime.second());
	}

	if (!setup_Sensor())
	{
		SerialDebug::log(LOG_LEVEL::ERROR, String(F("Sensor initialization failed")));
	}
	else
	{
		checkSensor = true;
		tickerSensor.attach(SENSOR_CHECK_INTERVAL, callback_checkSensor);
	}

	if (!setup_MHZ19())
	{
		SerialDebug::log(LOG_LEVEL::ERROR, String(F("MHZ19 initialization failed")));
	}
	else
	{
		checkCO2 = true;
		tickerCO2.attach(CO2_CHECK_INTERVAL, callback_checkCO2);
	}

	ui_change_screen();
}

void loop()
{
	lv_timer_handler(); /* let the GUI do its work */

	btn.check();

	wifiMqtt.process();

	if (checkCO2)
	{
		CO2 = myMHZ19.getCO2();    // Request CO2 (as ppm)

		if (CO2 == 0)
		{
			SerialDebug::log(LOG_LEVEL::ERROR, String(F("MHZ19 read failed: ")) + myMHZ19.errorCode);
			myMHZ19.verify();
		}
		else
		{
			checkCO2 = false;

			uint32_t color;

			if (CO2 < 800) color = TFT_COLOR_GREEN;
			else if (CO2 < 1500) color = TFT_COLOR_YELLOW;
			else color = TFT_COLOR_RED;

			char co2[8] = { 0 };
			sprintf(co2, "%d", CO2);

			ui_updateCO2(co2, color);     // show new CO2 value

			SerialDebug::log(LOG_LEVEL::DEBUG, String(F("CO2: ")) + co2);
		}
	}

	if (checkRTC)
	{
		checkRTC = false;

		DateTime now = rtc.now();
		if (displayedTime.minute() != now.minute())
		{
			displayedTime = now;

			SerialDebug::log(LOG_LEVEL::DEBUG, String(F("Device time: ")) + displayedTime.day() + "/" + displayedTime.month() + "/" + displayedTime.year() + " " + displayedTime.hour() + ":" + displayedTime.minute() + ":" + displayedTime.second());

			char newTimeString[32] = { 0 };
			sprintf(newTimeString, "%hu/%02hu  %02hu:%02hu", displayedTime.day(), displayedTime.month(), displayedTime.hour(), displayedTime.minute());
			ui_updateTime(newTimeString);
		}
	}

	if (checkSensor)
	{
		checkSensor = false;

		temperature = sensor.readTemperature() - 2.5;
		humidity = sensor.readHumidity() + 8;
		pressure = sensor.readPressure() / 100.0F;
		altitude = sensor.readAltitude(SEALEVELPRESSURE_HPA);

		char temp[8] = { 0 };
		sprintf(temp, "%.1f", temperature);
		ui_updateTemperature(temp);

		SerialDebug::log(LOG_LEVEL::DEBUG, String(F("Temperature: ")) + temp);

		char hum[8] = { 0 };
		sprintf(hum, "%.1f", humidity);
		ui_updateHumidity(hum);

		SerialDebug::log(LOG_LEVEL::DEBUG, String(F("Humidity: ")) + hum);
	}

	if (doPublish)
	{
		doPublish = false;

		bool wifi = wifiMqtt.publishState(CO2, temperature, humidity, pressure);

		ui_updateWiFi(wifi ? TFT_COLOR_GREEN : TFT_COLOR_RED);
	}
}
