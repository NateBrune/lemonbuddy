#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>
#include <unistd.h>
#include <getopt.h>
#include <errno.h>
#include <xcb/xcb.h>
#include <xcb/xcbext.h>
#include <X11/Xft/Xft.h>
#include <X11/Xlib-xcb.h>

#include "lemonbar.h"

#define max(a,b) ((a) > (b) ? (a) : (b))
#define min(a,b) ((a) < (b) ? (a) : (b))
#define indexof(c,s) (strchr((s),(c))-(s))

#define MAX_g_font_count 8

static Display *g_display;
static xcb_connection_t *g_connection;
static xcb_screen_t *g_scr;
static int g_scr_n = 0;

static xcb_gcontext_t g_gc[GC_MAX];
static xcb_visualid_t g_visual;
static Visual *g_visual_ptr;
static xcb_colormap_t g_colormap;

static lemonbar_bar_t *g_bar;
static lemonbar_font_t *g_font_list[MAX_g_font_count];

static int g_font_count = 0;
static int g_font_index = -1;
static int g_offsets_y[MAX_g_font_count];
static int g_offset_y_index = 0;

static uint32_t g_attrs = 0;
static bool g_dock = false;
static bool g_topbar = true;

static int g_bw = -1, g_bh = -1, g_bx = 0, g_by = 0;
static int g_bu = 1; // Underline height
static int g_bordertop = 0;
static int g_borderbottom = 0;

// fg, bg, line, border
static lemonbar_rgba_t g_fgc, g_bgc, g_ugc, g_bcct, g_bccb;
static lemonbar_rgba_t g_dfgc, g_dbgc, g_dugc, g_dbcct, g_dbccb;

static lemonbar_area_stack_t g_area_stack;

static XftColor g_sel_fg;
static XftDraw *g_xft_draw;

#define MAX_WIDTHS (1 << 16)
static wchar_t g_xft_char[MAX_WIDTHS];
static char g_xft_width[MAX_WIDTHS];

enum {
  NET_WM_WINDOW_TYPE,
  NET_WM_WINDOW_TYPE_DOCK,
  NET_WM_DESKTOP,
  NET_WM_STRUT_PARTIAL,
  NET_WM_STRUT,
  NET_WM_STATE,
  NET_WM_STATE_STICKY,
  NET_WM_STATE_ABOVE,
};

void lemonbar_update_gc(void)
{
  xcb_change_gc(g_connection, g_gc[GC_DRAW], XCB_GC_FOREGROUND, (const uint32_t []){ g_fgc.v });
  xcb_change_gc(g_connection, g_gc[GC_CLEAR], XCB_GC_FOREGROUND, (const uint32_t []){ g_bgc.v });
  xcb_change_gc(g_connection, g_gc[GC_ATTR], XCB_GC_FOREGROUND, (const uint32_t []){ g_ugc.v });
  xcb_change_gc(g_connection, g_gc[GC_BORDERTOP], XCB_GC_FOREGROUND, (const uint32_t []){ g_bcct.v });
  xcb_change_gc(g_connection, g_gc[GC_BORDERBTM], XCB_GC_FOREGROUND, (const uint32_t []){ g_bccb.v });
  XftColorFree(g_display, g_visual_ptr, g_colormap , &g_sel_fg);
  char color[] = "#ffffff";
  uint32_t ng_fgc = g_fgc.v & 0x00ffffff;
  snprintf(color, sizeof(color), "#%06X", ng_fgc);
  if (!XftColorAllocName (g_display, g_visual_ptr, g_colormap, color, &g_sel_fg))
    fprintf(stderr, "Couldn't allocate xft font color '%s'\n", color);
}

// void lemonbar_fill_gradient(xcb_drawable_t d, int x, int width, lemonbar_rgba_t start, lemonbar_rgba_t stop)
// {
//   float i;
//   const int K = 25; // The number of steps
//
//   for (i = 0.; i < 1.; i += (1. / K)) {
//     // Perform the linear interpolation magic
//     unsigned int rr = i * stop.r + (1. - i) * start.r;
//     unsigned int gg = i * stop.g + (1. - i) * start.g;
//     unsigned int bb = i * stop.b + (1. - i) * start.b;
//
//     // The alpha is ignored here
//     lemonbar_rgba_t step = {
//       .r = rr,
//       .g = gg,
//       .b = bb,
//       .a = 255,
//     };
//
//     xcb_change_gc(g_connection, g_gc[GC_DRAW], XCB_GC_FOREGROUND, (const uint32_t []){ step.v });
//     xcb_poly_fill_rectangle(g_connection, d, g_gc[GC_DRAW], 1,
//         (const xcb_rectangle_t []){ { x, i * g_bh, width, g_bh / K + 1 } });
//   }
//
//   xcb_change_gc(g_connection, g_gc[GC_DRAW], XCB_GC_FOREGROUND, (const uint32_t []){ g_fgc.v });
// }

void lemonbar_fill_rect(xcb_drawable_t d, xcb_gcontext_t _gc, int x, int y, int width, int height)
{
  xcb_rectangle_t rect[1];
  rect[0].x = x;
  rect[0].y = y;
  rect[0].width = width;
  rect[0].height = height;
  xcb_poly_fill_rectangle(g_connection, d, _gc, 1, rect);
}

// Apparently xcb cannot seem to compose the right request for this call, hence we have to do it g_by
// ourselves.
// The funcion is taken from 'wmdia' (http://wmdia.sourceforge.net/)
xcb_void_cookie_t lemonbar_xcb_poly_text_16_simple(xcb_connection_t *g_connection,
    xcb_drawable_t drawable, xcb_gcontext_t gc, int16_t x, int16_t y,
    uint32_t len, const uint16_t *str)
{
  static const xcb_protocol_request_t xcb_req = {
    5,                // count
    0,                // ext
    XCB_POLY_TEXT_16, // opcode
    1                 // isvoid
  };
  struct iovec xcb_parts[7];
  uint8_t xcb_lendelta[2];
  xcb_void_cookie_t xcb_ret;
  xcb_poly_text_8_request_t xcb_out;

  xcb_out.pad0 = 0;
  xcb_out.drawable = drawable;
  xcb_out.gc = gc;
  xcb_out.x = x;
  xcb_out.y = y;

  xcb_lendelta[0] = len;
  xcb_lendelta[1] = 0;

  xcb_parts[2].iov_base = (char *)&xcb_out;
  xcb_parts[2].iov_len = sizeof(xcb_out);
  xcb_parts[3].iov_base = 0;
  xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

  xcb_parts[4].iov_base = xcb_lendelta;
  xcb_parts[4].iov_len = sizeof(xcb_lendelta);
  xcb_parts[5].iov_base = (char *)str;
  xcb_parts[5].iov_len = len * sizeof(int16_t);

  xcb_parts[6].iov_base = 0;
  xcb_parts[6].iov_len = -(xcb_parts[4].iov_len + xcb_parts[5].iov_len) & 3;

  xcb_ret.sequence = xcb_send_request(g_connection, 0, xcb_parts + 2, &xcb_req);

  return xcb_ret;
}


int lemonbar_g_xft_char_width_slot(uint16_t ch)
{
  int slot = ch % MAX_WIDTHS;
  while (g_xft_char[slot] != 0 && g_xft_char[slot] != ch)
  {
    slot = (slot + 1) % MAX_WIDTHS;
  }
  return slot;
}

int lemonbar_g_xft_char_width(uint16_t ch, lemonbar_font_t *cur_font)
{
  int slot = lemonbar_g_xft_char_width_slot(ch);
  if (!g_xft_char[slot]) {
    XGlyphInfo gi;
    FT_UInt glyph = XftCharIndex (g_display, cur_font->xft_ft, (FcChar32) ch);
    XftFontLoadGlyphs (g_display, cur_font->xft_ft, FcFalse, &glyph, 1);
    XftGlyphExtents (g_display, cur_font->xft_ft, &glyph, 1, &gi);
    XftFontUnloadGlyphs (g_display, cur_font->xft_ft, &glyph, 1);
    g_xft_char[slot] = ch;
    g_xft_width[slot] = gi.xOff;
    return gi.xOff;
  } else if (g_xft_char[slot] == ch)
    return g_xft_width[slot];
  else
    return 0;
}

int lemonbar_shift(int x, int align, int ch_width)
{
  switch (align) {
    case ALIGN_C:
      xcb_copy_area(g_connection,
        g_bar->pixmap, g_bar->pixmap, g_gc[GC_DRAW],
        g_bar->rect.width / 2 - x / 2, 0,
        g_bar->rect.width / 2 - (x + ch_width) / 2, 0,
        x, g_bh);
      x = g_bar->rect.width / 2 - (x + ch_width) / 2 + x;
      break;
    case ALIGN_R:
      xcb_copy_area(g_connection,
        g_bar->pixmap, g_bar->pixmap, g_gc[GC_DRAW],
        g_bar->rect.width - x, 0,
        g_bar->rect.width - x - ch_width, 0,
        x, g_bh);
      x = g_bar->rect.width - ch_width;
      break;
  }

  // Draw the background first
  lemonbar_fill_rect(g_bar->pixmap, g_gc[GC_CLEAR], x, 0, ch_width, g_bh);
  return x;
}

void lemonbar_draw_lines(int x, int w)
{
  /* We can render both at the same time */
  if (g_attrs & ATTR_OVERL)
    lemonbar_fill_rect(g_bar->pixmap, g_gc[GC_ATTR], x, g_bordertop, w, g_bu);
  if (g_attrs & ATTR_UNDERL)
    lemonbar_fill_rect(g_bar->pixmap, g_gc[GC_ATTR], x, g_bh - g_bu - g_borderbottom, w, g_bu);
}

void lemonbar_draw_shift(int x, int align, int w)
{
  x = lemonbar_shift(x, align, w);
  lemonbar_draw_lines(x, w);
}

int lemonbar_draw_char(lemonbar_font_t *cur_font, int x, int align, uint16_t ch)
{
  int ch_width;

  if (cur_font->xft_ft) {
    ch_width = lemonbar_g_xft_char_width(ch, cur_font);
  } else {
    ch_width = (cur_font->width_lut) ?
      cur_font->width_lut[ch - cur_font->char_min].character_width:
      cur_font->width;
  }

  x = lemonbar_shift(x, align, ch_width);

  int y = g_bh / 2 + cur_font->height / 2- cur_font->descent + g_offsets_y[g_offset_y_index];
  if (cur_font->xft_ft) {
    XftDrawString16 (g_xft_draw, &g_sel_fg, cur_font->xft_ft, x,y, &ch, 1);
  } else {
    /* xcb accepts string in UCS-2 BE, so swap */
    ch = (ch >> 8) | (ch << 8);

    // The coordinates here are those of the baseline
    lemonbar_xcb_poly_text_16_simple(g_connection, g_bar->pixmap, g_gc[GC_DRAW],
        x, y,
        1, &ch);
  }

  lemonbar_draw_lines(x, ch_width);

  return ch_width;
}

lemonbar_rgba_t lemonbar_parse_color(const char *str, char **end, const lemonbar_rgba_t def)
{
  int string_len;
  char *ep;

  if (!str)
    return def;

  // Reset
  if (str[0] == '-') {
    if (end)
      *end = (char *)str + 1;

    return def;
  }

  // Hex representation
  if (str[0] != '#') {
    if (end)
      *end = (char *)str;

    fprintf(stderr, "Invalid color specified\n");
    return def;
  }

  errno = 0;
  lemonbar_rgba_t tmp = (lemonbar_rgba_t)(uint32_t)strtoul(str + 1, &ep, 16);

  if (end)
    *end = ep;

  // Some error checking is definitely good
  if (errno) {
    fprintf(stderr, "Invalid color specified\n");
    return def;
  }

  string_len = ep - (str + 1);

  switch (string_len) {
    case 3:
      // Expand the #rgb format into #rrggbb (aa is set to 0xff)
      tmp.v = (tmp.v & 0xf00) * 0x1100
        | (tmp.v & 0x0f0) * 0x0110
        | (tmp.v & 0x00f) * 0x0011;
    case 6:
      // If the code is in #rrggbb form then assume it's opaque
      tmp.a = 255;
      break;
    case 7:
    case 8:
      // Colors in #aarrggbb format, those need no adjustments
      break;
    default:
      fprintf(stderr, "Invalid color specified\n");
      return def;
  }

  if (!tmp.a)
    return (lemonbar_rgba_t) 0U;

  // The components are clamped automagically as the lemonbar_rgba_t is made of uint8_t
  return (lemonbar_rgba_t){
    .r = (tmp.r * tmp.a) / 255,
    .g = (tmp.g * tmp.a) / 255,
    .b = (tmp.b * tmp.a) / 255,
    .a = tmp.a,
  };
}

void lemonbar_set_attrig_bute(const char modifier, const char attrig_bute)
{
  int pos = indexof(attrig_bute, "ou");

  if (pos < 0) {
    fprintf(stderr, "Invalid attrig_bute \"%c\" found\n", attrig_bute);
    return;
  }

  switch (modifier) {
    case '+':
      g_attrs |= (1u<<pos);
      break;
    case '-':
      g_attrs &=~(1u<<pos);
      break;
    case '!':
      g_attrs ^= (1u<<pos);
      break;
  }
}

lemonbar_area_t *lemonbar_area_get(xcb_window_t win, const int btn, const int x)
{
  // Looping backwards ensures that we get the innermost area first
  for (int i = g_area_stack.at - 1; i >= 0; i--) {
    lemonbar_area_t *a = &g_area_stack.area[i];
    if (a->window == win && a->button == btn && x >= a->begin && x < a->end)
      return a;
  }
  return NULL;
}

void lemonbar_area_shift(xcb_window_t win, const int align, int delta)
{
  if (align == ALIGN_L)
    return;
  if (align == ALIGN_C)
    delta /= 2;

  for (int i = 0; i < g_area_stack.at; i++) {
    lemonbar_area_t *a = &g_area_stack.area[i];
    if (a->window == win && a->align == align && !a->active) {
      a->begin -= delta;
      a->end -= delta;
    }
  }
}

bool lemonbar_area_add(char *str, const char *optend, char **end, const int x, const int align, const int button)
{
  int i;
  char *trail;
  lemonbar_area_t *a;

  // A wild close area tag appeared!
  if (*str != ':') {
    *end = str;

    // Find most recent unclosed area.
    for (i = g_area_stack.at - 1; i >= 0 && !g_area_stack.area[i].active; i--)
      ;
    a = &g_area_stack.area[i];

    // Basic safety checks
    if (!a->cmd || a->align != align || a->window != g_bar->window) {
      fprintf(stderr, "Invalid geometry for the clickable area\n");
      return false;
    }

    const int size = x - a->begin;

    switch (align) {
      case ALIGN_L:
        a->end = x;
        break;
      case ALIGN_C:
        a->begin = g_bar->rect.width / 2 - size / 2 + a->begin / 2;
        a->end = a->begin + size;
        break;
      case ALIGN_R:
        // The newest is the rightmost one
        a->begin = g_bar->rect.width - size;
        a->end = g_bar->rect.width;
        break;
    }

    a->active = false;
    return true;
  }

  if ((unsigned int) g_area_stack.at + 1 > g_area_stack.max) {
    fprintf(stderr, "Cannot add any more clickable areas (used %d/%d)\n",
        g_area_stack.at, g_area_stack.max);
    return false;
  }
  a = &g_area_stack.area[g_area_stack.at++];

  // Found the closing : and check if it's just an escaped one
  for (trail = strchr(++str, ':'); trail && trail[-1] == '\\'; trail = strchr(trail + 1, ':'))
    ;

  // Find the trailing : and make sure it's within the formatting block, also reject empty commands
  if (!trail || str == trail || trail > optend) {
    *end = str;
    return false;
  }

  *trail = '\0';

  // Sanitize the user command g_by unescaping all the :
  for (char *needle = str; *needle; needle++) {
    int delta = trail - &needle[1];
    if (needle[0] == '\\' && needle[1] == ':') {
      memmove(&needle[0], &needle[1], delta);
      needle[delta] = 0;
    }
  }

  // This is a pointer to the string g_buffer allocated in the main
  a->cmd = str;
  a->active = true;
  a->align = align;
  a->begin = x;
  a->window = g_bar->window;
  a->button = button;

  *end = trail + 1;

  return true;
}

bool lemonbar_font_has_glyph(lemonbar_font_t *font, const uint16_t c)
{
  if (font->xft_ft) {
    if (XftCharExists(g_display, font->xft_ft, (FcChar32) c)) {
      return true;
    } else {
      return false;
    }

  }

  if (c < font->char_min || c > font->char_max)
    return false;

  if (font->width_lut && font->width_lut[c - font->char_min].character_width == 0)
    return false;

  return true;
}

lemonbar_font_t *lemonbar_select_drawable_font(const uint16_t c)
{
  // If the user has specified a font to use, try that first.
  if (g_font_index != -1 && lemonbar_font_has_glyph(g_font_list[g_font_index - 1], c)) {
    g_offset_y_index = g_font_index - 1;
    return g_font_list[g_font_index - 1];
  }

  // If the end is reached without finding an appropriate font, return NULL.
  // If the font can draw the character, return it.
  for (int i = 0; i < g_font_count; i++) {
    if (lemonbar_font_has_glyph(g_font_list[i], c)) {
      g_offset_y_index = i;
      return g_font_list[i];
    }
  }
  return NULL;
}


void lemonbar_parse_data(const char *text)
{
  lemonbar_font_t *cur_font;
  int pos_x, align, button;
  char *p = (char *) text, *block_end, *ep;
  lemonbar_rgba_t tmp;

  pos_x = 0;
  align = ALIGN_L;

  // Reset the stack position
  g_area_stack.at = 0;

  lemonbar_fill_rect(g_bar->pixmap, g_gc[GC_CLEAR], 0, 0, g_bar->rect.width, g_bh);

  /* Create xft drawable */
  if (!(g_xft_draw = XftDrawCreate (g_display, g_bar->pixmap, g_visual_ptr , g_colormap))) {
    fprintf(stderr, "Couldn't create xft drawable\n");
  }

  for (;;) {
    if (*p == '\0' || *p == '\n')
      break;

    if (p[0] == '%' && p[1] == '{' && (block_end = strchr(p++, '}'))) {
      p++;
      while (p < block_end) {
        int w;

        while (isspace(*p))
          p++;

        switch (*p++) {
          case '+': lemonbar_set_attrig_bute('+', *p++); break;
          case '-': lemonbar_set_attrig_bute('-', *p++); break;
          case '!': lemonbar_set_attrig_bute('!', *p++); break;

          case 'R':
            tmp = g_fgc;
            g_fgc = g_bgc;
            g_bgc = tmp;
            lemonbar_update_gc();
            break;

          case 'l': pos_x = 0; align = ALIGN_L; break;
          case 'c': pos_x = 0; align = ALIGN_C; break;
          case 'r': pos_x = 0; align = ALIGN_R; break;

          case 'A':
            button = XCB_BUTTON_INDEX_1;
            // The range is 1-5
            if (isdigit(*p) && (*p > '0' && *p < '6'))
              button = *p++ - '0';
            if (!lemonbar_area_add(p, block_end, &p, pos_x, align, button))
              return;
            break;

          case 'B': g_bgc = lemonbar_parse_color(p, &p, g_dbgc); lemonbar_update_gc(); break;
          case 'F': g_fgc = lemonbar_parse_color(p, &p, g_dfgc); lemonbar_update_gc(); break;
          case 'U': g_ugc = lemonbar_parse_color(p, &p, g_dugc); lemonbar_update_gc(); break;

          case 'O':
            errno = 0;
            w = (int) strtoul(p, &p, 10);
            if (errno)
              continue;

            lemonbar_draw_shift(pos_x, align, w);
            pos_x += w;
            lemonbar_area_shift(g_bar->window, align, w);
            break;

          case 'T':
            if (*p == '-') { //Reset to automatic font selection
              g_font_index = -1;
              p++;
              break;
            } else if (isdigit(*p)) {
              g_font_index = (int)strtoul(p, &ep, 10);
              // User-specified 'g_font_index' ∊ (0,g_font_count]
              // Otherwise just fallback to the automatic font selection
              if (!g_font_index || g_font_index > g_font_count)
                g_font_index = -1;
              p = ep;
              break;
            } else {
              fprintf(stderr, "Invalid font slot \"%c\"\n", *p++); //Swallow the token
              break;
            }

            // In case of error keep parsing after the closing }
          default:
            p = block_end;
        }
      }
      p++;
    } else {
      // utf-8 -> ucs-2
      uint8_t *utf = (uint8_t *)p;
      uint16_t ucs;

      // ASCII
      if (utf[0] < 0x80) {
        ucs = utf[0];
        p  += 1;
      }
      // Two g_byte utf8 sequence
      else if ((utf[0] & 0xe0) == 0xc0) {
        ucs = (utf[0] & 0x1f) << 6 | (utf[1] & 0x3f);
        p += 2;
      }
      // Three g_byte utf8 sequence
      else if ((utf[0] & 0xf0) == 0xe0) {
        ucs = (utf[0] & 0xf) << 12 | (utf[1] & 0x3f) << 6 | (utf[2] & 0x3f);
        p += 3;
      }
      // Four g_byte utf8 sequence
      else if ((utf[0] & 0xf8) == 0xf0) {
        ucs = 0xfffd;
        p += 4;
      }
      // Five g_byte utf8 sequence
      else if ((utf[0] & 0xfc) == 0xf8) {
        ucs = 0xfffd;
        p += 5;
      }
      // Six g_byte utf8 sequence
      else if ((utf[0] & 0xfe) == 0xfc) {
        ucs = 0xfffd;
        p += 6;
      }
      // Not a valid utf-8 sequence
      else {
        ucs = utf[0];
        p += 1;
      }

      cur_font = lemonbar_select_drawable_font(ucs);

      if (!cur_font)
        continue;

      if(cur_font->ptr)
        xcb_change_gc(g_connection, g_gc[GC_DRAW] , XCB_GC_FONT, (const uint32_t []) {
          cur_font->ptr
        });

      int w = lemonbar_draw_char(cur_font, pos_x, align, ucs);

      pos_x += w;

      lemonbar_area_shift(g_bar->window, align, w);
    }
  }
  XftDrawDestroy (g_xft_draw);
}

void lemonbar_font_load(const char *pattern, int offset_y)
{
  if (g_font_count >= MAX_g_font_count) {
    fprintf(stderr, "Max font count reached. Could not load font \"%s\"\n", pattern);
    exit(EXIT_FAILURE);
  }

  xcb_font_t font = xcb_generate_id(g_connection);
  lemonbar_font_t *ret = (lemonbar_font_t *) calloc(1, sizeof(lemonbar_font_t));

  if (!ret)
    return;

  xcb_void_cookie_t cookie = xcb_open_font_checked(g_connection, font, strlen(pattern), pattern);

  if (!xcb_request_check (g_connection, cookie)) {
    xcb_query_font_cookie_t queryreq = xcb_query_font(g_connection, font);
    xcb_query_font_reply_t *font_info = xcb_query_font_reply(g_connection, queryreq, NULL);

    ret->xft_ft = NULL;
    ret->ptr = font;
    ret->descent = font_info->font_descent;
    ret->height = font_info->font_ascent + font_info->font_descent;
    ret->width = font_info->max_bounds.character_width;
    ret->char_max = font_info->max_byte1 << 8 | font_info->max_char_or_byte2;
    ret->char_min = font_info->min_byte1 << 8 | font_info->min_char_or_byte2;

    // Copy over the width lut as it's part of font_info
    int lut_size = sizeof(xcb_charinfo_t) * xcb_query_font_char_infos_length(font_info);
    if (lut_size) {
      ret->width_lut = (xcb_charinfo_t *) malloc(lut_size);
      memcpy(ret->width_lut, xcb_query_font_char_infos(font_info), lut_size);
    }

    free(font_info);
  } else if ((ret->xft_ft = XftFontOpenName(g_display, g_scr_n, pattern))) {
    ret->ptr = 0;
    ret->ascent = ret->xft_ft->ascent;
    ret->descent = ret->xft_ft->descent;
    ret->height = ret->ascent + ret->descent;
  } else {
    fprintf(stderr, "Could not load font %s\n", pattern);
    free(ret);
    return;
  }

  g_font_list[g_font_count++] = ret;
  g_offsets_y[g_font_count-1] = offset_y;
}

void lemonbar_set_ewmh_atoms(void)
{
  const char *atom_names[] = {
    "_NET_WM_WINDOW_TYPE",
    "_NET_WM_WINDOW_TYPE_DOCK",
    "_NET_WM_DESKTOP",
    "_NET_WM_STRUT_PARTIAL",
    "_NET_WM_STRUT",
    "_NET_WM_STATE",
    // Leave those at the end since are batch-set
    "_NET_WM_STATE_STICKY",
    "_NET_WM_STATE_ABOVE",
  };
  const int atoms = sizeof(atom_names)/sizeof(char *);
  xcb_intern_atom_cookie_t atom_cookie[atoms];
  xcb_atom_t atom_list[atoms];
  xcb_intern_atom_reply_t *atom_reply;

  // As suggested fetch all the cookies first (yum!) and then retrieve the
  // atoms to exploit the async'ness
  for (int i = 0; i < atoms; i++)
    atom_cookie[i] = xcb_intern_atom(g_connection, 0, strlen(atom_names[i]), atom_names[i]);

  for (int i = 0; i < atoms; i++) {
    atom_reply = xcb_intern_atom_reply(g_connection, atom_cookie[i], NULL);
    if (!atom_reply)
      return;
    atom_list[i] = atom_reply->atom;
    free(atom_reply);
  }

  // Prepare the strut array
  int strut[12] = {0};
  if (g_topbar) {
    strut[2] = g_bh;
    strut[8] = g_bar->rect.x;
    strut[9] = g_bar->rect.x + g_bar->rect.width;
  } else {
    strut[3]  = g_bh;
    strut[10] = g_bar->rect.x;
    strut[11] = g_bar->rect.x + g_bar->rect.width;
  }

  xcb_change_property(g_connection, XCB_PROP_MODE_REPLACE, g_bar->window, atom_list[NET_WM_WINDOW_TYPE], XCB_ATOM_ATOM, 32, 1, &atom_list[NET_WM_WINDOW_TYPE_DOCK]);
  xcb_change_property(g_connection, XCB_PROP_MODE_APPEND,  g_bar->window, atom_list[NET_WM_STATE], XCB_ATOM_ATOM, 32, 2, &atom_list[NET_WM_STATE_STICKY]);
  xcb_change_property(g_connection, XCB_PROP_MODE_REPLACE, g_bar->window, atom_list[NET_WM_DESKTOP], XCB_ATOM_CARDINAL, 32, 1, (const uint32_t[]){ 0u - 1u });
  xcb_change_property(g_connection, XCB_PROP_MODE_REPLACE, g_bar->window, atom_list[NET_WM_STRUT_PARTIAL], XCB_ATOM_CARDINAL, 32, 12, strut);
  xcb_change_property(g_connection, XCB_PROP_MODE_REPLACE, g_bar->window, atom_list[NET_WM_STRUT], XCB_ATOM_CARDINAL, 32, 4, strut);
  xcb_change_property(g_connection, XCB_PROP_MODE_REPLACE, g_bar->window, XCB_ATOM_WM_NAME, XCB_ATOM_STRING, 8, 3, "lemonbar");
}

lemonbar_bar_t *lemonbar_make_bar(xcb_rectangle_t monitor_bounds, xcb_rectangle_t bar_bounds)
{
  lemonbar_bar_t *obj = (lemonbar_bar_t *) calloc(1, sizeof(lemonbar_bar_t));

  if (!obj) {
    fprintf(stderr, "Failed to allocate bar memory\n");
    exit(EXIT_FAILURE);
  }

  obj->rect = monitor_bounds;
  obj->rect.x += bar_bounds.x;
  obj->rect.y += (g_topbar ? 0 : obj->rect.height - g_bh - g_by) + bar_bounds.y;
  obj->rect.width = bar_bounds.width;
  obj->rect.height = bar_bounds.height;

  obj->window = xcb_generate_id(g_connection);

  uint8_t depth = (g_visual == g_scr->root_visual) ? XCB_COPY_FROM_PARENT : 32;

  xcb_create_window(
    g_connection, depth, obj->window, g_scr->root,
    obj->rect.x, obj->rect.y, bar_bounds.width, bar_bounds.height, 0,
    XCB_WINDOW_CLASS_INPUT_OUTPUT, g_visual,
    XCB_CW_BACK_PIXEL | XCB_CW_BORDER_PIXEL | XCB_CW_OVERRIDE_REDIRECT | XCB_CW_EVENT_MASK | XCB_CW_COLORMAP,
    (const uint32_t[]){
      g_bgc.v,
      g_bgc.v,
      g_dock,
      XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_BUTTON_PRESS,
      g_colormap
    });

  obj->pixmap = xcb_generate_id(g_connection);

  xcb_create_pixmap(g_connection, depth, obj->pixmap, obj->window, obj->rect.width, obj->rect.height);

  return obj;
}

int lemonbar_rect_sort_cb(const void *p1, const void *p2)
{
  const xcb_rectangle_t *r1 = (xcb_rectangle_t *)p1;
  const xcb_rectangle_t *r2 = (xcb_rectangle_t *)p2;

  if (r1->x < r2->x || r1->y + r1->height <= r2->y) {
    return -1;
  }

  if (r1->x > r2->x || r1->y + r1->height > r2->y) {
    return 1;
  }

  return 0;
}

xcb_visualid_t lemonbar_get_visual(void)
{
  XVisualInfo xv;
  xv.depth = 32;
  int result = 0;
  XVisualInfo* result_ptr = NULL;
  result_ptr = XGetVisualInfo(g_display, VisualDepthMask, &xv, &result);

  if (result > 0) {
    g_visual_ptr = result_ptr->visual;
    return result_ptr->visualid;
  }

  //Fallback
  g_visual_ptr = DefaultVisual(g_display, g_scr_n);
  return g_scr->root_visual;
}

void lemonbar_xconnect(void)
{
  if ((g_display = XOpenDisplay(0)) == NULL) {
    fprintf(stderr, "Couldnt open display\n");
    exit (EXIT_FAILURE);
  }

  if ((g_connection = XGetXCBConnection(g_display)) == NULL) {
    fprintf(stderr, "Couldnt connect to X\n");
    exit (EXIT_FAILURE);
  }

  XSetEventQueueOwner(g_display, XCBOwnsEventQueue);

  if (xcb_connection_has_error(g_connection)) {
    fprintf(stderr, "Couldn't connect to X\n");
    exit(EXIT_FAILURE);
  }

  /* Grab infos from the first screen */
  g_scr = xcb_setup_roots_iterator(xcb_get_setup(g_connection)).data;

  /* Try to get a RGBA visual and g_build the g_colormap for that */
  g_visual = lemonbar_get_visual();
  g_colormap = xcb_generate_id(g_connection);
  xcb_create_colormap(g_connection, XCB_COLORMAP_ALLOC_NONE, g_colormap, g_scr->root, g_visual);
}

void lemonbar_initialize(
  xcb_rectangle_t bar_rect, xcb_rectangle_t monitor_rect, const char *wm_name,
  bool top, bool dock, unsigned int areas, int lineheight,
  const char *bg, const char *fg, const char *linecolor,
  int border_top, int border_bottom, const char *border_top_color, const char *border_bottom_color)
{
  g_topbar = top;
  g_dock = dock;

  g_dbgc = g_bgc = lemonbar_parse_color(bg, NULL, (lemonbar_rgba_t) 0x00000000U);
  g_dfgc = g_fgc = lemonbar_parse_color(fg, NULL, (lemonbar_rgba_t) 0xffffffffU);
  g_dugc = g_ugc = lemonbar_parse_color(linecolor, NULL, g_fgc);
  g_dbcct = g_bcct = lemonbar_parse_color(border_top_color, NULL, (lemonbar_rgba_t) 0x00000000U);
  g_dbccb = g_bccb = lemonbar_parse_color(border_bottom_color, NULL, (lemonbar_rgba_t) 0x00000000U);

  g_bw = bar_rect.width;
  g_bh = bar_rect.height;
  g_bx = bar_rect.x;
  g_by = bar_rect.y;

  g_bu = lineheight;

  g_bordertop = border_top;
  g_borderbottom = border_bottom;

  // Initialize the stack holding the clickable areas
  g_area_stack.at = 0;
  g_area_stack.max = areas;
  g_area_stack.area = (lemonbar_area_t *) calloc(areas, sizeof(lemonbar_area_t));

  if (!g_area_stack.area) {
    fprintf(stderr, "Could not allocate enough memory for %d clickable areas, try lowering the number\n", areas);
    exit(EXIT_FAILURE);
  }

  // Try to load a default font
  if (!g_font_count) {
    fprintf(stderr, "No fonts loaded, using default \"fixed\"\n");
    lemonbar_font_load("fixed", 0);
  }

  // We tried and failed hard, there's something wrong
  if (!g_font_count) {
    fprintf(stderr, "No fonts loaded, exitting...\n");
    exit(EXIT_FAILURE);
  }

  // To make the alignment uniform, find maximum height
  int maxh = g_font_list[0]->height;
  for (int i = 1; i < g_font_count; i++)
    maxh = max(maxh, g_font_list[i]->height);

  // Set maximum height to all fonts
  for (int i = 0; i < g_font_count; i++)
    g_font_list[i]->height = maxh;

  // Initialize monitor
  g_bar = lemonbar_make_bar(monitor_rect, bar_rect);

  // For WM that support EWMH atoms
  lemonbar_set_ewmh_atoms();

  // Create the gc for drawing
  g_gc[GC_DRAW] = xcb_generate_id(g_connection);
  xcb_create_gc(g_connection, g_gc[GC_DRAW], g_bar->pixmap, XCB_GC_FOREGROUND, (const uint32_t []){ g_fgc.v });

  g_gc[GC_CLEAR] = xcb_generate_id(g_connection);
  xcb_create_gc(g_connection, g_gc[GC_CLEAR], g_bar->pixmap, XCB_GC_FOREGROUND, (const uint32_t []){ g_bgc.v });

  g_gc[GC_ATTR] = xcb_generate_id(g_connection);
  xcb_create_gc(g_connection, g_gc[GC_ATTR], g_bar->pixmap, XCB_GC_FOREGROUND, (const uint32_t []){ g_ugc.v });

  g_gc[GC_BORDERTOP] = xcb_generate_id(g_connection);
  xcb_create_gc(g_connection, g_gc[GC_BORDERTOP], g_bar->pixmap, XCB_GC_FOREGROUND, (const uint32_t []){ g_bcct.v });

  g_gc[GC_BORDERBTM] = xcb_generate_id(g_connection);
  xcb_create_gc(g_connection, g_gc[GC_BORDERBTM], g_bar->pixmap, XCB_GC_FOREGROUND, (const uint32_t []){ g_bccb.v });

  // Make the bar visible and clear the pixmap
  lemonbar_fill_rect(g_bar->pixmap, g_gc[GC_CLEAR], 0, 0, g_bar->rect.width, g_bh);
  xcb_map_window(g_connection, g_bar->window);

  // Make sure that the window really gets in the place it's supposed to be
  // Some WM such as Openbox need this
  xcb_configure_window(g_connection, g_bar->window, XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y, (const uint32_t []){ g_bar->rect.x, g_bar->rect.y });

  // Set the WM_NAME atom to the user specified value
  if (wm_name)
    xcb_change_property(g_connection, XCB_PROP_MODE_REPLACE, g_bar->window, XCB_ATOM_WM_NAME, XCB_ATOM_STRING, 8, strlen(wm_name), wm_name);

  char color[] = "#ffffff";
  uint32_t ng_fgc = g_fgc.v & 0x00ffffff;
  snprintf(color, sizeof(color), "#%06X", ng_fgc);

  if (!XftColorAllocName (g_display, g_visual_ptr, g_colormap, color, &g_sel_fg)) {
    fprintf(stderr, "Couldn't allocate xft font color '%s'\n", color);
  }
  xcb_flush(g_connection);
}

void lemonbar_cleanup(void)
{
  free(g_area_stack.area);

  for (int i = 0; i < g_font_count; i++) {
    if (g_font_list[i]->xft_ft) {
      XftFontClose (g_display, g_font_list[i]->xft_ft);
    } else {
      xcb_close_font(g_connection, g_font_list[i]->ptr);
      free(g_font_list[i]->width_lut);
    }
    free(g_font_list[i]);
  }

  if (g_bar) {
    xcb_destroy_window(g_connection, g_bar->window);
    xcb_free_pixmap(g_connection, g_bar->pixmap);
    free(g_bar);
  }

  XftColorFree(g_display, g_visual_ptr, g_colormap, &g_sel_fg);

  if (g_gc[GC_DRAW])
    xcb_free_gc(g_connection, g_gc[GC_DRAW]);
  if (g_gc[GC_CLEAR])
    xcb_free_gc(g_connection, g_gc[GC_CLEAR]);
  if (g_gc[GC_ATTR])
    xcb_free_gc(g_connection, g_gc[GC_ATTR]);
  if (g_gc[GC_BORDERTOP])
    xcb_free_gc(g_connection, g_gc[GC_BORDERTOP]);
  if (g_gc[GC_BORDERBTM])
    xcb_free_gc(g_connection, g_gc[GC_BORDERBTM]);
  if (g_connection)
    xcb_disconnect(g_connection);
}

// new fn

xcb_connection_t *lemonbar_get_xconnection() {
  return g_connection;
}

lemonbar_bar_t *lemonbar_get_bar() {
  return g_bar;
}

xcb_gcontext_t *lemonbar_get_gc() {
  return g_gc;
}

lemonbar_rgba_t lemonbar_get_color_white() {
  return (lemonbar_rgba_t) 0xffffffffU;
}

lemonbar_rgba_t lemonbar_get_color_black() {
  return (lemonbar_rgba_t) 0x00000000U;
}

void lemonbar_draw_borders()
{
  lemonbar_fill_rect(g_bar->pixmap, g_gc[GC_BORDERTOP], 0, 0, g_bar->rect.width, g_bordertop);
  lemonbar_fill_rect(g_bar->pixmap, g_gc[GC_BORDERBTM], 0, g_bh-g_borderbottom, g_bar->rect.width, g_borderbottom);
}
