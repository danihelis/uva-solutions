/* 474
 * Heads / Tails Probability
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_ENTRIES     1000001

typedef struct {
    char calc;
    int exp;
    double val;
} prob_t;

prob_t table[MAX_ENTRIES];

/* Calculate table of entries */
void calculate(int n) {
    if (!table[n].calc) {
        int h = n / 2;
        calculate(h);
        table[n].val = table[h].val * table[h].val * (n % 2 == 0 ? 1 : 0.5);
        table[n].exp = 2 * table[h].exp;
        while (table[n].val > 10) {
            table[n].exp++;
            table[n].val /= 10;
        }
        while (table[n].val < 1) {
            table[n].exp--;
            table[n].val *= 10;
        }
        table[n].calc = 1;
    }
}

/* Main function */
int main() {
    int n;
    memset(table, 0, sizeof (prob_t));
    table[0].exp = 0, table[0].val = 1, table[0].calc = 1;
    while (scanf("%d", &n) != EOF) {
        calculate(n);
        printf("2^-%d = %.3fe%d\n", n, table[n].val, table[n].exp);
    }
    return 0;
}
