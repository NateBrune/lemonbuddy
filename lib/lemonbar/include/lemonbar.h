#ifndef _LEMONBAR_H_
#define _LEMONBAR_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <xcb/xcb.h>
#include <xcb/xcbext.h>

struct XftFont;

typedef struct lemonbar_font_t {
  xcb_font_t ptr;
  xcb_charinfo_t *width_lut;
  XftFont *xft_ft;
  int ascent;
  int descent, height, width;
  uint16_t char_max;
  uint16_t char_min;
} lemonbar_font_t;

typedef struct lemonbar_bar_t {
  xcb_rectangle_t rect;
  xcb_window_t window;
  xcb_pixmap_t pixmap;
} lemonbar_bar_t ;

typedef struct lemonbar_area_t {
  unsigned int begin:16;
  unsigned int end:16;
  bool active:1;
  int align:3;
  unsigned int button:3;
  xcb_window_t window;
  char *cmd;
} lemonbar_area_t;

typedef union lemonbar_rgba_t {
  struct {
    uint8_t b;
    uint8_t g;
    uint8_t r;
    uint8_t a;
  };
  uint32_t v;
} lemonbar_rgba_t;

typedef struct lemonbar_area_stack_t {
  int at;
  unsigned int max;
  lemonbar_area_t *area;
} lemonbar_area_stack_t;

enum LEMONBAR_ATTR {
  ATTR_OVERL = (1<<0),
  ATTR_UNDERL = (1<<1),
};

enum LEMONBAR_ALIGNMENT {
  ALIGN_L = 0,
  ALIGN_C,
  ALIGN_R
};

enum LEMONBAR_GC {
  GC_DRAW = 0,
  GC_CLEAR,
  GC_ATTR,
  GC_BORDERTOP,
  GC_BORDERBTM,
  GC_MAX
};

void lemonbar_update_gc(void);
void lemonbar_fill_gradient_test(xcb_drawable_t d);
// void lemonbar_fill_gradient(xcb_drawable_t d, int x, int width, lemonbar_rgba_t start, lemonbar_rgba_t stop);
void lemonbar_fill_rect(xcb_drawable_t d, xcb_gcontext_t _gc, int x, int y, int width, int height);
xcb_void_cookie_t lemonbar_xcb_poly_text_16_simple(xcb_connection_t *c,
  xcb_drawable_t drawable, xcb_gcontext_t gc, int16_t x, int16_t y,
  uint32_t len, const uint16_t *str);
int lemonbar_xft_char_width_slot(uint16_t ch);
int lemonbar_xft_char_width(uint16_t ch, lemonbar_font_t *cur_font);
int lemonbar_shift(int x, int align, int ch_width);
void lemonbar_draw_lines(int x, int w);
void lemonbar_draw_shift(int x, int align, int w);
int lemonbar_draw_char(lemonbar_font_t *cur_font, int x, int align, uint16_t ch);
lemonbar_rgba_t lemonbar_parse_color(const char *str, char **end, const lemonbar_rgba_t def);
void lemonbar_set_attribute(const char modifier, const char attribute);
lemonbar_area_t *lemonbar_area_get(xcb_window_t win, const int btn, const int x);
void lemonbar_area_shift (xcb_window_t win, const int align, int delta);
bool lemonbar_area_add(char *str, const char *optend, char **end, const int x, const int align, const int button);
bool lemonbar_font_has_glyph(lemonbar_font_t *font, const uint16_t c);
lemonbar_font_t *lemonbar_select_drawable_font(const uint16_t c);
void lemonbar_parse_data(const char *text);
void lemonbar_font_load(const char *pattern, int offset_y);
void lemonbar_set_ewmh_atoms(void);
lemonbar_bar_t *lemonbar_make_bar(xcb_rectangle_t monitor_bounds, xcb_rectangle_t bar_bounds);
int lemonbar_rect_sort_cb(const void *p1, const void *p2);
xcb_visualid_t lemonbar_get_visual(void);
void lemonbar_xconnect(void);
void lemonbar_initialize(
  xcb_rectangle_t bar_rect, xcb_rectangle_t monitor_rect, const char *wm_name,
  bool topbar, bool dock, unsigned int areas, int lineheight,
  const char *bg, const char *fg, const char *linecolor,
  int border_top, int border_bottom, const char *border_top_color, const char *border_bottom_color);
void lemonbar_cleanup(void);

// new fn

xcb_connection_t *lemonbar_get_xconnection();
lemonbar_bar_t *lemonbar_get_bar();
xcb_gcontext_t *lemonbar_get_gc();
xcb_gcontext_t *lemonbar_get_border_gc();
lemonbar_rgba_t lemonbar_get_color_white();
lemonbar_rgba_t lemonbar_get_color_black();
lemonbar_rgba_t lemonbar_get_border_color();
void lemonbar_draw_borders();

#ifdef __cplusplus
}
#endif

#endif
