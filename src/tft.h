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

enum TFT_COLOR
{
	GREEN = 0x00FF00,
	YELLOW = 0xFFFF00,
	RED = 0xFF0000,
};

void ui_show();

void ui_change_screen();

void ui_updateTemperature(const char* temp);

void ui_updateHumidity(const char* hum);

void ui_updateCO2(const char* co2, enum TFT_COLOR co2_color);

void ui_updateTime(const char* displayedTime);

void ui_updateWiFi(enum TFT_COLOR wifi_color);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif

