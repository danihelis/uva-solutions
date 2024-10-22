/* 10660
 * Citizen attention offices
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define DIM         5
#define AREA        (DIM * DIM)
#define INFINITY    (1 << 30)

int pop[DIM][DIM];
int sol[DIM], comb[DIM], best_cost;

/* Find best cost */
void find_best_cost(int index, int pos) {
    if (index == DIM) {
        int r, c, k, cost, min;
        for (r = cost = 0; r < DIM; r++)
            for (c = 0; c < DIM; c++)
                if (pop[r][c] > 0) {
                    for (min = INFINITY, k = 0; k < DIM; k++) {
                        int dr = abs(r - (comb[k] / 5)),
                            dc = abs(c - (comb[k] % 5));
                        int cur_cost = (dr + dc) * pop[r][c];
                        if (cur_cost < min)
                            min = cur_cost;
                    }
                    cost += min;
                }
        if (cost < best_cost) {
            for (k = 0; k < DIM; k++)
                sol[k] = comb[k];
            best_cost = cost;
        }
    }
    else
        for (; pos <= AREA - (5 - index); pos++) {
            comb[index] = pos;
            find_best_cost(index + 1, pos + 1);
        }
}

/* Main function */
int main() {
    int n;
    assert(scanf("%*d") != EOF);
    while (scanf("%d", &n) == 1) {
        memset(pop, 0, AREA * sizeof (int));
        for (; n > 0; n--) {
            int r, c, p;
            assert(scanf("%d %d %d", &r, &c, &p) == 3);
            pop[r][c] = p;
        }
        best_cost = INFINITY;
        find_best_cost(0, 0);
        for (n = 0; n < DIM; n++)
            printf("%d%c", sol[n], n == DIM - 1 ? '\n' : ' ');
    }
    return EXIT_SUCCESS;
}
