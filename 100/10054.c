/* 10054
 * The Necklace
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_BEADS   1000
#define MAX_COLORS  50

typedef struct {
    int beads[MAX_COLORS];
    int count, loops;
} color_t;

color_t colors[MAX_COLORS];
int num_beads, first_color;

/* Visit a cycle */
void visit_cycle(int start) {
    int queue[MAX_BEADS], size, i, found;

    for (; colors[start].loops > 0; colors[start].loops--)
        printf("%d %d\n", start + 1, start + 1);
    
    queue[0] = start, size = 1;
    do {
        int cur = queue[size - 1];
        for (i = 0, found = 0; !found && i < MAX_COLORS; i++)
            if (colors[cur].beads[i] > 0) {
                colors[cur].beads[i]--, colors[cur].count--;
                colors[i].beads[cur]--, colors[i].count--;
                queue[size++] = i;
                found = 1;
            }
        if (!found)
            return;
    } while (queue[size - 1] != start);

    for (i = 1; i < size; i++) {
        printf("%d %d\n", queue[i - 1] + 1, queue[i] + 1);
        if (colors[queue[i]].count > 0 || colors[queue[i]].loops > 0)
            visit_cycle(queue[i]);
    }
}

/* Main function */
#define INC_COLOR(color, next)  colors[color].beads[next]++, \
                                colors[color].count++

int main() {
    int test, num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (test = 1; test <= num_tests; test++) {
        int i, feasible;
        printf("%sCase #%d\n", test == 1 ? "" : "\n", test);

        assert(scanf("%d", &num_beads) != EOF);
        for (i = 0; i < MAX_COLORS; i++) {
            color_t *c = &colors[i];
            c->count = c->loops = 0;
            memset(c->beads, 0, MAX_COLORS * sizeof (int));
        }
        for (i = 0; i < num_beads; i++) {
            int c1, c2;
            assert(scanf("%d %d", &c1, &c2) != EOF);
            c1--, c2--;
            if (i == 0)
                first_color = c1;
            if (c1 == c2)
                colors[c1].loops++;
            else {
                INC_COLOR(c1, c2);
                INC_COLOR(c2, c1);
            }
        }
        for (i = 0, feasible = 1; feasible && i < MAX_COLORS; i++) {
            color_t *c = &colors[i];
            feasible &= c->count % 2 == 0 && (c->loops == 0 || 
                    c->count > 0 || c->loops == num_beads);
        }
        if (!feasible)
            printf("some beads may be lost\n");
        else
            visit_cycle(first_color);
    }
    return EXIT_SUCCESS;
}
