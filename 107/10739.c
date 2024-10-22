/* 10739
 * String to Palindrome
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       1000
#define MAX_STR     (MAX_N + 2)
#define MIN(a,b)    ((a) < (b) ? (a) : (b))

/* Get minimum number of editions to obtain palindrome.
 * E[i,j] = min { 1 + E[i+1,j]
 *              { 1 + E[i,j-1]
 *              { E[i+1,j-1] + (s_i == s_j ? 0 : 1)
 * E[i,i] = 0
 */
int get_min_edition(char *string, int n) {
    int i, j, d, cost[MAX_N][MAX_N];
    for (i = 0; i < n - 1; i++)
        cost[i][i] = cost[i][i - 1] = 0;
    cost[n - 1][n - 1] = 0;
    for (d = 1; d < n; d++)
        for (i = 0, j = d; j < n; i++, j++) {
            int del = 1 + MIN(cost[i + 1][j], cost[i][j - 1]),
                xch = cost[i + 1][j - 1] + (string[i] == string[j] ? 0 : 1);
            cost[i][j] = MIN(del, xch);
        }
    return cost[0][n - 1];
}

/* Main function */
int main() {
    int num_tests, test;
    assert(scanf("%d", &num_tests) == 1);
    for (test = 1; test <= num_tests; test++) {
        char string[MAX_STR];
        assert(scanf(" %s", string) == 1);
        printf("Case %d: %d\n", test, 
                get_min_edition(string, strlen(string)));
    }
    return EXIT_SUCCESS;
}
