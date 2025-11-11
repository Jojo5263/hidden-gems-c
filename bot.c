#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jansson.h>

int main(void) {
    srand(1);
    int first_tick = 1;
    char buf[65536];

    while (fgets(buf, sizeof(buf), stdin)) {
        json_error_t err;
        json_t *root = json_loads(buf, 0, &err);
        if (!root) continue;

        if (first_tick) {
            json_t *cfg = json_object_get(root, "config");
            json_t *w = cfg ? json_object_get(cfg, "width") : NULL;
            json_t *h = cfg ? json_object_get(cfg, "height") : NULL;
            const char *ws = (w && json_is_integer(w)) ? NULL : "?";
            const char *hs = (h && json_is_integer(h)) ? NULL : "?";
            if (ws || hs) {
                fprintf(stderr, "Random walker (C) launching on a %sx%s map\n",
                        ws ? ws : "", hs ? hs : "");
            } else {
                fprintf(stderr, "Random walker (C) launching on a %lldx%lld map\n",
                        (long long)json_integer_value(w), (long long)json_integer_value(h));
            }
            fflush(stderr);
        }

        const char *moves[] = {"N","S","E","W"};
        const char *mv = moves[rand() % 4];
        printf("%s\n", mv);
        fflush(stdout);

        first_tick = 0;
        json_decref(root);
    }
    return 0;
}
