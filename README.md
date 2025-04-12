# Lydia 

A lightweight, single-header framework for making simple games or visual experiments using SDL2.  
Renders directly to a buffer you manage, with support for 2D rendering, textures, input handling, and more.

**Lydia** is not a full-fledged engine — it's a minimal rendering/input layer meant to give you control and simplicity. Think of it as a sandbox for messing with pixels and making tiny toys or prototypes.

## ✨ Features

- Simple pixel buffer rendering via SDL
- Built-in color packing/unpacking (AARRGGBB)
- Vec2 types (`vec2f`, `vec2i`, `vec2u`)
- Texture loading (via `stb_image`)
- Basic Spritesheet implementation
- Basic blending modes
- Input system (keyboard + mouse)
- Adjustable resolution scaling with pixel-perfect output
- Easy to plug into any C project

> **Note:** This is a header-only library. Just include the header and define `LYDIA_IMPLEMENT` in one source file.

---

## 🚀 Quickstart

```c
#define LYDIA_IMPLEMENT
#include "lydia.h"

int main() {
    lyd_init(320, 240, 640, 480, "Hello Lydia");

    while (lyd_get_running()) {
        lyd_update();

        lyd_clear(COLOR_BLACK);
        lyd_render_rect((vec2){50, 50}, (vec2){100, 100}, COLOR_RED);

        lyd_update_late();
    }

    lyd_quit();
    return 0;
}
```
## Optional defines

before including the header(or inside the header), you can define the following macros for customization
- *LYDIA_TYPEDEFS* : enables aliases like u8,i32,f64, etc
- *LYDIA_REMOVE_PREFIX* : removes the lyd_ prefix from types for cleaner usage (Texture, vec2, etc.)
- *LYDIA_IMPLEMENT* — you must define this once in your project to compile the implementation.

---

## Little cheatsheet

this contains some basic functions to get started if you dont understand something just read the source code, its pretty self-explanatory

```c
//types
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

typedef struct { f32 x, y; } lyd_vec2f;
typedef struct { i32 x, y; } lyd_vec2i;
typedef struct { u32 x, y; } lyd_vec2u;
typedef lyd_vec2f lyd_vec2; // by default vec2 is a float vector$


//general stuff$
void lyd_init(u32 buffer_w, u32 buffer_h, u32 window_w, u32 window_h, char *title);
void lyd_initx(u32 buffer_w, u32 buffer_h, u32 window_w, u32 window_h, char *title, f32 frame_rate, bool resizable, bool border);
void lyd_quit(void);
bool lyd_get_running(void);
void lyd_stop_running(void);
void lyd_update(void); //must be called at the start of the loop
void lyd_update_late(void); // must be called at the end of the loop

//render
void lyd_change_target(lyd_Texture *target); //leave null for the buffer
void lyd_clear(lyd_Color c);
void lyd_change_blending(lyd_BlendMode mode);
f32 lyd_time_delta(void);

void lyd_render_pixel(lyd_vec2 pos, lyd_Color color);
void lyd_render_rect(lyd_vec2 pos, lyd_vec2 size, lyd_Color color);
void lyd_render_texture(lyd_vec2 pos, lyd_Texture texture);
void lyd_render_line(lyd_vec2 start, lyd_vec2 end, lyd_Color color);

lyd_Spritesheet lyd_spritesheet_create(char *path, lyd_vec2u tilesize);
lyd_Texture lyd_spritesheet_get(lyd_Spritesheet s, u32 i);
void lyd_spritesheet_free(lyd_Spritesheet s);

lyd_Texture lyd_texture_load(char *path);
lyd_Texture lyd_texture_copy(lyd_Texture texture);
void lyd_texture_replace_color(lyd_Texture t, lyd_Color from, lyd_Color to);
void lyd_texture_flipx(lyd_Texture t);
void lyd_texture_flipy(lyd_Texture t);
void lyd_texture_cut(lyd_Texture *t, lyd_vec2 pos, lyd_vec2 size);
void lyd_texture_free(lyd_Texture texture);

//input
bool lyd_key_pressed(lyd_Key k);
bool lyd_key_released(lyd_Key k);
bool lyd_key_down(lyd_Key k);

lyd_vec2 lyd_mouse_get(void); //relative to the buffer
lyd_vec2 lyd_mouse_get_from_window(void); // relative to the window
bool lyd_mouse_released(lyd_MouseButton btn);
bool lyd_mouse_pressed(lyd_MouseButton btn);
bool lyd_mouse_down(lyd_MouseButton btn);
i32 lyd_mouse_scroll(void);

//colors
typedef u32 lyd_Color; // colors are represented by u32
                       // with the AARRGGBB format
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
```

---

## License

Public Domain / MIT -- do whatever you want
Attribution appreciated but not required.

---

## Problems / ideas

if you find any problem with the framework or you want to give me an idea on something to add, feel free to contact me(nvh.cha@gmail.com)
