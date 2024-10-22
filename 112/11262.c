/* 11262
 * Weird Fence
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define NUM_COLORS      2
#define MAX_POLES       100
#define MAX_LINKS       (MAX_POLES * MAX_POLES / 4)
#define INFINITY        1000000

typedef struct pole_s {
    int x, y, index, color;
    double total;
    struct pole_s *cover, *previous;
} pole_t, *pole_p;

pole_t pole[NUM_COLORS][MAX_POLES];
double link[MAX_POLES][MAX_POLES];
int num_poles[NUM_COLORS];

#define SQUARE(x)       ((x) * (x))
#define MAX(x,y)        ((x) > (y) ? (x) : (y))

/* Determine the distance between all poles */
void set_distances() {
    int i, j;
    for (i = 0; i < num_poles[0]; i++) {
        for (j = 0; j < num_poles[1]; j++) {
            pole_p p0 = &pole[0][i], p1 = &pole[1][j];
            link[i][j] = sqrt(SQUARE(p0->x - p1->x) + SQUARE(p0->y - p1->y));
        }
    }
}

/* Find minimal link to add to bipartite graph */
double find_minimal_link() {
    pole_p queue[MAX_POLES];
    int i, k, size, top;
    for (k = 0, size = 0; k < NUM_COLORS; k++) {
        for (i = 0; i < num_poles[k]; i++) {
            pole_p p = &pole[k][i];
            p->previous = NULL;
            p->total = (k == 0 && p->cover == NULL ? 0 : INFINITY);
            queue[size++] = p;
        }
    }
    
    top = 0;
    while (top < size) {
        pole_p p;
        /* Select path with minimum distance */
        for (k = top, i = top + 1; i < size; i++) {
            if (queue[i]->total < queue[k]->total) {
                k = i;
            }
        }
        if (k != top) {
            pole_p swap = queue[top];
            queue[top] = queue[k];
            queue[k] = swap;
        }
        p = queue[top++];

        /* Found extremity on right side */
        if (p->color == 1) {
            if (p->cover != NULL) {
                if (MAX(p->total, link[p->cover->index][p->index]) < p->cover->total) {
                    p->cover->total = MAX(p->total, link[p->cover->index][p->index]);
                    p->cover->previous = p;
                }
            }
            /* Found solution! */
            else {
                double biggest = p->total;
                while (p != NULL) {
                    if (p->previous->cover != NULL) {
                        p->previous->cover->cover = NULL;
                    }
                    p->cover = p->previous, p->previous->cover = p;
                    p = p->previous->previous;
                }
                return biggest;
            }
        }
        /* Add possible extremities on left side */
        else if (p->color == 0) {
            for (i = 0; i < num_poles[1]; i++) {
                pole_p next = &pole[1][i];
                if (MAX(link[p->index][i], p->total) < next->total) {
                    next->total = MAX(p->total, link[p->index][i]);
                    next->previous = p;
                }
            }
        }
    }
    assert(NULL);
    return 0;
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        char color;
        int i, x, y, c, n, k;
        assert(scanf("%d %d", &n, &k) != EOF);
        num_poles[0] = 0, num_poles[1] = 0;
        for (i = 0; i < n; i++) {
            pole_p p;
            assert(scanf("%d %d %c%*[^\n]", &x, &y, &color) != EOF);
            c = (color == 'r' ? 0 : 1);
            p = &pole[c][num_poles[c]];
            p->x = x, p->y = y, p->color = c, p->cover = NULL;
            p->index = num_poles[c]++;
        }
        if (k > num_poles[0] || k > num_poles[1]) {
            printf("Impossible\n");
        }
        else {
            double result;
            set_distances();
            for (i = 0, result = 0; i < k; i++) {
                result = find_minimal_link();
            }
            printf("%d\n", (int) ceil(result));
        }
    }
    return 0;
}
