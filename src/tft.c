#include "tft.h"

#include "ui/ui.h"

#include <lvgl.h>

#define MSG_TIME_CHANGED 100
#define MSG_TEMPERATURE_CHANGED 101
#define MSG_HUMIDITY_CHANGED 102
#define MSG_CO2_CHANGED 103

static void label_event_cb(lv_event_t* e)
{
	lv_obj_t* label = lv_event_get_target(e);
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_MSG_RECEIVED)
	{
		lv_msg_t* m = lv_event_get_msg(e);
		lv_label_set_text(label, lv_msg_get_payload(m));
	}
}

static void ui_register_events()
{
	lv_obj_add_event_cb(ui_time, label_event_cb, LV_EVENT_MSG_RECEIVED, NULL);
	lv_msg_subscribe_obj(MSG_TIME_CHANGED, ui_time, NULL);

	lv_obj_add_event_cb(ui_tempVal, label_event_cb, LV_EVENT_MSG_RECEIVED, NULL);
	lv_msg_subscribe_obj(MSG_TEMPERATURE_CHANGED, ui_tempVal, NULL);

	lv_obj_add_event_cb(ui_humVal, label_event_cb, LV_EVENT_MSG_RECEIVED, NULL);
	lv_msg_subscribe_obj(MSG_HUMIDITY_CHANGED, ui_humVal, NULL);

	lv_obj_add_event_cb(ui_co2Val, label_event_cb, LV_EVENT_MSG_RECEIVED, NULL);
	lv_msg_subscribe_obj(MSG_CO2_CHANGED, ui_co2Val, NULL);
}


void ui_show()
{
	ui_init();

	ui_register_events();

	// refresh display
	lv_disp_t* dispp = lv_disp_get_default();
	lv_refr_now(dispp);
}

void ui_change_screen()
{
	_ui_screen_change(ui_Screen1, LV_SCR_LOAD_ANIM_NONE, 100, 0);
}

void ui_updateTemperature(const char* temp)
{
	lv_msg_send(MSG_TEMPERATURE_CHANGED, temp);
}

void ui_updateHumidity(const char* hum)
{
	lv_msg_send(MSG_HUMIDITY_CHANGED, hum);
}

void ui_updateCO2(const char* co2, enum TFT_COLOR co2_color)
{
	lv_msg_send(MSG_CO2_CHANGED, co2);

	lv_obj_set_style_img_recolor(ui_co2Img, lv_color_hex(co2_color), LV_PART_MAIN | LV_STATE_DEFAULT);
}

void ui_updateTime(const char* displayedTime)
{
	lv_msg_send(MSG_TIME_CHANGED, displayedTime);
}

void ui_updateWiFi(enum TFT_COLOR wifi_color)
{
	lv_obj_set_style_img_recolor(ui_wifi, lv_color_hex(wifi_color), LV_PART_MAIN | LV_STATE_DEFAULT);
}


