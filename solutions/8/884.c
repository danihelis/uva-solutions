/* 884
 * Factorial Factors
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       1000000
#define MAX_P       1000

typedef struct {
    int divisor, factors, sum;
} entry_t;

entry_t table[MAX_N];

/* Compute factors using sieve */
void compute_table() {
    int i, j;
    table[1].factors = 1, table[1].sum = 1;
    for (i = 3; i <= MAX_N; i++)
        table[i - 1].divisor = i % 2 == 0 ? 2 : 0;
    for (i = 3; i <= MAX_N; i++) {
        entry_t *e = &table[i - 1];
        if (e->divisor == 0) {
            e->factors = 1;
            for (j = i * i; i < MAX_P && j <= MAX_N; j += 2 * i)
                table[j - 1].divisor = i;
        }
        else
            e->factors = 1 + table[i / e->divisor - 1].factors;
        e->sum = table[i - 2].sum + e->factors;
    }
}

/* Main function */
int main() {
    int i;
    compute_table();
    while (scanf("%d", &i) != EOF)
        printf("%d\n", table[i - 1].sum);
    return EXIT_SUCCESS;
}
