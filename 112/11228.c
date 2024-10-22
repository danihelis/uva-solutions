/* 11228
 * Transportation system.
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_CITIES      1000
#define MAX_ROADS       (MAX_CITIES * MAX_CITIES)
#define SQ(x)           ((x) * (x))
#define ROUND(x)        ((int) ((x) + 0.5 - 1e-7))

typedef enum {
    STATE,
    CONNECTION
} type_t;

typedef struct city_s {
    int x, y, visited;
    struct city_s *set[2];
} city_t;

typedef struct {
    int dist_sq;
    city_t *c1, *c2;
} road_t;

city_t city[MAX_CITIES];
road_t road[MAX_ROADS];
int num_cities;

/* Get set */
city_t * get_set(city_t *c, type_t type) {
    if (c->set[type] == c)
        return c;
    return (c->set[type] = get_set(c->set[type], type));
}

/* Union sets */
void set_union(city_t *a, city_t *b, type_t type) {
    city_t *set = get_set(a, type);
    set->set[type] = get_set(b, type);
}

/* Compare roads */
int compare_roads(const void *a, const void *b) {
    road_t *x = (road_t *) a, *y = (road_t *) b;
    return x->dist_sq - y->dist_sq;
}

/* Find MST */
void mst(int threshold, int *num_states, double *roads, double *rails) {
    int i, j, num_roads, num_conns;
    for (i = 0, num_roads = 0; i < num_cities; i++) {
        city_t *a = &city[i];
        a->set[STATE] = a, a->set[CONNECTION] = a, a->visited = 0;
        for (j = i + 1; j < num_cities; j++) {
            road_t *r = &road[num_roads++];
            city_t *b = &city[j];
            r->c1 = a, r->c2 = b;
            r->dist_sq = SQ(a->x - b->x) + SQ(a->y - b->y);
        }
    }
    qsort(road, num_roads, sizeof (road_t), compare_roads);
    threshold = threshold * threshold;
    for (i = 0, num_conns = 0, *roads = 0, *rails = 0; 
            i < num_roads && num_conns < num_cities - 1; i++) {
        road_t *r = &road[i];
        if (get_set(r->c1, CONNECTION) != get_set(r->c2, CONNECTION)) {
            set_union(r->c1, r->c2, CONNECTION);
            num_conns++;
            if (r->dist_sq <= threshold) {
                set_union(r->c1, r->c2, STATE);
                *roads += sqrt(r->dist_sq);
            }
            else
                *rails += sqrt(r->dist_sq);
        }
    }
    for (i = 0, *num_states = 0; i < num_cities; i++) {
        city_t *state = get_set(&city[i], STATE);
        if (!state->visited)
            state->visited = 1, (*num_states)++;
    }
}

/* Main function */
int main() {
    int test, num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (test = 1; test <= num_tests; test++) {
        int i, threshold, num_states;
        double roads, rails;
        assert(scanf("%d %d", &num_cities, &threshold) != EOF);
        for (i = 0; i < num_cities; i++) {
            city_t *c = &city[i];
            assert(scanf("%d %d", &c->x, &c->y) != EOF);
        }
        mst(threshold, &num_states, &roads, &rails);
        printf("Case #%d: %d %d %d\n", test, num_states,
                ROUND(roads), ROUND(rails));
    }
    return EXIT_SUCCESS;
}
