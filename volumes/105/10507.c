/* 10507
 * Waking up brain
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_ZONES           26
#define ACTIVATION_NUMBER   3
#define INDEX(x)            ((x) - 'A')

typedef struct {
    char link[MAX_ZONES];
    char stimuli, waken, used;
} zone_t;

zone_t zone[MAX_ZONES];
int used[MAX_ZONES];
int num_zones;

/* Wake */
int wake(char init[]) {
    int i, j, year, total;
    int waken[MAX_ZONES], num_waken;
    for (i = 0, num_waken = 0; i < ACTIVATION_NUMBER; i++) {
        waken[num_waken++] = INDEX(init[i]);
    }
    year = -1, total = 0;
    while (num_waken > 0) {
        year++;
        for (i = 0; i < num_waken; i++) {
            int z = waken[i];
            zone[z].waken = 1, total++;
            for (j = 0; j < num_zones; j++) {
                int y = used[j];
                if (zone[z].link[y] && !zone[y].waken)
                    zone[y].stimuli++;
            }
        }
        for (i = 0, num_waken = 0; i < num_zones; i++) {
            int z = used[i];
            if (!zone[z].waken && zone[z].stimuli >= ACTIVATION_NUMBER)
                waken[num_waken++] = z;
        }
    }
    return total == num_zones ? year : -1;
}

/* Main function */
int main() {
    while (scanf("%d", &num_zones) != EOF) {
        int connections, i, num_used, years;
        char init[4];
        memset(zone, 0, MAX_ZONES * sizeof (zone_t));
        assert(scanf("%d", &connections) != EOF);
        assert(scanf(" %s", init) != EOF);
        for (i = 0, num_used = 0; i < ACTIVATION_NUMBER; i++) {
            int z = INDEX(init[i]);
            if (!zone[z].used) {
                zone[z].used = 1;
                used[num_used++] = z;
            }
        }
        for (; connections > 0; connections--) {
            int z[2];
            char c[2]; 
            assert(scanf(" %c%c", &c[0], &c[1]) != EOF);
            z[0] = INDEX(c[0]), z[1] = INDEX(c[1]);
            for (i = 0; i < 2; i++) {
                if (!zone[z[i]].used) {
                    zone[z[i]].used = 1;
                    used[num_used++] = z[i];
                }
                zone[z[i]].link[z[1 - i]] = 1;
            }
        }
        if (num_used < num_zones || (years = wake(init)) < 0)
            printf("THIS BRAIN NEVER WAKES UP\n");
        else
            printf("WAKE UP IN, %d, YEARS\n", years);
    }
    return 0;
}
