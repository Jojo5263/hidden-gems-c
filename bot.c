#include <jansson.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int bot_x;
int bot_y;
int gem_X;
int gem_Y;
int lastPosX;
int lastPosY;
int floors;
json_t *w;
json_t *h;
/* int **checked; */

// 4-Way Bresenham Line Algorithm
void goTo(int BotX, int BotY, int TargetX, int TargetY) {
  int dx = abs(TargetX - BotX);
  int dy = abs(TargetY - BotY);
  int sx = (BotX < TargetX) ? 1 : -1;
  int sy = (BotY < TargetY) ? 1 : -1;
  int err = dx - dy;

  // Bresenham decision next step
  if (err <= 0) {
    // Move in X direction
    if (sx > 0)
      printf("O\n");
    else
      printf("W\n");
  } else {
    // Move in Y direction
    if (sy > 0)
      printf("S\n");
    else
      printf("N\n");
  }
}

int main(void) {
  char buf[65536];
  int first_tick = 1;

  while (fgets(buf, sizeof(buf), stdin)) {
    json_error_t err;
    json_t *root = json_loads(buf, 0, &err);
    if (!root)
      continue;

    if (first_tick) {
      json_t *cfg = json_object_get(root, "config");
      w = cfg ? json_object_get(cfg, "width") : NULL;
      h = cfg ? json_object_get(cfg, "height") : NULL;
      first_tick = 0;
    }

    // Bot & Gem Position laden
    json_t *bot_pos = json_object_get(root, "bot");
    json_t *visible_gems = json_object_get(root, "visible_gems");

    bot_x = json_integer_value(json_array_get(bot_pos, 0));
    bot_y = json_integer_value(json_array_get(bot_pos, 1));

    /* checked = (int **)malloc(json_integer_value(w) * sizeof(int *));

    for (int i = 0; i < json_integer_value(w); ++i) {
      checked[i] = (int *)malloc(json_integer_value(h) * sizeof(int));
    } */

    if (json_array_size(visible_gems) > 0) {
      gem_X = json_integer_value(
          json_array_get(json_array_get(visible_gems, 0), 0));
      gem_Y = json_integer_value(
          json_array_get(json_array_get(visible_gems, 0), 1));
      goTo(bot_x, bot_y, gem_X, gem_Y);
    } else {
      // Zufallsbewegung wenn keine Edelsteine sichtbar
      switch (rand() % 4) {
      case 0:
        printf("N\n");
        break;
      case 1:
        printf("E\n");
        break;
      case 2:
        printf("S\n");
        break;
      case 3:
        printf("W\n");
        break;
      }
    }

    /* for (int i = 0; i < json_integer_value(w); ++i) {
      free(checked[i]);
    }
    free(checked);
    checked = NULL; */

    fflush(stdout);
    json_decref(root);
  }
  return 0;
}