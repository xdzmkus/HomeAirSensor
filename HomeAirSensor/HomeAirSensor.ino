#include <SerialDebug.hpp>

//#define DEBUG_DRAW
#include <GFX.h>

#include <ArduinoDebounceButton.h>

using namespace ArduLibs;

#define BTN_PIN D0

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

enum class CO2_STATE
{
	UNKNOWN,
	GOOD,
	NOTOK,
	BAD
};

CO2_STATE co2State = CO2_STATE::UNKNOWN;

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

// *** TFT-1.4 *** 128 x 128 ***//

static const uint16_t screenWidth = 128;
static const uint16_t screenHeight = 128;
static const uint8_t rotation = 0;

#include <Arduino_GFX_Library.h>

#define TFT_MISO GFX_NOT_DEFINED
#define TFT_MOSI D7
#define TFT_SCLK D5
#define TFT_CS   D4   // Chip select control pin
#define TFT_DC   D3   // Data Command control pin
#define TFT_RST  GFX_NOT_DEFINED // Reset pin (could connect to RST pin)

/* More data bus class: https://github.com/moononournation/Arduino_GFX/wiki/Data-Bus-Class */
Arduino_DataBus* bus = new Arduino_ESP8266SPI(TFT_DC /* DC */, TFT_CS /* CS */);

/* More display class: https://github.com/moononournation/Arduino_GFX/wiki/Display-Class */
Arduino_GFX* gfx = new Arduino_ST7735(bus, TFT_RST /* RST */, rotation /* rotation */, false /* IPS */, screenWidth /* width */, screenHeight /* height */, 2 /* col offset 1 */, 3 /* row offset 1 */, 2 /* col offset 2 */, 1 /* row offset 2 */);

const unsigned int color = BLACK;

#define TEMP_X 28
#define TEMP_Y 10
#define TEMP_W 100
#define TEMP_H 35

GFX_Float lcdTemp = GFX_Float<Arduino_GFX>(temperature, 1, 4, gfx, color, color, TEMP_X, TEMP_Y, TEMP_W, TEMP_H);

#define HUM_X 35
#define HUM_Y 48
#define HUM_W 63
#define HUM_H 30

GFX_FloatEx lcdHum = GFX_FloatEx<Arduino_GFX>(humidity, 1, 3, "%", 2, gfx, color, color, HUM_X, HUM_Y, HUM_W, HUM_H);

#define CO2_X 50
#define CO2_Y 70
#define CO2_W 78
#define CO2_H 50

GFX_Integer lcdCO2 = GFX_Integer<Arduino_GFX>(CO2, 3, gfx, color, color, CO2_X, CO2_Y, CO2_W, CO2_H);

#define TIME_X 50
#define TIME_Y 110
#define TIME_W 78
#define TIME_H 18

GFX_Text lcdTime = GFX_Text<Arduino_GFX>("HomeAirSensor", 1, gfx, color, color, TIME_X, TIME_Y, TIME_W, TIME_H);

#define WIFI_X 6
#define WIFI_Y 52

#include "src/gui_images.h"
#include "src/WiFiMQTT_Sensor.h"

WiFiMQTT_Sensor wifiMqtt;

// Interrupts ---------------------------/

#include <Ticker.h>
Ticker tickerSensor;
Ticker tickerCO2;
Ticker tickerRTC;
Ticker tickerMQTT;

#define SENSOR_CHECK_INTERVAL	5.0F    // 5 seconds
#define CO2_CHECK_INTERVAL		60.0F   // 60 seconds
#define RTC_CHECK_INTERVAL		1000    // 1 second
#define MQTT_PUBLISH_INTERVAL	30.0F   // 30 seconds

volatile bool checkSensor = false;
volatile bool checkCO2 = false;
volatile bool checkRTC = false;
volatile bool doPublish = false;

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
		SerialDebug::println(LOG_LEVEL::DEBUG, F("Clicked"));
		SerialDebug::println(LOG_LEVEL::INFO, F("Publish state..."));
		doPublish = true;
		break;
	case BUTTON_EVENT::LongPressed:
		SerialDebug::println(LOG_LEVEL::DEBUG, F("LongPressed"));
		SerialDebug::println(LOG_LEVEL::WARN, F("Rebooting..."));
		ESP.restart();
		break;
	default:
		break;
	}
}

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

		SerialDebug::println(LOG_LEVEL::DEBUG, F("Send NTP request"));

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
	SerialDebug::println(LOG_LEVEL::DEBUG, String(F("Seconds since Jan 1 1900 = ")) + secsSince1900);

	// now convert NTP time into everyday time
	// Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
	const uint32_t seventyYears = 2208988800UL;
	// subtract seventy years:
	uint32_t epoch = secsSince1900 - seventyYears + 3 * 3600; // UTC+3

	return epoch;
}

void gui_updateScreen()
{	
	if (CO2 < 800 && co2State != CO2_STATE::GOOD)
	{
		co2State = CO2_STATE::GOOD;
		gfx->draw16bitRGBBitmap(0, 0, (uint16_t*)GREEN_BG_128x128, GREEN_BG_128X128_WIDTH, GREEN_BG_128X128_HEIGHT);
		
		lcdTemp.setColors(GREEN, color);
		lcdTemp.show();

		lcdHum.setColors(GREEN, color);
		lcdHum.show();

		lcdCO2.setColors(GREEN, color);
		lcdCO2.show();

		lcdTime.setColors(GREEN, color);
		lcdTime.show();
	}
	else if (CO2 >= 800 && CO2 < 1500 && co2State != CO2_STATE::NOTOK)
	{
		co2State = CO2_STATE::NOTOK;
		gfx->draw16bitRGBBitmap(0, 0, (uint16_t*)YELLOW_BG_128x128, YELLOW_BG_128X128_WIDTH, YELLOW_BG_128X128_HEIGHT);

		lcdTemp.setColors(YELLOW, color);
		lcdTemp.show();

		lcdHum.setColors(YELLOW, color);
		lcdHum.show();

		lcdCO2.setColors(YELLOW, color);
		lcdCO2.show();
		
		lcdTime.setColors(YELLOW, color);
		lcdTime.show();
	}
	else if (CO2 >= 1500 && co2State != CO2_STATE::BAD)
	{
		co2State = CO2_STATE::BAD;
		gfx->draw16bitRGBBitmap(0, 0, (uint16_t*)RED_BG_128x128, RED_BG_128X128_WIDTH, RED_BG_128X128_HEIGHT);

		lcdTemp.setColors(RED, color);
		lcdTemp.show();

		lcdHum.setColors(RED, color);
		lcdHum.show();

		lcdCO2.setColors(RED, color);
		lcdCO2.show();
		
		lcdTime.setColors(RED, color);
		lcdTime.show();
	}
}


bool setup_RTC()
{
	SerialDebug::println(LOG_LEVEL::INFO, F("RTC init..."));

	if (!rtc.begin())
	{
		SerialDebug::println(LOG_LEVEL::ERROR, F("Couldn't find RTC"));
		return false;
	}

	uint32_t unixtime = getNTPTime();

	SerialDebug::println(LOG_LEVEL::DEBUG, String(F("Unix time since Jan 1 1970 = ")) + String(unixtime));

	if (unixtime != 0)
	{
		rtc.adjust(unixtime);
	}

	SerialDebug::println(LOG_LEVEL::INFO, F("RTC done."));

	return true;
}

bool setup_Sensor()
{
	SerialDebug::println(LOG_LEVEL::INFO, F("BME280 init..."));

	unsigned status = sensor.begin(0x76);

	if (!status)
	{
		SerialDebug::println(LOG_LEVEL::ERROR, F("Could not find a valid sensor, check wiring, address, sensor ID!"));
		SerialDebug::println(LOG_LEVEL::INFO, String(F("SensorID was: 0x")) + String(sensor.sensorID(), 16));
		SerialDebug::println(LOG_LEVEL::INFO, F("   ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n"));
		SerialDebug::println(LOG_LEVEL::INFO, F("   ID of 0x56-0x58 represents a BMP 280,\n"));
		SerialDebug::println(LOG_LEVEL::INFO, F("   ID of 0x60 represents a BME 280.\n"));
		SerialDebug::println(LOG_LEVEL::INFO, F("   ID of 0x61 represents a BME 680.\n"));
		return false;
	}

	SerialDebug::println(LOG_LEVEL::INFO, F("BME280 done."));

	return true;
}

bool setup_MHZ19()
{
	SerialDebug::println(LOG_LEVEL::INFO, F("MHZ-19 init..."));

	mySerial.begin(BAUDRATE);

	myMHZ19.begin(mySerial);                                // Important, Pass your Stream reference 
	myMHZ19.autoCalibration(false);                         // Turn auto calibration OFF

	SerialDebug::println(LOG_LEVEL::INFO, F("MHZ-19 done."));

	return myMHZ19.errorCode;
}

void setup()
{
	SerialDebug::begin(115200);

	SerialDebug::println(LOG_LEVEL::WARN, String(F("Device started")));

	// TFT init
	gfx->begin();
	gfx->setTextWrap(false);
	gfx->draw16bitRGBBitmap(0, 0, (uint16_t*)DK_LOGO_128x128, DK_LOGO_128X128_WIDTH, DK_LOGO_128X128_HEIGHT);

	btn.initPin();

	// wait for button to reconfigure WiFi
	delay(wifiMqtt.TIMEOUT);

	bool f_setupMode = btn.getCurrentState();

	btn.setEventHandler(handleButtonEvent);

	if (f_setupMode) SerialDebug::println(LOG_LEVEL::WARN, F("BUTTON PRESSED - RECONFIGURE WIFI"));

	wifiMqtt.init(f_setupMode);

	tickerMQTT.attach(MQTT_PUBLISH_INTERVAL, callback_publishMQTT);

	if (!setup_RTC())
	{
		SerialDebug::println(LOG_LEVEL::ERROR, String(F("RTC disabled!")));
	}
	else
	{
		checkRTC = true;
		tickerRTC.attach_ms(RTC_CHECK_INTERVAL, callback_checkRTC); // 500ms period

		DateTime curTime = rtc.now();

		SerialDebug::println(LOG_LEVEL::DEBUG, String(F("Device time: ")) + curTime.day() + "/" + curTime.month() + "/" + curTime.year() + " " + curTime.hour() + ":" + curTime.minute() + ":" + curTime.second());
	}

	if (!setup_Sensor())
	{
		SerialDebug::println(LOG_LEVEL::ERROR, String(F("BME disabled!")));
	}
	else
	{
		checkSensor = true;
		tickerSensor.attach(SENSOR_CHECK_INTERVAL, callback_checkSensor);
	}

	if (!setup_MHZ19())
	{
		SerialDebug::println(LOG_LEVEL::ERROR, String(F("MHZ19 disabled!")));
	}
	else
	{
		checkCO2 = true;
		tickerCO2.attach(CO2_CHECK_INTERVAL, callback_checkCO2);
	}

	lcdTemp.setDecimalSize(3);
	lcdHum.setDecimalSize(1);

	gui_updateScreen();

	SerialDebug::println(LOG_LEVEL::INFO, String(F("Device ready")));
}

void loop()
{
	btn.check();

	wifiMqtt.process();

	if (checkCO2)
	{
		CO2 = myMHZ19.getCO2();    // Request CO2 (as ppm)

		if (CO2 == 0)
		{
			SerialDebug::println(LOG_LEVEL::ERROR, String(F("MHZ19 read failed: ")) + myMHZ19.errorCode);
			myMHZ19.verify();
		}
		else
		{
			checkCO2 = false;

			SerialDebug::println(LOG_LEVEL::DEBUG, String(F("CO2: ")) + CO2);

			lcdCO2.updateValue(CO2);

			gui_updateScreen();
		}
	}

	if (checkRTC)
	{
		checkRTC = false;

		DateTime now = rtc.now();
		if (displayedTime.minute() != now.minute())
		{
			displayedTime = now;

			char newTimeString[32] = { 0 };
			sprintf(newTimeString, "%hu/%02hu %02hu:%02hu", displayedTime.day(), displayedTime.month(), displayedTime.hour(), displayedTime.minute());
			SerialDebug::println(LOG_LEVEL::DEBUG, String(F("Device time: ")) + String(newTimeString));

			lcdTime.updateText(newTimeString);
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
		SerialDebug::println(LOG_LEVEL::DEBUG, String(F("Temperature: ")) + temp);

		lcdTemp.updateValue(temperature);

		char hum[8] = { 0 };
		sprintf(hum, "%.1f", humidity);
		SerialDebug::println(LOG_LEVEL::DEBUG, String(F("Humidity: ")) + hum);

		lcdHum.updateValue(humidity);
	}

	if (doPublish)
	{
		doPublish = false;

		if (wifiMqtt.publishState(CO2, temperature, humidity, pressure))
		{
			gfx->draw16bitRGBBitmap(WIFI_X, WIFI_Y, (uint16_t*)WIFI_16x16, WIFI_16x16_WIDTH, WIFI_16x16_HEIGHT);
		}
		else
		{
			gfx->fillRect(WIFI_X, WIFI_Y, WIFI_16x16_WIDTH, WIFI_16x16_HEIGHT, WHITE);
		}
	}
}
