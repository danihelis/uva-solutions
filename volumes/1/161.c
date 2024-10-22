/* 161
 * Traffic Lights
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_LIGHTS      102
#define MAX_TIME        (60 * 60 * 5)
#define YELLOW_TIME     5

/* Main function */
int main() {
    int cycle[MAX_LIGHTS];
    while (scanf("%d", &cycle[0]) != EOF && cycle[0] > 0) {
        int i, n, time, sync, smallest = cycle[0];
        n = 1;
        while (scanf("%d", &cycle[n]) != EOF && cycle[n] > 0) {
            if (smallest > cycle[n]) {
                smallest = cycle[n];
            }
            n++;
        }
        time = smallest;
        sync = 0;
        while (!sync && time <= MAX_TIME) {
            for (i = 0, sync = 1; sync && i < n; i++) {
                int phase = time / cycle[i], period = time % cycle[i];
                if (phase % 2 == 0 && period >= cycle[i] - YELLOW_TIME) {
                    phase++;
                }
                if (phase % 2 == 1) {
                    sync = 0;
                    time = (phase + 1) * cycle[i];
                }
            }
        }
        (sync ? printf("%02d:%02d:%02d\n", time / 3600, (time / 60) % 60, time % 60) :
                printf("Signals fail to synchronise in 5 hours\n"));
    }
    return 0;
}
