/*
 .-.               .---.              _______                                   .-.  
/_/ \              |   |              \  ___ `'.   .--.                        / \_\
\ \  \             |   |.-.          .-' |--.\  \  |__|                       /  / / 
 \ \  \            |   | \ \        / /| |    \  ' .--.                      /  / /  
  \ \  \           |   |  \ \      / / | |     |  '|  |    __               /  / /   
   >->  `          |   |   \ \    / /  | |     |  ||  | .:--.'.            '  <-<    
  / /  /           |   |    \ \  / /   | |     ' .'|  |/ |   \ |            \  \ \
 / /  /            |   |     \ `  /    | |___.' /' |  |`" __ | |             \  \ \
/_/  /             |   |      \  /    /_______.'/  |__| .'.''| |              \  \_\
\ \ /              '---'      / /     \_______|/       / /   | |_              \ / / 
 `-`                      |`-' /                       \ \._,\ '/               '-'  
                           '..'                         `--'  `"                     
a small header file for creating games i guess, uses sdl for the backend to render arrays to the screen
i know its not really much but its just a fun experiment for me

big todo:
 - time ticks(custom adjustable tick) 
 - mouse input
*/

// since this "framework"(idk how to call it) uses a bunch of macros
// to define preferences like LYDIA_TYPEDEFS, i reccoment defining this
// preferences at the top of the header file so that whenvever you include it
// you will always have the preferences
// es:
// #define LYDIA_TYPEDEFS
// #defien LYDIA_REMOVE_PREFIX

#ifndef LYDIA_H
#define LYDIA_H

//include shit
#include <inttypes.h>
#include <stdbool.h>

// small aliases for common types
// optional to use but reccomended by me :)
#define LYDIA_TYPEDEFS // TODO REMOVE AFTER
#ifdef LYDIA_TYPEDEFS // you can use the typedefs by calling #define LYDIA_TYPEDEFS
                      // before including the header file
typedef uint8_t   u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t    i8;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;

typedef float    f32;
typedef double   f64;

typedef size_t usize;
#endif

//vec2 types
typedef struct { f32 x, y; } lyd_vec2f;
typedef struct { i32 x, y; } lyd_vec2i;
typedef struct { u32 x, y; } lyd_vec2u;
//vec2 is by default a vec2f
typedef lyd_vec2f lyd_vec2;

#define LYD_VEC2TOU(V) (lyd_vec2u){(u32)V.x, (u32)V.y}
#define LYD_VEC2TOI(V) (lyd_vec2i){(i32)V.x, (i32)V.y}
#define LYD_VEC2TOF(V) (lyd_vec2f){(f32)V.x, (f32)V.y}

//general stuff
void lyd_init(u32 buffer_w, u32 buffer_h, u32 window_w, u32 window_h, char *title);
void lyd_initx(u32 buffer_w, u32 buffer_h, u32 window_w, u32 window_h, char *title, f32 frame_rate, bool resizable, bool border);
void lyd_quit(void);
bool lyd_get_running(void);
void lyd_stop_running(void);

void lyd_update(void);
void lyd_update_late(void);

//render stuff
typedef u32 lyd_Color; // colors are represented by u32
                   // they use the AARRGGBB format
#define LYD_COLOR_WHITE     0xffffffff
#define LYD_COLOR_BLACK     0xff000000
#define LYD_COLOR_RED       0xffff0000
#define LYD_COLOR_GREEN     0xff00ff00
#define LYD_COLOR_BLUE      0xff0000ff
#define LYD_COLOR_MAGENTA   0xffff00ff
#define LYD_COLOR_YELLOW    0xffffff00
#define LYD_COLOR_TURQUOISE 0xff00ffff

lyd_Color color_pack(u8 a, u8 r, u8 g, u8 b);
void color_unpack(lyd_Color color, u8 *a, u8 *r, u8*g, u8*b);

typedef struct {
  lyd_vec2u size;
  lyd_Color *data;
} lyd_Texture;

lyd_Texture lyd_texture_load(char *path);
lyd_Texture lyd_texture_copy(lyd_Texture texture);
void lyd_texture_replace_color(lyd_Texture t, lyd_Color from, lyd_Color to);
void lyd_texture_flipx(lyd_Texture t);
void lyd_texture_flipy(lyd_Texture t);
void lyd_texture_cut(lyd_Texture *t, lyd_vec2 pos, lyd_vec2 size);
void lyd_texture_free(lyd_Texture texture);

typedef enum {
  LYD_BLEND_NONE,
  LYD_BLEND_NORMAL,
  LYD_BLEND_ADDITIVE,
  LYD_BLEND_SUBTRACTIVE,
  LYD_BLEND_MULTIPLY,
  LYD_BLEND_SCREEN,
  LYD_BLEND_DARKEN,
  LYD_BLEND_LIGHTEN
} lyd_BlendMode;

void lyd_change_target(lyd_Texture *target); //leave null for the buffer
void lyd_clear(lyd_Color c);
void lyd_change_blending(lyd_BlendMode mode);
f32 lyd_time_delta(void);
f32 lyd_time_elapsed(void);

void lyd_render_pixel(lyd_vec2 pos, lyd_Color color);
void lyd_render_rect(lyd_vec2 pos, lyd_vec2 size, lyd_Color color);
void lyd_render_texture(lyd_vec2 pos, lyd_Texture texture);
void lyd_render_line(lyd_vec2 start, lyd_vec2 end, lyd_Color color);

//input stuff
typedef enum {
    LYD_KEY_UNKNOWN = 0,

    // Letters
    LYD_KEY_A = 4,
    LYD_KEY_B = 5,
    LYD_KEY_C = 6,
    LYD_KEY_D = 7,
    LYD_KEY_E = 8,
    LYD_KEY_F = 9,
    LYD_KEY_G = 10,
    LYD_KEY_H = 11,
    LYD_KEY_I = 12,
    LYD_KEY_J = 13,
    LYD_KEY_K = 14,
    LYD_KEY_L = 15,
    LYD_KEY_M = 16,
    LYD_KEY_N = 17,
    LYD_KEY_O = 18,
    LYD_KEY_P = 19,
    LYD_KEY_Q = 20,
    LYD_KEY_R = 21,
    LYD_KEY_S = 22,
    LYD_KEY_T = 23,
    LYD_KEY_U = 24,
    LYD_KEY_V = 25,
    LYD_KEY_W = 26,
    LYD_KEY_X = 27,
    LYD_KEY_Y = 28,
    LYD_KEY_Z = 29,

    // Numbers
    LYD_KEY_1 = 30,
    LYD_KEY_2 = 31,
    LYD_KEY_3 = 32,
    LYD_KEY_4 = 33,
    LYD_KEY_5 = 34,
    LYD_KEY_6 = 35,
    LYD_KEY_7 = 36,
    LYD_KEY_8 = 37,
    LYD_KEY_9 = 38,
    LYD_KEY_0 = 39,

    // Symbols
    LYD_KEY_RETURN = 40,
    LYD_KEY_ESCAPE = 41,
    LYD_KEY_BACKSPACE = 42,
    LYD_KEY_TAB = 43,
    LYD_KEY_SPACE = 44,
    LYD_KEY_MINUS = 45,
    LYD_KEY_EQUALS = 46,
    LYD_KEY_LEFTBRACKET = 47,
    LYD_KEY_RIGHTBRACKET = 48,
    LYD_KEY_BACKSLASH = 49,
    LYD_KEY_NONUSHASH = 50,
    LYD_KEY_SEMICOLON = 51,
    LYD_KEY_APOSTROPHE = 52,
    LYD_KEY_GRAVE = 53,
    LYD_KEY_COMMA = 54,
    LYD_KEY_PERIOD = 55,
    LYD_KEY_SLASH = 56,
    
    // Function Keys
    LYD_KEY_F1 = 58,
    LYD_KEY_F2 = 59,
    LYD_KEY_F3 = 60,
    LYD_KEY_F4 = 61,
    LYD_KEY_F5 = 62,
    LYD_KEY_F6 = 63,
    LYD_KEY_F7 = 64,
    LYD_KEY_F8 = 65,
    LYD_KEY_F9 = 66,
    LYD_KEY_F10 = 67,
    LYD_KEY_F11 = 68,
    LYD_KEY_F12 = 69,

    // Control Keys
    LYD_KEY_PRINTSCREEN = 70,
    LYD_KEY_SCROLLLOCK = 71,
    LYD_KEY_PAUSE = 72,
    LYD_KEY_INSERT = 73,
    LYD_KEY_HOME = 74,
    LYD_KEY_PAGEUP = 75,
    LYD_KEY_DELETE = 76,
    LYD_KEY_END = 77,
    LYD_KEY_PAGEDOWN = 78,
    LYD_KEY_RIGHT = 79,
    LYD_KEY_LEFT = 80,
    LYD_KEY_DOWN = 81,
    LYD_KEY_UP = 82,

    // Modifier Keys
    LYD_KEY_LCTRL = 224,
    LYD_KEY_LSHIFT = 225,
    LYD_KEY_LALT = 226,
    LYD_KEY_LGUI = 227, // Left Windows / Command Key
    LYD_KEY_RCTRL = 228,
    LYD_KEY_RSHIFT = 229,
    LYD_KEY_RALT = 230,
    LYD_KEY_RGUI = 231, // Right Windows / Command Key

    LYD_KEY_CAPSLOCK = 57,

    // Numpad
    LYD_KEY_NUMLOCKCLEAR = 83,
    LYD_KEY_KP_DIVIDE = 84,
    LYD_KEY_KP_MULTIPLY = 85,
    LYD_KEY_KP_MINUS = 86,
    LYD_KEY_KP_PLUS = 87,
    LYD_KEY_KP_ENTER = 88,
    LYD_KEY_KP_1 = 89,
    LYD_KEY_KP_2 = 90,
    LYD_KEY_KP_3 = 91,
    LYD_KEY_KP_4 = 92,
    LYD_KEY_KP_5 = 93,
    LYD_KEY_KP_6 = 94,
    LYD_KEY_KP_7 = 95,
    LYD_KEY_KP_8 = 96,
    LYD_KEY_KP_9 = 97,
    LYD_KEY_KP_0 = 98,
    LYD_KEY_KP_PERIOD = 99,

    // Special Keys
    LYD_KEY_APPLICATION = 101, // Menu Key
    LYD_KEY_POWER = 102,
    LYD_KEY_KP_EQUALS = 103,
    LYD_KEY_F13 = 104,
    LYD_KEY_F14 = 105,
    LYD_KEY_F15 = 106,
    LYD_KEY_F16 = 107,
    LYD_KEY_F17 = 108,
    LYD_KEY_F18 = 109,
    LYD_KEY_F19 = 110,
    LYD_KEY_F20 = 111,
    LYD_KEY_F21 = 112,
    LYD_KEY_F22 = 113,
    LYD_KEY_F23 = 114,
    LYD_KEY_F24 = 115,
    LYD_KEY_EXECUTE = 116,
    LYD_KEY_HELP = 117,
    LYD_KEY_MENU = 118,
    LYD_KEY_SELECT = 119,
    LYD_KEY_STOP = 120,
    LYD_KEY_AGAIN = 121,
    LYD_KEY_UNDO = 122,
    LYD_KEY_CUT = 123,
    LYD_KEY_COPY = 124,
    LYD_KEY_PASTE = 125,
    LYD_KEY_FIND = 126,
    LYD_KEY_MUTE = 127,
    LYD_KEY_VOLUMEUP = 128,
    LYD_KEY_VOLUMEDOWN = 129,

    LYD_KEY_COUNT = 230+1
} lyd_Key;

typedef enum {
  LYD_MOUSE_LEFT,
  LYD_MOUSE_RIGHT,
  LYD_MOUSE_MIDDLE,
  LYD_MOUSE_BUTTON4,
  LYD_MOUSE_BUTTON5,

  LYD_MOUSE_COUNT
} lyd_MouseButton;

bool lyd_key_pressed(lyd_Key k);
bool lyd_key_released(lyd_Key k);
bool lyd_key_down(lyd_Key k);
lyd_vec2 lyd_mouse_get(void);
lyd_vec2 lyd_mouse_get_from_window(void);
bool lyd_mouse_released(lyd_MouseButton btn);
bool lyd_mouse_pressed(lyd_MouseButton btn);
bool lyd_mouse_down(lyd_MouseButton btn);

// every function, struct, enum member.... has the lyd prefix to avoid confusion
// by defining this macro before including the file you disable the prefix
#define LYDIA_REMOVE_PREFIX //TODO REMOVE THIS LATER
#ifdef LYDIA_REMOVE_PREFIX
typedef lyd_vec2f             vec2f;
typedef lyd_vec2i             vec2i;
typedef lyd_vec2u             vec2u;
typedef lyd_vec2f              vec2;
typedef lyd_Color             Color;
typedef lyd_Texture         Texture;
typedef lyd_Key                 Key;
typedef lyd_MouseButton MouseButton;
typedef lyd_BlendMode     BlendMode;

#define COLOR_WHITE     LYD_COLOR_WHITE     
#define COLOR_BLACK     LYD_COLOR_BLACK     
#define COLOR_RED       LYD_COLOR_RED       
#define COLOR_GREEN     LYD_COLOR_GREEN     
#define COLOR_BLUE      LYD_COLOR_BLUE      
#define COLOR_MAGENTA   LYD_COLOR_MAGENTA   
#define COLOR_YELLOW    LYD_COLOR_YELLOW    
#define COLOR_TURQUOISE LYD_COLOR_TURQUOISE 
#endif

#define LYDIA_IMPLEMENT //TODO REMOVE AFTER
#ifdef LYDIA_IMPLEMENT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <SDL2/SDL.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define PRINT_LOG(level, ...) { printf("[%s]: ", level); printf(__VA_ARGS__); }
#define ERROR_EXT(...) { printf("[ERROR]: "); printf(__VA_ARGS__); exit(1); }
#define ERROR_RET(R, ...) { printf("[ERROR]: "); printf(__VA_ARGS__); return R; }

static bool running;

typedef struct {
  vec2u window_size;
  bool resizable;
  char *title;

  SDL_Window *sdlwin;
  SDL_Renderer *sdlrender;
  SDL_Texture *sdltex;

  Texture buffer;
  Texture *target;
  lyd_BlendMode blending;
} _RenderState;
static _RenderState render;

typedef struct {
  f32 target_frame_time;
  f32 delta;
  u32 last_frame_time;
  u32 start_time;
} _TimeState;
static _TimeState time;

static bool _key_current[LYD_KEY_COUNT] = {0};
static bool _key_previous[LYD_KEY_COUNT] = {0};
static bool _mouse_current[LYD_MOUSE_COUNT] = {0};
static bool _mouse_previous[LYD_MOUSE_COUNT] = {0};
static vec2 _mouse_pos = {0};

lyd_Color color_pack(u8 a, u8 r, u8 g, u8 b) {
  return ((u32)a << 24) | ((u32)r << 16) | ((u32)g << 8) | (u32)b;
}
void color_unpack(lyd_Color color, u8 *a, u8 *r, u8*g, u8*b) {
  *a = (color >> 24) & 0xff;
  *r = (color >> 16) & 0xff;
  *g = (color >> 8)  & 0xff;
  *b = color         & 0xff;
}

void lyd_init(u32 buffer_w, u32 buffer_h, u32 window_w, u32 window_h, char *title) { lyd_initx(buffer_w, buffer_h, window_w, window_h, title, 60.f, false, true); }
void lyd_initx(u32 buffer_w, u32 buffer_h, u32 window_w, u32 window_h, char *title, f32 frame_rate, bool resizable, bool border) {
  render = (_RenderState){0};
  render.window_size = (vec2u){window_w, window_h};
  render.title = title;
  render.resizable = resizable;
  render.blending = LYD_BLEND_NORMAL;
  render.buffer = (Texture){ (vec2u){buffer_w, buffer_h}, (Color*)malloc(sizeof(Color)*buffer_w*buffer_h) };
  if (!render.buffer.data)
    ERROR_EXT("failed to malloc for buffer data during window creation\n");
  render.target = &render.buffer;

  SDL_Init(SDL_INIT_VIDEO);
  int window_type = SDL_WINDOW_SHOWN;
  if (resizable) window_type |= SDL_WINDOW_RESIZABLE;
  if (!border) window_type |= SDL_WINDOW_BORDERLESS;
  render.sdlwin = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      window_w, window_h, window_type);
  render.sdlrender = SDL_CreateRenderer(render.sdlwin, -1, SDL_RENDERER_ACCELERATED);
  
  render.sdltex = SDL_CreateTexture(render.sdlrender, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, buffer_w, buffer_h);
  
  for (u32 i=0;i<buffer_w*buffer_h;i++) {
    render.buffer.data[i] = 0xFFFFFFFF;
  }   

  time = (_TimeState) {
    .last_frame_time = SDL_GetTicks(),
    .delta = 0.f,
    .target_frame_time = (1000 / frame_rate)
  };

  running = true;
}
void lyd_quit(void) {
  free(render.buffer.data);
  SDL_DestroyTexture(render.sdltex);
  SDL_DestroyRenderer(render.sdlrender);
  SDL_DestroyWindow(render.sdlwin);
  SDL_Quit();
}
bool lyd_get_running(void) {
  return running;
}
void lyd_stop_running(void) {
  running = false;
}

void lyd_update(void) {
  time.start_time = SDL_GetTicks();

  memcpy(_key_previous, _key_current, sizeof(_key_previous));
  const u8 *keystates = SDL_GetKeyboardState(NULL);
  for (u32 i=0;i<LYD_KEY_COUNT;i++) {
    _key_current[i] = keystates[i];
  }

  memcpy(_mouse_previous, _mouse_current, sizeof(_mouse_previous));
  for (u8 i=0;i<LYD_MOUSE_COUNT;i++)
    _mouse_current[i] = 0;
  u32 mouse_state = SDL_GetMouseState(NULL, NULL);
  if (mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT))
    _mouse_current[LYD_MOUSE_LEFT] = 1;
  if (mouse_state & SDL_BUTTON(SDL_BUTTON_RIGHT))
    _mouse_current[LYD_MOUSE_RIGHT] = 1;
  if (mouse_state & SDL_BUTTON(SDL_BUTTON_MIDDLE))
    _mouse_current[LYD_MOUSE_MIDDLE] = 1;
  if (mouse_state & SDL_BUTTON(SDL_BUTTON_X1))
    _mouse_current[LYD_MOUSE_BUTTON4] = 1;
  if (mouse_state & SDL_BUTTON(SDL_BUTTON_X2))
    _mouse_current[LYD_MOUSE_BUTTON5] = 1;

  SDL_Event sdlevent;
  while (SDL_PollEvent(&sdlevent)) {
    switch (sdlevent.type) {
      default:
        break;
      
      case SDL_QUIT:
        running = false;
      break;
      case SDL_MOUSEMOTION:
        _mouse_pos.x = sdlevent.motion.x;
        _mouse_pos.y = sdlevent.motion.y;
      break;
    }
  }
}
void lyd_update_late(void) {
  SDL_Rect dst;

  if (render.resizable) {
    SDL_GetWindowSize(render.sdlwin, &render.window_size.x, &render.window_size.y);
  }
  f32 sx = (f32)render.window_size.x / render.buffer.size.x;
  f32 sy = (f32)render.window_size.y / render.buffer.size.y;
  f32 scale = (sx<sy) ? sx : sy;

  dst = (SDL_Rect) {
    (render.window_size.x-render.buffer.size.x*scale)/2,
      (render.window_size.y-render.buffer.size.y*scale)/2,
      render.buffer.size.x*scale, render.buffer.size.y*scale
  };

  SDL_UpdateTexture(render.sdltex, NULL, render.buffer.data, render.buffer.size.x*sizeof(u32));
  SDL_RenderClear(render.sdlrender);
  SDL_RenderCopy(render.sdlrender, render.sdltex, NULL, &dst);
  SDL_RenderPresent(render.sdlrender);

  u32 frame_time = SDL_GetTicks() - time.start_time;
  if (frame_time < time.target_frame_time)
    SDL_Delay(time.target_frame_time-frame_time);

  u32 current_time = SDL_GetTicks();
  time.delta = (current_time - time.last_frame_time) / 1000.f;
  time.last_frame_time = current_time;
}

bool lyd_key_pressed(lyd_Key k) {
  if (k >= LYD_KEY_COUNT) ERROR_RET(false, "(lyd_key_pressed) theres no key number: %i\n", k);
  return _key_current[k] && !_key_previous[k];
}
bool lyd_key_down(lyd_Key k) {
  if (k >= LYD_KEY_COUNT) ERROR_RET(false, "(lyd_key_down) theres no key number: %i\n", k);
  return _key_current[k];
}
bool lyd_key_released(lyd_Key k) {
  if (k >= LYD_KEY_COUNT) ERROR_RET(false, "(lyd_key_released) theres no key number: %i\n", k);
  return !_key_current[k] && _key_previous[k];
}
bool lyd_mouse_released(MouseButton btn) {
  if (btn >= LYD_MOUSE_COUNT) ERROR_RET(false, "(lyd_mouse_released) theres no mouse button: %i\n", btn);
  return !_mouse_current[btn] && _mouse_previous[btn];
}
bool lyd_mouse_pressed(MouseButton btn) {
  if (btn >= LYD_MOUSE_COUNT) ERROR_RET(false, "(lyd_mouse_released) theres no mouse button: %i\n", btn);
  return _mouse_current[btn] && !_mouse_previous[btn];
}
bool lyd_mouse_down(MouseButton btn) {
  if (btn >= LYD_MOUSE_COUNT) ERROR_RET(false, "(lyd_mouse_released) theres no mouse button: %i\n", btn);
  return _mouse_current[btn];
}
lyd_vec2 lyd_mouse_get(void) {
  f32 x = (_mouse_pos.x * render.buffer.size.x) / render.window_size.x;
  f32 y = (_mouse_pos.y * render.buffer.size.y) / render.window_size.y;
  return (vec2){x, y};
}
lyd_vec2 lyd_mouse_get_from_window(void) {
  return _mouse_pos;
}

void lyd_change_target(lyd_Texture *target) {
  if (target == NULL)
    render.target = &render.buffer;
  else
    render.target = target;
}
void lyd_clear(lyd_Color c) {
  for (u32 i=0;i<render.target->size.x*render.target->size.y;i++) {
    render.target->data[i] = c;
  }
}
void lyd_change_blending(lyd_BlendMode mode) {
  render.blending = mode;
}
void lyd_render_pixel(lyd_vec2 pos, lyd_Color color) {
  if (pos.x > 0 && pos.y > 0 && pos.x < render.target->size.x && pos.y < render.target->size.y) {
    u32 out = color;
    if (render.blending != LYD_BLEND_NONE) {
      u8 src_a = 0;
      u8 src_r = 0;
      u8 src_g = 0;
      u8 src_b = 0;
      color_unpack(color, &src_a, &src_r, &src_g, &src_b);
      u8 dst_a = 0;
      u8 dst_r = 0;
      u8 dst_g = 0;
      u8 dst_b = 0;
      color_unpack(render.target->data[(u32)(pos.x+(u32)(pos.y)*render.target->size.x)], &dst_a, &dst_r, &dst_g, &dst_b);
      u8 out_a = 0;
      u8 out_r = 0;
      u8 out_g = 0;
      u8 out_b = 0;
      switch (render.blending) {
        default:
        break;

        case LYD_BLEND_NORMAL:
          out_a = (src_a * src_a + dst_a * (255 - src_a)) / 255;
          out_r = (src_r * src_a + dst_r * (255 - src_a)) / 255;
          out_g = (src_g * src_a + dst_g * (255 - src_a)) / 255;
          out_b = (src_b * src_a + dst_b * (255 - src_a)) / 255;
        break;

        case LYD_BLEND_ADDITIVE:
          out_a = src_a * src_a / 255 + dst_a;
          out_r = src_r * src_a / 255 + dst_r;
          out_g = src_g * src_a / 255 + dst_g;
          out_b = src_b * src_a / 255 + dst_b;
        break;

        case LYD_BLEND_SUBTRACTIVE:
          out_a = (dst_a - src_a * src_a / 255) < 0 ? 0 : dst_a - src_a * src_a / 255;
          out_r = (dst_r - src_r * src_a / 255) < 0 ? 0 : dst_r - src_r * src_a / 255;
          out_g = (dst_g - src_g * src_a / 255) < 0 ? 0 : dst_g - src_g * src_a / 255;
          out_b = (dst_b - src_b * src_a / 255) < 0 ? 0 : dst_b - src_b * src_a / 255;
        break;

        case LYD_BLEND_MULTIPLY:
          out_a = src_a * dst_a / 255;
          out_r = src_r * dst_r / 255;
          out_g = src_g * dst_g / 255;
          out_b = src_b * dst_b / 255;
        break;

        case LYD_BLEND_SCREEN:
          out_a = 255 - ((255 - src_a) * (255 - dst_a)) / 255;
          out_r = 255 - ((255 - src_r) * (255 - dst_r)) / 255;
          out_g = 255 - ((255 - src_g) * (255 - dst_g)) / 255;
          out_b = 255 - ((255 - src_b) * (255 - dst_b)) / 255;
        break;

        case LYD_BLEND_DARKEN:
          out_a = fmin(src_a, dst_a);
          out_r = fmin(src_r, dst_r);
          out_g = fmin(src_g, dst_g);
          out_b = fmin(src_b, dst_b);
        break;

        case LYD_BLEND_LIGHTEN:
          out_a = fmax(src_a, dst_a);
          out_r = fmax(src_r, dst_r);
          out_g = fmax(src_g, dst_g);
          out_b = fmax(src_b, dst_b);
        break;
      }
      out = color_pack(out_a, out_r, out_g, out_b);
    }

    render.target->data[(u32)(pos.x+(u32)(pos.y)*render.target->size.x)] = out;
  }
}
void lyd_render_rect(lyd_vec2 pos, lyd_vec2 size, lyd_Color color) {
  for (u32 i=0;i<size.y;i++) 
    for (u32 j=0;j<size.x;j++)
      lyd_render_pixel((lyd_vec2){pos.x+j, pos.y+i}, color);
}
void lyd_render_texture(lyd_vec2 pos, lyd_Texture texture) {
  for (u32 i=0;i<texture.size.y;i++)
    for (u32 j=0;j<texture.size.x;j++)
      lyd_render_pixel((lyd_vec2){pos.x+j, pos.y+i}, texture.data[j+i*texture.size.x]);
}

void lyd_render_line(lyd_vec2 start, lyd_vec2 end, lyd_Color color) {
  f32 dx = end.x - start.x;
  f32 dy = end.y - start.y;

  i32 steps = (int)fmax(fabs(dx), fabs(dy));

  f32 x_inc = dx / steps;
  f32 y_inc = dy / steps;

  f32 x = start.x;
  f32 y = start.y;

  for (u32 i=0;i<=steps;i++) {
    lyd_render_pixel((vec2){(int)(x+0.5f), (int)(y+0.5f)}, color);
    x += x_inc;
    y += y_inc;
  }
}


lyd_Texture lyd_texture_load(char *path) {
  int width, height, channels;
  uint8_t *imageData = stbi_load(path, &width, &height, &channels, 4); // Force RGBA (4 channels)
  if (!imageData)
    ERROR_EXT("failed to load image: %s\n", path);

  lyd_Texture texture = (lyd_Texture){0};
  texture.size.x = width;
  texture.size.y = height;
  texture.data = (lyd_Color *)malloc(width * height * sizeof(lyd_Color));

  for (int i = 0; i < width * height; i++) {
    uint8_t r = imageData[i * 4];
    uint8_t g = imageData[i * 4 + 1];
    uint8_t b = imageData[i * 4 + 2];
    uint8_t a = imageData[i * 4 + 3];
    texture.data[i] = (a << 24) | (r << 16) | (g << 8) | b;
  }

  stbi_image_free(imageData);
  return texture;
}

lyd_Texture lyd_texture_copy(lyd_Texture texture) {
  lyd_Texture ret = (lyd_Texture){.size = texture.size};
  ret.data = malloc(sizeof(lyd_Color)*texture.size.x*texture.size.y);
  for (u32 i=0;i<texture.size.x*texture.size.y;i++) {
    ret.data[i] = texture.data[i];
  }
  return ret;
}

void lyd_texture_replace_color(lyd_Texture t, lyd_Color from, lyd_Color to) {
  for (u32 i=0;i<t.size.x*t.size.y;i++) {
    if (t.data[i] == from)
      t.data[i] = to;
  }
}

void lyd_texture_flipy(lyd_Texture t) {
  lyd_Texture tmp = lyd_texture_copy(t);
  for (u32 i=0;i<t.size.x;i++)
    for (u32 j=0;j<t.size.y;j++)
      t.data[j*t.size.x+i] = tmp.data[(t.size.y-1-j)*t.size.x+i];
  free(tmp.data);
}
void lyd_texture_flipx(lyd_Texture t) {
  lyd_Texture tmp = lyd_texture_copy(t);
  for (u32 i=0;i<t.size.y;i++) {
    for (u32 j=0;j<t.size.x;j++) {
      t.data[i*t.size.x+j] = tmp.data[i*t.size.x+(t.size.x-j)];
    }
  }
  free(tmp.data);
}
void lyd_texture_cut(lyd_Texture *t, lyd_vec2 pos, lyd_vec2 size) {
  lyd_Texture res = (lyd_Texture){
    .size = LYD_VEC2TOU(size),
    .data = malloc(sizeof(lyd_Color)*size.x*size.y)
  };
  if (!res.data)
    ERROR_EXT("failed to malloc for texture cut function\n")

  for (u32 i=0;i<size.y;i++) {
    for (u32 j=0;j<size.x;j++) {
      res.data[(u32)(i * size.x + j)] = t->data[(int)((pos.y + i) * t->size.x + pos.x + j)];
    }
  }

  lyd_texture_free(*t);
  *t = res;
}
  
void lyd_texture_free(lyd_Texture texture) {
  free(texture.data);
}

#endif

#endif
