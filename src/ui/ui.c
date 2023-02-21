// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.2.0
// LVGL VERSION: 8.2.0
// PROJECT: HomeAirSensor

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////
lv_obj_t * ui_Screen0;
lv_obj_t * ui_connecting;
lv_obj_t * ui_Screen1;
lv_obj_t * ui_wifi;
lv_obj_t * ui_time;
lv_obj_t * ui_tempImg;
lv_obj_t * ui_tempVal;
lv_obj_t * ui_humImg;
lv_obj_t * ui_humVal;
lv_obj_t * ui_co2Img;
lv_obj_t * ui_co2Val;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////

///////////////////// SCREENS ////////////////////
void ui_Screen0_screen_init(void)
{
    ui_Screen0 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen0, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_connecting = lv_img_create(ui_Screen0);
    lv_img_set_src(ui_connecting, &ui_img_wifi_16x16_png);
    lv_obj_set_width(ui_connecting, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_connecting, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_connecting, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_connecting, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_connecting, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_zoom(ui_connecting, 1024);
    lv_obj_set_style_img_recolor(ui_connecting, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui_connecting, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

}
void ui_Screen1_screen_init(void)
{
    ui_Screen1 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Screen1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_Screen1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Screen1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_Screen1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Screen1, &ui_font_u22, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_wifi = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_wifi, &ui_img_wifi_16x16_png);
    lv_obj_set_width(ui_wifi, LV_SIZE_CONTENT);   /// 28
    lv_obj_set_height(ui_wifi, LV_SIZE_CONTENT);    /// 29
    lv_obj_set_x(ui_wifi, 1);
    lv_obj_set_y(ui_wifi, 3);
    lv_obj_add_flag(ui_wifi, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_wifi, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_img_recolor(ui_wifi, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui_wifi, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_time = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_time, 80);
    lv_obj_set_height(ui_time, LV_SIZE_CONTENT);    /// 0
    lv_obj_set_x(ui_time, 20);
    lv_obj_set_y(ui_time, 1);
    lv_label_set_long_mode(ui_time, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(ui_time, "00:00");

    ui_tempImg = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_tempImg, &ui_img_temp_24x32_png);
    lv_obj_set_x(ui_tempImg, -3);
    lv_obj_set_y(ui_tempImg, 1);
    lv_obj_set_align(ui_tempImg, LV_ALIGN_TOP_RIGHT);
    lv_obj_add_flag(ui_tempImg, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_tempImg, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_img_recolor(ui_tempImg, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui_tempImg, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_tempVal = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_tempVal, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_tempVal, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_tempVal, -2);
    lv_obj_set_y(ui_tempVal, 40);
    lv_obj_set_align(ui_tempVal, LV_ALIGN_TOP_RIGHT);
    lv_label_set_text(ui_tempVal, "00.0");

    ui_humImg = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_humImg, &ui_img_hum_30x30_png);
    lv_obj_set_x(ui_humImg, -5);
    lv_obj_set_y(ui_humImg, -30);
    lv_obj_set_align(ui_humImg, LV_ALIGN_BOTTOM_RIGHT);
    lv_obj_add_flag(ui_humImg, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_humImg, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_img_recolor(ui_humImg, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui_humImg, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_humVal = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_humVal, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_humVal, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_humVal, -2);
    lv_obj_set_y(ui_humVal, -2);
    lv_obj_set_align(ui_humVal, LV_ALIGN_BOTTOM_RIGHT);
    lv_label_set_text(ui_humVal, "00.0");

    ui_co2Img = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_co2Img, &ui_img_co2_50x50_png);
    lv_obj_set_x(ui_co2Img, 17);
    lv_obj_set_y(ui_co2Img, -12);
    lv_obj_set_align(ui_co2Img, LV_ALIGN_LEFT_MID);
    lv_obj_add_flag(ui_co2Img, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_co2Img, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_img_recolor(ui_co2Img, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui_co2Img, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_co2Val = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_co2Val, 85);
    lv_obj_set_height(ui_co2Val, LV_SIZE_CONTENT);    /// 0
    lv_obj_set_x(ui_co2Val, 0);
    lv_obj_set_y(ui_co2Val, 82);
    lv_label_set_long_mode(ui_co2Val, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(ui_co2Val, "0000");
    lv_obj_set_style_text_color(ui_co2Val, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_co2Val, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_co2Val, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_co2Val, &ui_font_u32, LV_PART_MAIN | LV_STATE_DEFAULT);

}

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_Screen0_screen_init();
    ui_Screen1_screen_init();
    lv_disp_load_scr(ui_Screen0);
}
