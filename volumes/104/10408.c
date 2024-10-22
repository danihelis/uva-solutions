/* 10408
 * Farey sequences
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   1000

typedef struct {
    int num, den;
} frac_t;

frac_t valid[MAX_N][MAX_N];
int size[MAX_N];
frac_t sequence[MAX_N * MAX_N];
int length;

/* Determines if A and B are coprimes */
int gcd(int a, int b) {
    while (b > 0) {
        int m = a % b;
        a = b;
        b = m;
    }
    return a;
}

/* Determine all coprimes  */
void determine_valid_fractions() {
    int i, j;
    for (i = 1; i <= MAX_N; i++) {
        valid[i - 1][0].num = 1, valid[i - 1][0].den = i;
        size[i - 1] = 1;
        for (j = 2; j < i; j++)
            if (gcd(i, j) == 1) {
                valid[i - 1][size[i - 1]].num = j;
                valid[i - 1][size[i - 1]].den = i;
                size[i - 1]++;
            }
    }
}

/* Compare two fractions */
int compare(const void *a, const void *b) {
    frac_t *x = (frac_t *) a, *y = (frac_t *) b;
    return x->num * y->den - x->den * y->num;
}

/* Place all fraction numbers in a sequence */
void create_sequence(int n) {
    int i, j, length = 0;
    for (i = 0; i < n; i++)
        for (j = 0; j < size[i]; j++)
            sequence[length++] = valid[i][j];
    qsort(sequence, length, sizeof (frac_t), compare);
}

/* Main function */
int main() {
    int n, k;
    determine_valid_fractions();
    while (scanf("%d %d", &n, &k) != EOF) {
        create_sequence(n);
        k--;
        printf("%d/%d\n", sequence[k].num, sequence[k].den);
    }
    return EXIT_SUCCESS;
}
