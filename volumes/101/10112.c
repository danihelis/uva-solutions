/* 10112
 * Myacm Triangles
 * By Johan Schreiber
 */
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_POINTS      15

typedef struct {
    char name;
    int x, y;
} point_t;

point_t points[MAX_POINTS];
point_t *solution[3];
int num_points;


/* Computes the sine between three points */
int sine(point_t *a, point_t *b, point_t *c) {
    return (b->x - a->x) * (c->y - a->y) - (c->x - a->x) * (b->y - a->y);
}


/* Signal of an integer */
int signal(int x) {
    return x < 0 ? -1 : x > 0 ? 1 : 0;
}


/* Checks if a triangle does not contain any other points */
int is_triangle_isolated(point_t *a, point_t *b, point_t *c) {
    int i;
    for (i = 0; i < num_points; i++) {
        int s1, s2, s3;
        point_t *p = &points[i];

        if (p == a || p == b || p == c) continue;

        s1 = signal(sine(a, p, b));
        s2 = signal(sine(b, p, c));
        s3 = signal(sine(c, p, a));

        if ((s1 == 0 && s2 == s3) || (s2 == 0 && s1 == s3) ||
                (s3 == 0 && s1 == s2) || (s1 == s2 && s1 == s3)) {
            return 0;
        }
    }
    return 1;
}


/* Check all possible triangles and return the largest area */
void find_largest_triangle() {
    int ia, ib, ic;
    int largest = 0;

    for (ia = 0; ia < num_points - 2; ia++) {
        point_t *a = &points[ia];

        for (ib = ia + 1; ib < num_points - 1; ib++) {
            point_t *b = &points[ib];

            for (ic = ib + 1; ic < num_points; ic++) {
                point_t *c = &points[ic];

                if (is_triangle_isolated(a, b, c)) {
                    int area = sine(a, b, c); /* double area, actually */
                    if (area < 0) area = -area;

                    if (area > largest) {
                        largest = area;
                        solution[0] = a;
                        solution[1] = b;
                        solution[2] = c;
                    }
                }
            }
        }
    }
    assert(largest > 0);
}


/* Main function */
int main() {
    while (scanf("%d", &num_points) == 1 && num_points > 0) {
        int i;
        for (i = 0; i < num_points; i++) {
            point_t *p = &points[i];
            assert(scanf(" %c %d %d", &p->name, &p->x, &p->y) == 3);
        }
        find_largest_triangle();
        for (i = 0; i < 3; i++) {
            printf("%c", solution[i]->name);
        }
        printf("\n");
    }
    return EXIT_SUCCESS;
}
