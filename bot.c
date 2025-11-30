#include <jansson.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char buf[65536];
    int bot_x, bot_y, gem_X, gem_Y;

    while (fgets(buf, sizeof(buf), stdin)) {
        json_error_t err;
        json_t *root = json_loads(buf, 0, &err);
        if (!root) {
            printf("N\n");
            continue;
        }

        json_t *bot_pos = json_object_get(root, "bot");
        bot_x = json_integer_value(json_array_get(bot_pos, 0));
        bot_y = json_integer_value(json_array_get(bot_pos, 1));

        json_t *visible_gems = json_object_get(root, "visible_gems");

        if (visible_gems && json_array_size(visible_gems) > 0) {
            json_t *first_gem = json_array_get(visible_gems, 0);
            json_t *pos = json_object_get(first_gem, "position");
            if (pos && json_is_array(pos) && json_array_size(pos) == 2) {
                gem_X = json_integer_value(json_array_get(pos, 0));
                gem_Y = json_integer_value(json_array_get(pos, 1));
            } else {
                gem_X = gem_Y = 0;
            }

            int dx = abs(gem_X - bot_x);
            int dy = abs(gem_Y - bot_y);

            if (dx == 0 && dy == 0) {
                printf("N\n");
            } else if (dx > dy) {
                printf("%s\n", (bot_x < gem_X) ? "E" : "W");
            } else {
                printf("%s\n", (bot_y < gem_Y) ? "S" : "N");
            }
        } else {
            int move = rand() % 4;
            switch (move) {
                case 0: printf("N\n"); break;
                case 1: printf("E\n"); break;
                case 2: printf("S\n"); break;
                case 3: printf("W\n"); break;
            }
        }

        fflush(stdout);
        json_decref(root);
    }
    return 0;
}
