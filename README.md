# Lydia 

A lightweight, single-header framework for making simple games or visual experiments using SDL2.  
Renders directly to a buffer you manage, with support for 2D rendering, textures, input handling, and more.

**Lydia** is not a full-fledged engine — it's a minimal rendering/input layer meant to give you control and simplicity. Think of it as a sandbox for messing with pixels and making tiny toys or prototypes.

## ✨ Features

- Simple pixel buffer rendering via SDL
- Built-in color packing/unpacking (AARRGGBB)
- Vec2 types (`vec2f`, `vec2i`, `vec2u`)
- Texture loading (via `stb_image`)
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
- LYDIA_TYPEDEFS : enables aliases like u8,i32,f64, etc
- LYDIA_REMOVE_PREFIX : removes the lyd_ prefix from types/functions for cleaner usage (Texture, vec2, etc.)
- LYDIA_IMPLEMENT — you must define this once in your project to compile the implementation.
