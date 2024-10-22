/* 1329
 * Corporative Network
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       20000
#define DIST(a,b)   (abs((a) - (b)) % 1000)

typedef struct enterprise_s {
    struct enterprise_s *center;
    int index, distance;
} enterprise_t;

enterprise_t enterprise[MAX_N];
int num_enterprises;


/* Initialize all enterprises as centers of themselves */
void init() {
    int i;
    for (i = 0; i < num_enterprises; i++) {
        enterprise_t *e = &enterprise[i];
        e->center = e, e->index = i, e->distance = 0;
    }
}

/* Return distance and update centers */
int get_distance(enterprise_t *e) {
    if (e->center == e) return e->distance;
    e->distance += get_distance(e->center);
    e->center = e->center->center;
    return e->distance;
}

/* Link a center enterprise to another enterprise */
void link(enterprise_t *a, enterprise_t *b) {
    int dist_b = get_distance(b);
    a->center = b->center;
    a->distance += DIST(a->index, b->index) + dist_b;
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    while (num_tests-- > 0) {
        char op = 0;
        assert(scanf("%d", &num_enterprises) != EOF);
        init();
        while (op != 'O') {
            int a, b;
            assert(scanf(" %c", &op) != EOF);
            switch (op) {
                case 'E':
                    assert(scanf("%d", &a) != EOF);
                    printf("%d\n", get_distance(&enterprise[a - 1]));
                    break;
                case 'I':
                    assert(scanf("%d %d", &a, &b) != EOF);
                    link(&enterprise[a - 1], &enterprise[b - 1]);
            }
        }
    }
    return EXIT_SUCCESS;
}
