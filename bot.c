#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jansson.h>

int main(void) {
    char buf[65536];
    int first_tick = 1;

    while (fgets(buf, sizeof(buf), stdin)) {
        json_error_t err;
        json_t *root = json_loads(buf, 0, &err);
        if (!root) continue;

        if (first_tick) {
            //Bewegung in Buffer laden
            json_t *cfg = json_object_get(root, "config");
            json_t *w = cfg ? json_object_get(cfg, "width") : NULL;
            json_t *h = cfg ? json_object_get(cfg, "height") : NULL;
            if (w && h && json_is_integer(w) && json_is_integer(h)) {
                fprintf(stderr, "Bot launching on a %lldx%lld map\n",
                        (long long)json_integer_value(w),
                        (long long)json_integer_value(h));
            }
            fflush(stderr);
            first_tick = 0;
        }
        //Bot & Gem Position laden
        json_t *bot_pos = json_object_get(root, "bot");
        json_t *visible_gems = json_object_get(root, "visible_gems");

        int bot_x = (int)json_integer_value(json_array_get(bot_pos, 0));
        int bot_y = (int)json_integer_value(json_array_get(bot_pos, 1));

        int min_dist = 1000000;
        int target_x = bot_x;
        int target_y = bot_y;
        int foundGem = 0;
        //Falls eins einen Gem in sichtweite gibt
        

        
        if (foundGem) {
            //Schnellster Weg zu Gem laufen
            if (bot_x < target_x) printf("E\n");
            else if (bot_x > target_x) printf("W\n");
            else if (bot_y < target_y) printf("S\n");
            else if (bot_y > target_y) printf("N\n");
        } else {
            //Nächsten Gem suchen
            
        }

        fflush(stdout);
        json_decref(root);
    }

    return 0;
}
