/* 10596
 * Morning Walk
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N           200
#define MARK_EDGE(a,b)  (junction[a].edge[b] = 1, junction[a].degree++)

typedef struct {
    char edge[MAX_N], visited;
    int degree;
} junction_t;

junction_t junction[MAX_N];
int num_junctions;

/* Visit a junction recursivelly */
void visit_junction(int index) {
    junction_t *j = &junction[index];
    int i;
    j->visited = 1;
    for (i = 0; i < num_junctions; i++) {
        if (j->edge[i] && !junction[i].visited) visit_junction(i);
    }
}

/* Main function */
int main() {
    int num_roads;
    while (scanf("%d %d", &num_junctions, &num_roads) == 2) {
        int i, a, b, possible;
        memset(junction, 0, sizeof (junction_t) * num_junctions);
        possible = num_roads > 0;
        while (num_roads-- > 0) {
            assert(scanf("%d %d", &a, &b) == 2);
            MARK_EDGE(a, b);
            MARK_EDGE(b, a);
        }
        for (i = 0; possible && i < num_junctions; i++) {
            possible = junction[i].degree % 2 == 0;
        }
        if (possible) {
            for (i = 0; i < num_junctions; i++) {
                if (junction[i].degree > 0) {
                    visit_junction(i);
                    break;
                }
            }
            for (i = 0; possible && i < num_junctions; i++) {
                possible = junction[i].visited || junction[i].degree == 0;
            }
        }
        printf("%sPossible\n", possible ? "" : "Not ");
    }
    return EXIT_SUCCESS;
}
