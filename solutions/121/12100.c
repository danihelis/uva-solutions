/* 12100
 * Printer Queue
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       100
#define MAX_JOBS    9
#define MAX(x,y)    ((x) > (y) ? (x) : (y))

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) == 1);
    for (; num_tests > 0; num_tests--) {
        int job[MAX_N], count[MAX_JOBS], n, pos, delay, i, k;
        assert(scanf("%d %d", &n, &pos) == 2);
        memset(count, 0, MAX_JOBS * sizeof (int));
        for (i = 0; i < n; i++) {
            assert(scanf("%d", &job[i]) == 1);
            count[job[i] - 1]++;
        }
        for (k = MAX_JOBS, delay = i = 0; k >= job[pos]; k--)
            for (; count[k - 1] > 0; i = (i + 1) % n)
                if (i == pos && k == job[pos])
                    count[k - 1] = 0;
                else if (job[i] == k)
                    delay++, count[k - 1]--;
        printf("%d\n", delay + 1);
    }
    return EXIT_SUCCESS;
}
