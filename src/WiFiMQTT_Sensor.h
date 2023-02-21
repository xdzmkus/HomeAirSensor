#ifndef _WIFIMQTT_HA_SENSOR_H_
#define _WIFIMQTT_HA_SENSOR_H_

#include <WiFiMQTT_HA.h>

const char* const WLAN_AP_SSID = "HOME-AIR-SENSOR";
const char* const WLAN_AP_PASS = "5b385136-";
const char* const WLAN_HOSTNAME = "HOME-AIR-SENSOR";

const char* const DEVICE_UNIQUE_ID = "HOME-AIR-36c";

const char* const DEVICE_manufacturer = "XDZMKUS";
const char* const DEVICE_model = "Air Sensor";
const char* const DEVICE_name = "Home Air sensor";
const char* const DEVICE_sw_version = "2.0.0";

const char* const TEMPERATURE_SENSOR_UNIQUE_ID = "HOME-AIR-36c-temperature";
const char* const HUMIDITY_SENSOR_UNIQUE_ID = "HOME-AIR-36c-humidity";
const char* const PRESSURE_SENSOR_UNIQUE_ID = "HOME-AIR-36c-pressure";
const char* const CO2_SENSOR_UNIQUE_ID = "HOME-AIR-36c-co2";

const char* const DISCOVERY_TOPIC_TEMPERATURE = "homeassistant/sensor/home-air-sensor/temperature/config";
const char* const DISCOVERY_TOPIC_HUMIDITY = "homeassistant/sensor/home-air-sensor/humidity/config";
const char* const DISCOVERY_TOPIC_PRESSURE = "homeassistant/sensor/home-air-sensor/pressure/config";
const char* const DISCOVERY_TOPIC_CO2 = "homeassistant/sensor/home-air-sensor/co2/config";

const char* const COMMON_STATE_TOPIC = "homeassistant/sensor/home-air-sensor/state";
const char* const AVAIL_STATUS_TOPIC = "homeassistant/sensor/home-air-sensor/status";

class WiFiMQTT_Sensor : public WiFiMQTT_HA
{
public:

	WiFiMQTT_Sensor()
		: WiFiMQTT_HA(WLAN_AP_SSID, WLAN_AP_PASS, WLAN_HOSTNAME, DEVICE_UNIQUE_ID, AVAIL_STATUS_TOPIC)
	{
	}

	bool publishState(int co2, float temperature, float humidity, float pressure)
	{
		DynamicJsonDocument doc(128);

		doc["temperature"] = String(temperature, 1);
		doc["humidity"] = String(humidity, 1);
		doc["pressure"] = String(pressure, 1);
		doc["co2"] = co2;

		return publishJson(COMMON_STATE_TOPIC, doc);
	}

protected:

	void discover() override
	{
		StaticJsonDocument<512> deviceDoc;

		deviceDoc["platform"] = "mqtt";
		deviceDoc["enabled_by_default"] = true;
		deviceDoc["state_class"] = "measurement";
		deviceDoc["state_topic"] = COMMON_STATE_TOPIC;
		deviceDoc["json_attributes_topic"] = COMMON_STATE_TOPIC;
		deviceDoc["availability"][0]["topic"] = AVAIL_STATUS_TOPIC;

		JsonObject device = deviceDoc.createNestedObject("device");
		device["identifiers"] = DEVICE_UNIQUE_ID;
		device["manufacturer"] = DEVICE_manufacturer;
		device["model"] = DEVICE_model;
		device["name"] = DEVICE_name;
		device["sw_version"] = DEVICE_sw_version;

		DynamicJsonDocument doc(1024);

		doc = deviceDoc;
		doc["name"] = "Temperature";
		doc["device_class"] = "temperature";
		doc["unit_of_measurement"] = "ºC";
		doc["value_template"] = "{{ value_json.temperature }}";
		doc["unique_id"] = TEMPERATURE_SENSOR_UNIQUE_ID;

		publishJson(DISCOVERY_TOPIC_TEMPERATURE, doc, true);

		doc = deviceDoc;
		doc["name"] = "Humidity";
		doc["device_class"] = "humidity";
		doc["unit_of_measurement"] = "%";
		doc["value_template"] = "{{ value_json.humidity }}";
		doc["unique_id"] = HUMIDITY_SENSOR_UNIQUE_ID;

		publishJson(DISCOVERY_TOPIC_HUMIDITY, doc, true);

		doc = deviceDoc;
		doc["name"] = "Pressure";
		doc["device_class"] = "pressure";
		doc["unit_of_measurement"] = "hPa";
		doc["value_template"] = "{{ value_json.pressure }}";
		doc["unique_id"] = PRESSURE_SENSOR_UNIQUE_ID;

		publishJson(DISCOVERY_TOPIC_PRESSURE, doc, true);

		doc = deviceDoc;
		doc["name"] = "CO2";
		doc["device_class"] = "carbon_dioxide";
		doc["unit_of_measurement"] = "ppm";
		doc["value_template"] = "{{ value_json.co2 }}";
		doc["unique_id"] = CO2_SENSOR_UNIQUE_ID;

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
