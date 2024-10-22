/* 10635
 * Prince and Princess
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       250
#define MAX_DIM     (MAX_N * MAX_N)
#define MAX(x,y)    ((x) > (y) ? (x) : (y))

int index[MAX_DIM];
int value[2][MAX_DIM];
int size[2];

/* Set index */
void set_index(int n, int *sequence, int size) {
    int i;
    memset(index, 0, n * n * sizeof (int));
    for (i = 0; i < size; i++)
        index[sequence[i] - 1] = i + 1;
}

/* Compute length of longest increasing subsequence */
int compute_length(int *sequence, int size) {
    int lowest[MAX_DIM];
    int length, i, k;
    for (i = 0, length = 0; i < size; i++) {
        int value = index[sequence[i] - 1];
        if (value > 0) {
            for (k = length; k > 0 && lowest[k - 1] > value; k--)
                ;
            lowest[k] = value;
            if (k == length)
                length++;
        }
    }
    return length;
}

/* Main function */
int main() {
    int i, j, n, test, num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (test = 0; test < num_tests; test++) {
        assert(scanf("%d %d %d", &n, &size[0], &size[1]) != EOF);
        for (i = 0; i < 2; i++)
            for (j = 0, size[i] += 1; j < size[i]; j++)
                assert(scanf("%d", &value[i][j]) != EOF);
        i = size[0] > size[1] ? 0 : 1;
        set_index(n, value[i], size[i]);
        n = compute_length(value[1 - i], size[1 - i]);
        printf("Case %d: %d\n", test + 1, n);
    }
    return EXIT_SUCCESS;
}
