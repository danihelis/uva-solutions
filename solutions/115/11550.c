/* 11550
 * Demanding Dilemma
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       8
#define MAX_M       (MAX_N * MAX_N)
#define MAX_HASH    (1 << MAX_N)

int incident[MAX_N][MAX_M];
char hash[MAX_HASH];

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) == 1);
    while (num_tests-- > 0) {
        int i, e, vertices, edges, valid;
        assert(scanf("%d %d", &vertices, &edges) == 2);
        for (i = 0; i < vertices; i++) {
            for (e = 0; e < edges; e++) {
                assert(scanf("%d", &incident[i][e]) == 1);
            }
        }
        memset(hash, 0, sizeof (hash));
        for (e = 0, valid = 1; valid && e < edges; e++) {
            int degree, code;
            for (i = degree = code = 0; degree <= 2 && i < vertices; i++) {
                if (incident[i][e]) {
                    degree++;
                    code |= 1 << i;
                }
            }
            valid = degree == 2 && hash[code] == 0;
            hash[code] = 1;
        }
        printf("%s\n", valid ? "Yes" : "No");
    }
    return EXIT_SUCCESS;
}
