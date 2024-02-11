#pragma once

#ifdef __AVR__
#include <avr/io.h>
#include <avr/pgmspace.h>
#elif defined(ESP8266) || defined(ESP32)
#include <pgmspace.h>
#elif defined(__IMXRT1052__) || defined(__IMXRT1062__)
// PROGMEM is defefind for T4 to place data in specific memory section
#undef PROGMEM
#define PROGMEM
#else
#define PROGMEM
#endif

#define DK_LOGO_128X128_WIDTH (128)
#define DK_LOGO_128X128_HEIGHT (128)

extern const unsigned char DK_LOGO_128x128[] PROGMEM;

#define RED_BG_128X128_WIDTH (128)
#define RED_BG_128X128_HEIGHT (128)

extern const unsigned char RED_BG_128x128[] PROGMEM;

#define GREEN_BG_128X128_WIDTH (128)
#define GREEN_BG_128X128_HEIGHT (128)

extern const unsigned char GREEN_BG_128x128[] PROGMEM;

#define YELLOW_BG_128X128_WIDTH (128)
#define YELLOW_BG_128X128_HEIGHT (128)

extern const unsigned char YELLOW_BG_128x128[] PROGMEM;

#define WIFI_16x16_WIDTH (16)
#define WIFI_16x16_HEIGHT (16)

extern const unsigned char WIFI_16x16[] PROGMEM;
