#ifndef _TFT_h
#define _TFT_h

#ifdef __cplusplus
extern "C" {
#endif

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

	const uint32_t TFT_COLOR_GREEN = 0x00FF00;
	const uint32_t TFT_COLOR_YELLOW = 0xFFFF00;
	const uint32_t TFT_COLOR_RED = 0xFF0000;

	void ui_show();

	void ui_change_screen();

	void ui_updateTemperature(const char* temp);

	void ui_updateHumidity(const char* hum);

	void ui_updateCO2(const char* co2, uint32_t co2_color);

	void ui_updateTime(const char* displayedTime);

	void ui_updateWiFi(uint32_t wifi_color);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif

