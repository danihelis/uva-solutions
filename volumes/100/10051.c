/* 10051
 * Tower of Cubes
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_CUBES 500
#define NUM_COLOURS 100
#define MAX_SIDES 6
#define MAX_STRING 10

#define OPPOSITE(x) ((x) % 2 == 0 ? (x) + 1 : (x) - 1)

typedef enum {
    FRONT,
    BACK,
    LEFT, 
    RIGHT,
    TOP,
    BOTTOM
} side_t;

char side_name[MAX_SIDES][MAX_STRING] = {"front", "back", "left", "right", "top", "bottom"};

typedef struct {
    int colour[MAX_SIDES];
    int index;
} cube_t, *cube_p;

typedef struct placed_s {
    struct placed_s *prior;
    cube_p cube;
    side_t base;
    int height;
} placed_t, *placed_p;

cube_t cube[MAX_CUBES];
placed_t top[NUM_COLOURS][MAX_SIDES * MAX_CUBES];
int num_cubes, top_size[NUM_COLOURS];
placed_p global_highest;

/* Add in a colour sequence */
void add_sequence(cube_p cube, side_t base) {
    int base_colour = cube->colour[base], opposite_colour = cube->colour[OPPOSITE(base)];
    int i;
    placed_p best =  NULL;
    for (i = 0; i < top_size[base_colour]; i++) {
        placed_p top_cube = &top[base_colour][i];
        if (top_cube->cube->index == cube->index) {
            continue;
        }
        if (best == NULL || top_cube->height > best->height) {
            best = top_cube;
        }
    }
    top[opposite_colour][top_size[opposite_colour]].cube = cube;
    top[opposite_colour][top_size[opposite_colour]].base = base;
    top[opposite_colour][top_size[opposite_colour]].height = 1 + 
        (best == NULL ? 0 : best->height);
    top[opposite_colour][top_size[opposite_colour]].prior = best;
    if (global_highest == NULL || top[opposite_colour][top_size[opposite_colour]].height >
            global_highest->height) {
        global_highest = &top[opposite_colour][top_size[opposite_colour]];
    }
    top_size[opposite_colour]++;
}

/* Main function */
int main() {
    int test = 1;
    while (scanf("%d", &num_cubes) != EOF && num_cubes > 0) {
        int i, j;
        memset(top_size, 0, NUM_COLOURS * sizeof (int));
        global_highest = NULL;
        for (i = 0; i < num_cubes; i++) {
            cube[i].index = i + 1;
            for (j = 0; j < MAX_SIDES; j++) {
                assert(scanf("%d", &cube[i].colour[j]) != EOF);
                cube[i].colour[j]--;
            }
        }
        for (i = num_cubes - 1; i >= 0; i--) {
            for (j = 0; j < MAX_SIDES; j++) {
                add_sequence(&cube[i], j);
            }
        }
        printf("%sCase #%d\n%d\n", (test > 1 ? "\n" : ""), test, global_highest->height);
        for (; global_highest != NULL; global_highest = global_highest->prior) {
            printf("%d %s\n", global_highest->cube->index, 
                    side_name[OPPOSITE(global_highest->base)]);
        }
        test++;
    }
    return 0;
}
