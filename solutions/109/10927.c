/* 10927
 * Bright Lights
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_LIGHTS      100000

typedef struct {
    long x, y, z;
} light_t;

light_t light[MAX_LIGHTS], invisible[MAX_LIGHTS];
int num_lights, num_invisibles;

long compute_angle(light_t a, light_t b) {
    return a.x * b.y - a.y * b.x;
}

long distance(light_t a) {
    return a.x * a.x + a.y * a.y;
}

int compare_angle(const void *a, const void *b) {
    light_t *x = (light_t *) a, *y = (light_t *) b;
    long angle = compute_angle(*x, *y);
    if (angle == 0)
        return distance(*x) < distance(*y) ? -1 : 1;
    return angle < 0 ? -1 : 1;
}

int compare_x(const void *a, const void *b) {
    light_t *x = (light_t *) a, *y = (light_t *) b;
    if (x->x == y->x)
        return x->y < y->y ? -1 : 1;
    return x->x < y->x ? -1 : 1;
}


void compute_invisibles() {
    int i;
    long height;
    qsort(light, num_lights, sizeof (light_t), compare_angle);
    for (i = 0, num_invisibles = 0, height = 0; i < num_lights; i++) {
        if (i == 0 || compute_angle(light[i], light[i - 1]) != 0)
            height = light[i].z;
        else {
            if (light[i].z <= height)
                invisible[num_invisibles++] = light[i];
            else
                height = light[i].z;
        }
    }
    qsort(invisible, num_invisibles, sizeof (light_t), compare_x);
}

/* Main function */
int main() {
    int i, test = 0;
    while (scanf("%d", &num_lights) != EOF && num_lights > 0) {
        for (i = 0; i < num_lights; i++) {
            light_t *l = &light[i];
            assert(scanf("%ld %ld %ld", &l->x, &l->y, &l->z) != EOF);
        }
        compute_invisibles();
        printf("Data set %d:\n", ++test);
        if (num_invisibles == 0)
            printf("All the lights are visible.\n");
        else {
            printf("Some lights are not visible:\n");
            for (i = 0; i < num_invisibles; i++)
                printf("x = %ld, y = %ld%c\n", invisible[i].x, 
                        invisible[i].y, i == num_invisibles - 1 ? '.' : ';');
        }
    }
    return EXIT_SUCCESS;
}
