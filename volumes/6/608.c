/* 608
 * Counterfeit Dollar
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_COINS       (12)
#define MAX_STRING      (MAX_COINS + 2)
#define NUM_BALANCES    3
#define NUM_PLATES      2

typedef enum {
    UNUSED,
    LIGHT,
    HEAVY,
    NORMAL
} weight_t;

typedef struct {
    char plate[NUM_PLATES][MAX_STRING];
    weight_t weight[NUM_PLATES];
} balance_t;

/* Main function */
int main() {
    weight_t coin[MAX_COINS];
    balance_t balance[NUM_BALANCES];
    int num_tests;
    assert(scanf("%d ", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        int c, i, k, found, solution = 0;
        char *p;
        weight_t solution_weight = UNUSED;

        for (i = 0; i < NUM_BALANCES; i++) {
            char tilt[MAX_STRING];
            assert(scanf("%s %s %s ", balance[i].plate[0], balance[i].plate[1], tilt) != EOF);
            balance[i].weight[0] = tilt[0] == 'e' ? NORMAL : tilt[0] == 'd' ? LIGHT : HEAVY;
            balance[i].weight[1] = tilt[0] == 'e' ? NORMAL : tilt[0] == 'u' ? LIGHT : HEAVY;
        }

        for (c = 0; c < MAX_COINS; c++) {
            coin[c] = UNUSED;
        }
        for (i = 0; i < NUM_BALANCES; i++) {
            for (k = 0; k < NUM_PLATES; k++) {
                weight_t w = balance[i].weight[k];
                for (p = balance[i].plate[k]; *p != 0; p++) {
                    c = *p - 'A';
                    coin[c] = coin[c] != UNUSED && coin[c] != w ? NORMAL : w;
                }
            }
            if (balance[i].weight[0] != NORMAL) {
                for (c = 0; c < MAX_COINS; c++) {
                    int occur;
                    for (k = 0, occur = 0; coin[c] != NORMAL && !occur && k < NUM_PLATES; k++) {
                        occur = strchr(balance[i].plate[k], c + 'A') != NULL;
                    }
                    if (!occur) {
                        coin[c] = NORMAL;
                    }
                }
            }
        }
        for (i = 0, found = 0; !found && i < NUM_BALANCES; i++) {
            int total;
            for (k = 0, total = 0; k < NUM_PLATES; k++) {
                for (p = balance[i].plate[k]; *p != 0; p++) {
                    c = *p - 'A';
                    if (coin[c] != NORMAL) {
                        total++;
                        solution = c;
                        solution_weight = balance[i].weight[k];
                    }
                }
            }
            found = total == 1;
        }
        
        printf("%c is the counterfeit coin and it is %s.\n", solution + 'A',
                solution_weight == LIGHT ? "light" : "heavy");
    }
    return 0;
}
