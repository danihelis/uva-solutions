/* 11953
 * Battleships
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_SIZE    100
#define MAX_STRING  (MAX_SIZE + 2)

#define EMPTY       '.'
#define SHIP        'x'
#define HIT_SHIP    '@'

char map[MAX_SIZE][MAX_STRING];
int size;

/* Compute number of alive ships in the map */
int compute_alive_ships() {
    int i, j, count;
    for (i = 0, count = 0; i < size; i++)
        for (j = 0; j < size; j++)
            if (map[i][j] != EMPTY) {
                int ni, nj, di, dj, alive;
                di = (i < size - 1 && map[i + 1][j] != EMPTY ? 1 : 0);
                dj = (j < size - 1 && map[i][j + 1] != EMPTY ? 1 : 0);
                for (ni = i, nj = j, alive = 0; ni < size && nj < size && 
                        map[ni][nj] != EMPTY; ni += di, nj += dj) {
                    alive |= map[ni][nj] == SHIP;
                    map[ni][nj] = EMPTY;
                }
                count += alive ? 1 : 0;
            }
    return count;
}

/* Main function */
int main() {
    int test, num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (test = 1; test <= num_tests; test++) {
        int i;
        assert(scanf("%d", &size) != EOF);
        for (i = 0; i < size; i++)
            assert(scanf(" %s", map[i]) != EOF);
        printf("Case %d: %d\n", test, compute_alive_ships());
    }
    return EXIT_SUCCESS;
}
