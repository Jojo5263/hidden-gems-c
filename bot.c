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
        json_t *walls = json_object_get(root, "walls");

        
        int bot_x = (int)json_integer_value(json_array_get(bot_pos, 0));
        int bot_y = (int)json_integer_value(json_array_get(bot_pos, 1));

        int min_dist = 1000;
        int target_x = bot_x;
        int target_y = bot_y;
        int foundGem = 0;
        int nearestWall [] = {0,0};
        //Falls eins einen Gem in sichtweite gibt

        if (visible_gems && json_is_array(visible_gems) && json_array_size(visible_gems) > 0) {
            size_t i;
            json_t *gem;
            //Distanz zum Gem berechnen
            json_array_foreach(visible_gems, i, gem) {
                json_t *pos = json_object_get(gem, "position");
                int dx = (int)json_integer_value(json_array_get(pos, 0));
                int dy = (int)json_integer_value(json_array_get(pos, 1));
                int dist = abs(bot_x - dx) + abs(bot_y - dy);
                if (dist < min_dist) {
                    min_dist = dist;
                    target_x = dx;
                    target_y = dy;
                    foundGem = 1;
                }
            }
        }

        
        if (foundGem) {
            //Schnellster Weg zu Gem laufen
            if (bot_x < target_x) printf("E\n");
            else if (bot_x > target_x) printf("W\n");
            else if (bot_y < target_y) printf("S\n");
            else if (bot_y > target_y) printf("N\n");
        } else {
            

        }



        fflush(stdout);
        json_decref(root);
    }

    return 0;
}

int nearestWallX(){

    return 1;
}

int nearestWallY(){

    return 1;
}
