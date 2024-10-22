/* 10523
 * Very Easy !!!
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define BASE        100000
#define FORMAT      "%05d"
#define MAX_DIGITS  100

typedef struct {
    int digit[MAX_DIGITS], size;
} bigint_t;

/* Sum two bigints */
void sum_bigint(bigint_t *r, bigint_t *a, bigint_t *b, int scale) {
    int i, carry;
    for (i = 0, carry = 0; carry > 0 || i < a->size || i < b->size; i++) {
        carry += (i < a->size ? a->digit[i] : 0) + 
                (i < b->size ? b->digit[i] * scale : 0);
        r->digit[i] = carry % BASE;
        carry /= BASE;
    }
    r->size = i;
}

/* Print bigint */
void print_bigint(bigint_t *n) {
    int i;
    assert(n->size > 0);
    printf("%d", n->digit[n->size - 1]);
    for (i = n->size - 2; i >= 0; i--)
        printf(FORMAT, n->digit[i]);
    printf("\n");
}

/* Main function */
int main() {
    int i, n, a;
    bigint_t zero;
    zero.size = 0;
    while (scanf("%d %d", &n, &a) != EOF) {
        bigint_t sum, expo, result;
        if (a == 0) {
            printf("0\n");
            continue;
        }
        sum.size = 0;
        expo.digit[0] = 1, expo.size = 1;
        for (i = 1; i <= n; i++) {
            sum_bigint(&result, &zero, &expo, a);
            expo = result;
            sum_bigint(&result, &sum, &expo, i);
            sum = result;
        }
        print_bigint(&sum);
    }
    return EXIT_SUCCESS;
}
