#include "lydia.h"

static bool running = true;

static vec2 start;
static vec2 end;

static u32 i;

int main(int argc, char *argv[]) {
  lyd_init(320, 180, 1280, 720, "test");

  lyd_Texture t = lyd_texture_load("test.png");
  lyd_texture_cut(&t, (vec2){1, 5}, (vec2){17, 33});

  start = (vec2){0.5f, 0.5f};
  end = (vec2){0};

  i = 0;

  while (lyd_get_running()) {
    lyd_update();
    lyd_clear(COLOR_BLACK);
    lyd_change_blending(LYD_BLEND_LIGHTEN);

    if (lyd_key_down(LYD_KEY_W)) start.y -= 0.5;
    if (lyd_key_down(LYD_KEY_S)) start.y += 0.5;
    if (lyd_key_down(LYD_KEY_A)) start.x -= 0.5;
    if (lyd_key_down(LYD_KEY_D)) start.x += 0.5;

    if (lyd_key_down(LYD_KEY_UP)) end.y -= 0.5;
    if (lyd_key_down(LYD_KEY_DOWN)) end.y += 0.5;
    if (lyd_key_down(LYD_KEY_LEFT)) end.x -= 0.5;
    if (lyd_key_down(LYD_KEY_RIGHT)) end.x += 0.5;

    lyd_render_texture((vec2){3, 2}, t);

    lyd_render_line(start, end, COLOR_RED);
    lyd_render_rect(start, (vec2){120, 120}, color_pack(255, 0, 0, 255));
    lyd_render_rect(end, (vec2){120, 120}, color_pack(192, 255, 255, 0));

    if (lyd_key_pressed(LYD_KEY_SPACE))
      i++;

    if (lyd_mouse_pressed(i))
      printf("pressed\n");
    if (lyd_mouse_down(i))
      printf("down\n");
    if (lyd_mouse_released(i))
      printf("released\n");

    lyd_update_late();
  }

  lyd_texture_free(t);

  lyd_quit();
  return 0;
}
