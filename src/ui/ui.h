// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.2.0
// LVGL VERSION: 8.2.0
// PROJECT: HomeAirSensor

#ifndef _HOMEAIRSENSOR_UI_H
#define _HOMEAIRSENSOR_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined __has_include
#if __has_include("lvgl.h")
#include "lvgl.h"
#elif __has_include("lvgl/lvgl.h")
#include "lvgl/lvgl.h"
#else
#include "lvgl.h"
#endif
#else
#include "lvgl.h"
#endif

extern lv_obj_t * ui_Screen0;
extern lv_obj_t * ui_connecting;
extern lv_obj_t * ui_Screen1;
extern lv_obj_t * ui_wifi;
extern lv_obj_t * ui_time;
extern lv_obj_t * ui_tempImg;
extern lv_obj_t * ui_tempVal;
extern lv_obj_t * ui_humImg;
extern lv_obj_t * ui_humVal;
extern lv_obj_t * ui_co2Img;
extern lv_obj_t * ui_co2Val;


LV_IMG_DECLARE(ui_img_dk_32x32_png);    // assets\DK_32x32.png
LV_IMG_DECLARE(ui_img_wifi_16x16_png);    // assets\wifi_16x16.png
LV_IMG_DECLARE(ui_img_temp_24x32_png);    // assets\temp_24x32.png
LV_IMG_DECLARE(ui_img_hum_30x30_png);    // assets\hum_30x30.png
LV_IMG_DECLARE(ui_img_co2_50x50_png);    // assets\co2_50x50.png


LV_FONT_DECLARE(ui_font_u22);
LV_FONT_DECLARE(ui_font_u32);


void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
