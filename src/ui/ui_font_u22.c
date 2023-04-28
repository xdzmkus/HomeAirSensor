/*******************************************************************************
 * Size: 22 px
 * Bpp: 1
 * Opts: --bpp 1 --size 22 --font C:\Users\xdzmk\Documents\SquareLine\assets\Ubuntu-M.ttf -o C:\Users\xdzmk\Documents\SquareLine\assets\ui_font_u22.c --format lvgl -r 0x20-0x3F --no-compress --no-prefilter
 ******************************************************************************/

#include "ui.h"

#ifndef UI_FONT_U22
#define UI_FONT_U22 1
#endif

#if UI_FONT_U22

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xff, 0xff, 0xff, 0xfc, 0x1, 0xff,

    /* U+0022 "\"" */
    0xef, 0xdf, 0xbf, 0x7e, 0xfd, 0xc0,

    /* U+0023 "#" */
    0xc, 0x70, 0x63, 0x83, 0x18, 0x38, 0xcf, 0xff,
    0xff, 0xfc, 0x63, 0x83, 0x1c, 0x38, 0xc1, 0xc6,
    0x3f, 0xff, 0xff, 0xf3, 0x1c, 0x38, 0xc1, 0xc6,
    0xe, 0x30,

    /* U+0024 "$" */
    0x1c, 0x7, 0x3, 0xf9, 0xfe, 0xf0, 0xb8, 0xe,
    0x3, 0xc0, 0x7e, 0xf, 0xc0, 0xf8, 0xf, 0x1,
    0xc0, 0x7c, 0x3f, 0xfe, 0xff, 0x7, 0x1, 0xc0,
    0x70,

    /* U+0025 "%" */
    0x38, 0x1c, 0x1f, 0x7, 0xc, 0x63, 0x83, 0x18,
    0xe0, 0xc6, 0x70, 0x31, 0x98, 0x7, 0xce, 0x0,
    0xe3, 0x3c, 0x1, 0xdf, 0x80, 0xee, 0x70, 0x3b,
    0xc, 0x1c, 0xc3, 0x6, 0x30, 0xc3, 0x8e, 0x70,
    0xc1, 0xf8, 0x70, 0x3c,

    /* U+0026 "&" */
    0x1f, 0x0, 0xfe, 0x7, 0x1c, 0x1c, 0x70, 0x71,
    0xc1, 0xee, 0x3, 0xf0, 0x7, 0x80, 0x7e, 0x19,
    0xde, 0x6e, 0x3f, 0xb8, 0x7c, 0xe0, 0xf3, 0xc7,
    0xe7, 0xff, 0x87, 0xc7,

    /* U+0027 "'" */
    0xff, 0xff, 0xc0,

    /* U+0028 "(" */
    0x0, 0x71, 0xce, 0x31, 0xc7, 0x38, 0xe3, 0x8e,
    0x38, 0xe3, 0x8e, 0x1c, 0x71, 0xc3, 0x8e, 0x1c,
    0x20,

    /* U+0029 ")" */
    0x3, 0x8e, 0x1c, 0x30, 0xe3, 0x87, 0x1c, 0x71,
    0xc7, 0x1c, 0x71, 0xce, 0x38, 0xe7, 0x1c, 0xe1,
    0x0,

    /* U+002A "*" */
    0x1c, 0xe, 0x37, 0x7d, 0x7f, 0xf8, 0xe0, 0xd8,
    0xee, 0x22, 0x0,

    /* U+002B "+" */
    0xe, 0x3, 0x80, 0xe0, 0x38, 0xff, 0xff, 0xf0,
    0xe0, 0x38, 0xe, 0x3, 0x80, 0xe0,

    /* U+002C "," */
    0x77, 0x77, 0x6e, 0x0,

    /* U+002D "-" */
    0xff, 0xf0,

    /* U+002E "." */
    0xff, 0x80,

    /* U+002F "/" */
    0x0, 0xc0, 0x38, 0x7, 0x0, 0xc0, 0x38, 0x7,
    0x0, 0xc0, 0x38, 0x7, 0x1, 0xc0, 0x38, 0x7,
    0x1, 0xc0, 0x38, 0x6, 0x1, 0xc0, 0x38, 0x6,
    0x1, 0xc0, 0x38, 0x6, 0x0,

    /* U+0030 "0" */
    0x1f, 0x7, 0xf1, 0xc7, 0x38, 0xee, 0xf, 0xc1,
    0xf8, 0x3f, 0x7, 0xe0, 0xfc, 0x1f, 0x83, 0xf0,
    0x77, 0x1c, 0xe3, 0x8f, 0xe0, 0xf8,

    /* U+0031 "1" */
    0xe, 0x3c, 0xff, 0xfe, 0xe1, 0xc3, 0x87, 0xe,
    0x1c, 0x38, 0x70, 0xe1, 0xc3, 0x87,

    /* U+0032 "2" */
    0x3e, 0x3f, 0xcc, 0x78, 0xe, 0x3, 0x80, 0xe0,
    0x78, 0x3c, 0x1e, 0x7, 0x3, 0x81, 0xc0, 0x70,
    0x38, 0xf, 0xff, 0xff,

    /* U+0033 "3" */
    0x3f, 0x1f, 0xe4, 0x3c, 0x7, 0x1, 0xc0, 0xe1,
    0xf0, 0x7c, 0x3, 0x80, 0x70, 0x1c, 0x7, 0x1,
    0xd0, 0xef, 0xf9, 0xf8,

    /* U+0034 "4" */
    0x3, 0x80, 0xf0, 0x3e, 0x7, 0xc1, 0xb8, 0x77,
    0xc, 0xe3, 0x9c, 0x63, 0x9c, 0x73, 0xff, 0xff,
    0xf0, 0x38, 0x7, 0x0, 0xe0, 0x1c,

    /* U+0035 "5" */
    0x7f, 0x9f, 0xe7, 0x1, 0xc0, 0x70, 0x1c, 0x7,
    0xe1, 0xfe, 0x7, 0x80, 0xf0, 0x1c, 0x7, 0x1,
    0xe0, 0xef, 0xfb, 0xf8,

    /* U+0036 "6" */
    0x3, 0xc1, 0xf8, 0x78, 0x1c, 0x7, 0x0, 0xe0,
    0x3f, 0xc7, 0xfe, 0xe1, 0xfc, 0x1f, 0x83, 0xf0,
    0x7e, 0xe, 0xe3, 0x8f, 0xf0, 0xf8,

    /* U+0037 "7" */
    0xff, 0xff, 0xf0, 0x18, 0xe, 0x7, 0x1, 0xc0,
    0x60, 0x38, 0xc, 0x7, 0x1, 0xc0, 0x70, 0x18,
    0xe, 0x3, 0x80, 0xe0,

    /* U+0038 "8" */
    0x1f, 0xf, 0xf3, 0xcf, 0x70, 0xee, 0x1d, 0xc3,
    0x9e, 0xe1, 0xf8, 0x3f, 0x8e, 0x7b, 0x83, 0xf0,
    0x7e, 0xf, 0xe3, 0xdf, 0xf0, 0xf8,

    /* U+0039 "9" */
    0x1f, 0xf, 0xf1, 0xc7, 0x70, 0xee, 0xf, 0xc1,
    0xf8, 0x3f, 0x87, 0x7f, 0xe3, 0xfc, 0x7, 0x0,
    0xe0, 0x3c, 0x1f, 0x1f, 0x83, 0xc0,

    /* U+003A ":" */
    0xff, 0x80, 0x0, 0x1f, 0xf0,

    /* U+003B ";" */
    0xff, 0x80, 0x0, 0xff, 0xfd, 0x80,

    /* U+003C "<" */
    0x0, 0x40, 0x70, 0x7c, 0xfc, 0xfc, 0x38, 0xf,
    0x80, 0xf8, 0xf, 0xc0, 0xf0, 0x4,

    /* U+003D "=" */
    0xff, 0xff, 0xf0, 0x0, 0x0, 0x0, 0x3f, 0xff,
    0xfc,

    /* U+003E ">" */
    0x80, 0x38, 0xf, 0x80, 0xfc, 0xf, 0xc0, 0x70,
    0x7c, 0x7c, 0xfc, 0x3c, 0x8, 0x0,

    /* U+003F "?" */
    0x7e, 0x7f, 0x91, 0xe0, 0x70, 0x38, 0x3c, 0x3c,
    0x3c, 0x3c, 0x1c, 0xe, 0x0, 0x0, 0x1, 0xc0,
    0xe0, 0x70
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 82, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 108, .box_w = 3, .box_h = 16, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 7, .adv_w = 161, .box_w = 7, .box_h = 6, .ofs_x = 2, .ofs_y = 11},
    {.bitmap_index = 13, .adv_w = 236, .box_w = 13, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 39, .adv_w = 200, .box_w = 10, .box_h = 20, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 64, .adv_w = 316, .box_w = 18, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 100, .adv_w = 241, .box_w = 14, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 128, .adv_w = 92, .box_w = 3, .box_h = 6, .ofs_x = 2, .ofs_y = 11},
    {.bitmap_index = 131, .adv_w = 119, .box_w = 6, .box_h = 22, .ofs_x = 2, .ofs_y = -4},
    {.bitmap_index = 148, .adv_w = 119, .box_w = 6, .box_h = 22, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 165, .adv_w = 170, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 176, .adv_w = 200, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 190, .adv_w = 94, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 194, .adv_w = 111, .box_w = 6, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 196, .adv_w = 94, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 198, .adv_w = 146, .box_w = 11, .box_h = 21, .ofs_x = -1, .ofs_y = -4},
    {.bitmap_index = 227, .adv_w = 200, .box_w = 11, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 249, .adv_w = 200, .box_w = 7, .box_h = 16, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 263, .adv_w = 200, .box_w = 10, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 283, .adv_w = 200, .box_w = 10, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 303, .adv_w = 200, .box_w = 11, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 325, .adv_w = 200, .box_w = 10, .box_h = 16, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 345, .adv_w = 200, .box_w = 11, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 367, .adv_w = 200, .box_w = 10, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 387, .adv_w = 200, .box_w = 11, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 409, .adv_w = 200, .box_w = 11, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 431, .adv_w = 94, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 436, .adv_w = 93, .box_w = 3, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 442, .adv_w = 200, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 456, .adv_w = 200, .box_w = 10, .box_h = 7, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 465, .adv_w = 200, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 479, .adv_w = 149, .box_w = 9, .box_h = 16, .ofs_x = 0, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 32, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Pair left and right glyphs for kerning*/
static const uint8_t kern_pair_glyph_ids[] =
{
    9, 10
};

/* Kerning between the respective left and right glyphs
 * 4.4 format which needs to scaled with `kern_scale`*/
static const int8_t kern_pair_values[] =
{
    21
};

/*Collect the kern pair's data in one place*/
static const lv_font_fmt_txt_kern_pair_t kern_pairs =
{
    .glyph_ids = kern_pair_glyph_ids,
    .values = kern_pair_values,
    .pair_cnt = 1,
    .glyph_ids_size = 0
};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = &kern_pairs,
    .kern_scale = 16,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t ui_font_u22 = {
#else
lv_font_t ui_font_u22 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 22,          /*The maximum line height required by the font*/
    .base_line = 4,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -3,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if UI_FONT_U22*/

