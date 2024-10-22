/* 11115
 * Uncle Jack
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define BASE        10000
#define FORMAT      "%04d"
#define MAX_DIGITS  20

typedef struct {
    int digit[MAX_DIGITS], size;
} bigint_t;

/* Sum bigints */
void sum(bigint_t *r, bigint_t *a, bigint_t *b, int scale, int shift) {
    int i, carry;
    for (i = 0, carry = 0; carry > 0 || i < a->size ||
            i - shift < b->size; i++) {
        carry += (i < a->size ? a->digit[i] : 0) +
            (i >= shift && i -shift < b->size ? 
                b->digit[i - shift] * scale : 0);
        r->digit[i] = carry % BASE;
        carry /= BASE;
    }
    while (i > 0 && r->digit[i - 1] == 0)
        i--;
    r->size = i;
}

/* Multiply bigints */
void multiply(bigint_t *r, bigint_t *a, bigint_t *b) {
    bigint_t temp;
    int i;
    temp.size = 0;
    for (i = 0; i < a->size; i++)
        sum(&temp, &temp, b, a->digit[i], i);
    *r = temp;
}

/* Exponent */
void expo(bigint_t *r, int base, int power) {
    bigint_t multi;
    r->digit[0] = 1, r->size = 1;
    multi.digit[0] = base, multi.size = 1;
    while (power > 0) {
        if (power & 1)
            multiply(r, r, &multi);
        multiply(&multi, &multi, &multi);
        power >>= 1;
    }
}

/* Print */
void print_bigint(bigint_t *n) {
    int i;
    printf("%d", n->digit[n->size - 1]);
    for (i = n->size - 2; i >= 0; i--)
        printf(FORMAT, n->digit[i]);
    printf("\n");
}

/* Main function */
int main() {
    int n, k;
    while (scanf("%d %d", &k, &n) != EOF && k > 0) {
        bigint_t resp;
        expo(&resp, k, n);
        print_bigint(&resp);
    }
    return EXIT_SUCCESS;
}
