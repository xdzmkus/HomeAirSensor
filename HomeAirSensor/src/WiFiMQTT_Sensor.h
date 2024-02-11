#ifndef _WIFIMQTT_SENSOR_H_
#define _WIFIMQTT_SENSOR_H_

#include <WiFiMQTT_HA.hpp>

static const char* const WLAN_AP_SSID PROGMEM = "HOME-AIR-SENSOR";
static const char* const WLAN_AP_PASS PROGMEM = "5b385136";
static const char* const WLAN_HOSTNAME PROGMEM = "HOME-AIR-SENSOR";

static const char* const DEVICE_UNIQUE_ID PROGMEM = "HOME-AIR-36c";

static const char* const DEVICE_manufacturer PROGMEM = "XDZMKUS";
static const char* const DEVICE_model PROGMEM = "Air Sensor";
static const char* const DEVICE_name PROGMEM = "Home Air sensor";
static const char* const DEVICE_sw_version PROGMEM = "2.0.0";

static const char* const TEMPERATURE_SENSOR_UNIQUE_ID PROGMEM = "HOME-AIR-36c-temperature";
static const char* const HUMIDITY_SENSOR_UNIQUE_ID PROGMEM = "HOME-AIR-36c-humidity";
static const char* const PRESSURE_SENSOR_UNIQUE_ID PROGMEM = "HOME-AIR-36c-pressure";
static const char* const CO2_SENSOR_UNIQUE_ID PROGMEM = "HOME-AIR-36c-co2";

static const char* const DISCOVERY_TOPIC_TEMPERATURE PROGMEM = "homeassistant/sensor/home-air-sensor/temperature/config";
static const char* const DISCOVERY_TOPIC_HUMIDITY PROGMEM = "homeassistant/sensor/home-air-sensor/humidity/config";
static const char* const DISCOVERY_TOPIC_PRESSURE PROGMEM = "homeassistant/sensor/home-air-sensor/pressure/config";
static const char* const DISCOVERY_TOPIC_CO2 PROGMEM = "homeassistant/sensor/home-air-sensor/co2/config";

static const char* const COMMON_STATE_TOPIC PROGMEM = "homeassistant/sensor/home-air-sensor/state";
static const char* const AVAIL_STATUS_TOPIC PROGMEM = "homeassistant/sensor/home-air-sensor/status";

using namespace ArduLibs;

class WiFiMQTT_Sensor : public WiFiMQTT_HA
{
public:

	WiFiMQTT_Sensor()
		: WiFiMQTT_HA(WLAN_AP_SSID, WLAN_AP_PASS, WLAN_HOSTNAME, DEVICE_UNIQUE_ID, AVAIL_STATUS_TOPIC)
	{
	}

	bool publishState(int co2, float temperature, float humidity, float pressure)
	{
		JsonDocument doc;

		doc[F("temperature")] = String(temperature, 1);
		doc[F("humidity")] = String(humidity, 1);
		doc[F("pressure")] = String(pressure, 1);
		doc[F("co2")] = co2;

		return publishJson(COMMON_STATE_TOPIC, doc);
	}

protected:

	void discover() override
	{
		JsonDocument deviceDoc;

		deviceDoc[F("platform")] = F("mqtt");
		deviceDoc[F("enabled_by_default")] = true;
		deviceDoc[F("state_class")] = F("measurement");
		deviceDoc[F("state_topic")] = COMMON_STATE_TOPIC;
		deviceDoc[F("json_attributes_topic")] = COMMON_STATE_TOPIC;
		deviceDoc[F("availability")][0][F("topic")] = AVAIL_STATUS_TOPIC;
		deviceDoc[F("device")][F("identifiers")] = DEVICE_UNIQUE_ID;
		deviceDoc[F("device")][F("manufacturer")] = DEVICE_manufacturer;
		deviceDoc[F("device")][F("model")] = DEVICE_model;
		deviceDoc[F("device")][F("name")] = DEVICE_name;
		deviceDoc[F("device")][F("sw_version")] = DEVICE_sw_version;

		JsonDocument doc;

		doc = deviceDoc;
		doc[F("name")] = F("Temperature");
		doc[F("device_class")] = F("temperature");
		doc[F("unit_of_measurement")] = F("°C");
		doc[F("value_template")] = F("{{ value_json.temperature }}");
		doc[F("unique_id")] = TEMPERATURE_SENSOR_UNIQUE_ID;

		publishJson(DISCOVERY_TOPIC_TEMPERATURE, doc, true);

		doc = deviceDoc;
		doc[F("name")] = F("Humidity");
		doc[F("device_class")] = F("humidity");
		doc[F("unit_of_measurement")] = F("%");
		doc[F("value_template")] = F("{{ value_json.humidity }}");
		doc[F("unique_id")] = HUMIDITY_SENSOR_UNIQUE_ID;

		publishJson(DISCOVERY_TOPIC_HUMIDITY, doc, true);

		doc = deviceDoc;
		doc[F("name")] = F("Pressure");
		doc[F("device_class")] = F("pressure");
		doc[F("unit_of_measurement")] = F("hPa");
		doc[F("value_template")] = F("{{ value_json.pressure }}");
		doc[F("unique_id")] = PRESSURE_SENSOR_UNIQUE_ID;

		publishJson(DISCOVERY_TOPIC_PRESSURE, doc, true);

		doc = deviceDoc;
		doc[F("name")] = F("CO2");
		doc[F("device_class")] = F("carbon_dioxide");
		doc[F("unit_of_measurement")] = F("ppm");
		doc[F("value_template")] = F("{{ value_json.co2 }}");
		doc[F("unique_id")] = CO2_SENSOR_UNIQUE_ID;

		publishJson(DISCOVERY_TOPIC_CO2, doc, true);
	}

	void subscribe() override
	{
		return;
	}

	void receiveMessage(char* topic, uint8_t* payload, unsigned int length) override
	{
		WiFiMQTT_HA::receiveMessage(topic, payload, length);
	}
};

#endif
