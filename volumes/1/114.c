/**
 * 114
 * Simulation Wizardry
 * by Daniel Donadon
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIM 50
#define MAX_ELEMS (MAX_DIM) * (MAX_DIM)

#define NUM_DIR 4
typedef enum {
    RIGHT = 0,
    UP = 1,
    LEFT = 2,
    DOWN = 3
} direction;

typedef struct {
    int score_value, lifetime_cost;
} bumper_t;

bumper_t bumper[MAX_ELEMS];
int num_bumpers;
int map[MAX_DIM][MAX_DIM];
int max_x, max_y;
int wall_lifetime_cost;

int posx, posy;
direction dir;
int score;
int lifetime;

/* Emulate pinball */
void emulate_pinball() {
    score = 0;
    while (lifetime > 0) {
        int newx = posx + (dir == RIGHT ? 1 : (dir == LEFT ? -1 : 0));
        int newy = posy + (dir == UP ? 1 : (dir == DOWN ? -1 : 0));
        int hit = 0;

        /* Hit a wall */
        hit = (newx <= 0 || newx >= max_x - 1 || newy <= 0 || newy >= max_y - 1);
        if (hit) {
            lifetime -= wall_lifetime_cost;
        }
        /* Hit a bumper */
        else if (map[newy][newx] != -1) {
            bumper_t *b = &bumper[map[newy][newx]];
            if (lifetime <= 1) {
                break; /* add hoc rule for balls hitting bumpers with one unit of life */
            }
            hit = 1;
            lifetime -= b->lifetime_cost;
            score += b->score_value;
        }

        /* Move to new position if it has not hit */
        if (!hit) {
            posx = newx;
            posy = newy;
        }
        /* Rotate clockwise if it has hit, without moving from its place */
        else {
            dir = (dir == RIGHT ? DOWN : dir - 1);
        }        
        lifetime--;
    }
}


/* Main */
int main() {
    int i, dir_int;
    long sum = 0;

    memset(map, (unsigned char) 0xff, MAX_ELEMS * sizeof(int));
    scanf("%d %d", &max_x, &max_y);
    scanf("%d", &wall_lifetime_cost);
    scanf("%d", &num_bumpers);
    for (i = 0; i < num_bumpers; i++) {
        int x, y;
        bumper_t *b = &bumper[i];
        scanf("%d %d %d %d", &x, &y, &b->score_value, &b->lifetime_cost);
        map[--y][--x] = i;
    }

    while (scanf("%d %d %d %d", &posx, &posy, &dir_int, &lifetime) == 4) {
        dir = (direction) dir_int;
        posx--;
        posy--;
        emulate_pinball();
        printf("%d\n", score);
        sum += score;
    }
    printf("%ld\n", sum);
    return 0;
} 
