/* 11360
 * Have Fun with Matrices
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_VALUE       10
#define MAX_N           10
#define MAX_STRING      15

#define SWAP(r0,c0,r1,c1)   do { \
        char swap = matrix[r0][c0]; \
        matrix[r0][c0] = matrix[r1][c1]; \
        matrix[r1][c1] = swap; \
    } while (0)

/* Main function */
int main() {
    int test, num_tests;
    assert(scanf("%d", &num_tests) == 1);
    for (test = 1; test <= num_tests; test++) {
        int i, j, n, ops;
        char matrix[MAX_N][MAX_N + 1], cmd;
        assert(scanf("%d", &n) == 1);
        for (i = 0; i < n; i++)
            assert(scanf(" %s", matrix[i]) == 1);        
        assert(scanf("%d", &ops) == 1);
        while (ops-- > 0) {
            int a, b;
            assert(scanf(" %c%*s", &cmd) == 1);
            switch (cmd) {
                case 'r':
                case 'c':
                    assert(scanf("%d %d", &a, &b) == 2);
                    --a, --b;
                    for (i = 0; i < n; i++)
                        if (cmd == 'r')
                            SWAP(a, i, b, i);
                        else
                            SWAP(i, a, i, b);
                    break;
                case 'i':
                case 'd':
                    for (i = 0; i < n; i++)
                        for (j = 0; j < n; j++)
                            matrix[i][j] = '0' + (MAX_VALUE + matrix[i][j] - '0' + 
                                    (cmd == 'i' ? 1 : -1)) % MAX_VALUE;
                    break;
                case 't':
                    for (i = 0; i < n - 1; i++)
                        for (j = i + 1; j < n; j++)
                            SWAP(i, j, j, i);
                    break;
            }
        }
        printf("Case #%d\n", test);
        for (i = 0; i < n; i++)
            puts(matrix[i]);
        puts("");
    }       
    return EXIT_SUCCESS;
}
