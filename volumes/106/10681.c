/* 10681
 * Teobaldo's Trip
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_CITIES      100
#define ADD_LINK(a, b)  link[(a)][num_links[(a)]++] = (b)

int link[MAX_CITIES][MAX_CITIES];
int num_links[MAX_CITIES];
int num_cities;

/* Compute whether Teobaldo's trip is feasible */
int can_travel(int origin, int destination, int days) {
    char is_route[MAX_CITIES], can_travel[MAX_CITIES];
    int d, i, j;
    memset(can_travel, 0, num_cities);
    can_travel[destination] = 1;
    for (d = days - 1; d >= 0; d--) {
        memcpy(is_route, can_travel, num_cities);
        for (i = 0; i < num_cities; i++) {
            can_travel[i] = 0;
            for (j = 0; j < num_links[i] && !can_travel[i]; j++) {
                can_travel[i] = is_route[link[i][j]];
            }
        }
    }
    return can_travel[origin];
}

/* Main function */
int main() {
    int num_entries;
    while (scanf("%d %d", &num_cities, &num_entries) != EOF && num_cities > 0) {
        int i, start, end, days;
        memset(num_links, 0, num_cities * sizeof (int));
        for (i = 0; i < num_entries; i++) {
            int a, b;
            assert(scanf("%d %d", &a, &b) != EOF);
            a--, b--;
            ADD_LINK(a, b), ADD_LINK(b, a);
        }
        assert(scanf("%d %d %d", &start, &end, &days) != EOF);
        i = can_travel(--start, --end, days);
        printf("%s, Teobaldo can%s travel.\n", (i ? "Yes" : "No"), (i ? "" : " not"));
    }
    return 0;
}
