/* 11222
 * Only I did it!
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N           1000
#define MAX_P           10001
#define NUM_PERSONS     3

int solved[NUM_PERSONS][MAX_N], unique[NUM_PERSONS][MAX_N];
int num_solved[NUM_PERSONS], num_uniques[NUM_PERSONS];
char problem[MAX_P];

/* Compare */
int compare(const void *a, const void *b) {
    return * (int *) a - * (int *) b;
}

/* Main function */
int main() {
    int test, num_tests;
    assert(scanf("%d", &num_tests) == 1);
    for (test = 1; test <= num_tests; test++) {
        int k, i, p, max;
        memset(problem, 0, sizeof (problem));
        for (k = 0; k < NUM_PERSONS; k++) {
            assert(scanf("%d", &max) == 1);
            for (i = num_solved[k] = 0; i < max; i++) {
                assert(scanf("%d", &p) == 1);
                if ((problem[p] & (1 << k)) == 0)
                    solved[k][num_solved[k]++] = p, problem[p] |= 1 << k;
            }
        }
        for (k = max = 0; k < NUM_PERSONS; k++) {
            for (i = num_uniques[k] = 0; i < num_solved[k]; i++) {
                int p = solved[k][i];
                if ((problem[p] & ~(1 << k)) == 0)
                    unique[k][num_uniques[k]++] = p;
            }
            if (num_uniques[k] > max)
                max = num_uniques[k];
        }
        printf("Case #%d:\n", test);
        for (k = 0; k < NUM_PERSONS; k++)
            if (num_uniques[k] == max) {
                printf("%d %d", k + 1, max);
                qsort(unique[k], num_uniques[k], sizeof (int), compare);
                for (i = 0; i < num_uniques[k]; i++)
                    printf(" %d", unique[k][i]);
                puts("");
            }
    }
    return EXIT_SUCCESS;
}
