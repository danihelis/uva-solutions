/* 11536
 * Smallest Sub-Array
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_K       100
#define INFINITY    1000000000
#define MIN(a,b)    ((a) < (b) ? (a) : (b))

int start[MAX_K];

/* Find smallest sequence containing all serial numbers */
int smallest_sequence(int n, int m, int k) {
    int i, j, x0, x1, x2, s, found, smallest, first;
    if (k <= 3) return k;
    memset(start, 0xff, k * sizeof (int));
    smallest = INFINITY;
    for (i = x0 = x1 = x2 = found = first = 0; i < n; i++) {
        if (i < 3) s = i + 1;
        else s = (x0 + x1 + x2) % m + 1;
        x0 = x1;
        x1 = x2;
        x2 = s;
        if (s > k) continue;
        s--;
        if (found == k && s == first) {
            int second = first == 0 ? 1 : 0;
            for (j = second + 1; j < k; j++) {
                if (j != first && start[j] < start[second]) second = j;
            }
            first = second;
            smallest = MIN(smallest, i - start[first] + 1);
        }
        if (start[s] < 0) {
            if (++found == k) {
                for (first = 0, j = 1; j < k; j++) {
                    if (j != s && start[j] < start[first]) first = j;
                }
                smallest = i - start[first] + 1;
            }
        }
        start[s] = i;
    }
    return smallest;
}

/* Main function */
int main() {
    int test, num_tests;
    assert(scanf("%d", &num_tests) == 1);
    for (test = 1; test <= num_tests; test++) {
        int answer, n, m, k;
        assert(scanf("%d %d %d", &n, &m, &k) == 3);
        answer = smallest_sequence(n, m, k);
        printf("Case %d: ", test);
        if (answer == INFINITY) printf("sequence nai\n");
        else printf("%d\n", answer);
    }
    return EXIT_SUCCESS;
}
