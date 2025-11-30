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
        json_t *walls = json_object_get(root, "walls");

        int bot_x = (int)json_integer_value(json_array_get(bot_pos, 0));
        int bot_y = (int)json_integer_value(json_array_get(bot_pos, 1));

        int min_dist = 1000000;
        int target_x = bot_x;
        int target_y = bot_y;
        int foundGem = 0;
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
            //Nächsten Gem suchen
            switch (rand() % 4) {
             
                case 0:
                    printf("N\n");
                    break;

                case 1:
                    printf("S\n");
                    break;

                case 2:
                    printf("W\n");
                    break;

                case 3:
                    printf("E\n");
                    break;

                default:
                    printf("Wait\n");
                
            }

            


            
        }



        fflush(stdout);
        json_decref(root);
    }
    return 0;
}
