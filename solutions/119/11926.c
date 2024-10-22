/* 11926
 * Multitasking
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DAYS   1000000

char schedule[MAX_DAYS];

/* Main function */
int main() {
    int n, m;
    while (scanf("%d %d", &n, &m) != EOF && (n > 0 || m > 0)) {
        int i, k, conflict, start, end, period;
        memset(schedule, 0, MAX_DAYS);
        for (i = 0, conflict = 0; i < n; i++) {
            assert(scanf("%d %d", &start, &end) != EOF);
            for (; !conflict && start < end; start++) {
                conflict = schedule[start] != 0;
                schedule[start] = 1;
            }
        }
        for (i = 0; i < m; i++) {
            assert(scanf("%d %d %d", &start, &end, &period) != EOF);
            for (; !conflict && start < MAX_DAYS;
                    start += period, end += period) {
                for (k = start; !conflict && k < end && k < MAX_DAYS; k++) {
                    conflict = schedule[k] != 0;
                    schedule[k] = 1;
                }
            }
        }
        printf("%sCONFLICT\n", conflict ? "" : "NO ");
    }
    return 0;
}
