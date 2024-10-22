/* 623
 * 500!
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define BASE        10000
#define BASE_FMT    "%04d"
#define MAX_DIGITS  800
#define MAX_NUMBERS 1001

typedef struct {
    int digit[MAX_DIGITS];
    int num_digits;
} bigint_t, *bigint_p;

bigint_t factorial[MAX_NUMBERS];
int last_factorial;

/* Multiply a bigint by a scalar */
void multiply(bigint_p r, bigint_p a, int scale) {
    int i, carry;
    for (i = 0, carry = 0; carry > 0 || i < a->num_digits; i++) {
        carry += (i < a->num_digits ? a->digit[i] * scale : 0);
        r->digit[i] = carry % BASE;
        carry /= BASE;
    }
    r->num_digits = i;
}

/* Print bigint */
void print_bigint(bigint_p n) {
    int i;
    printf("%d", n->digit[n->num_digits - 1]);
    for (i = n->num_digits - 2; i >= 0; i--) {
        printf(BASE_FMT, n->digit[i]);
    }
    printf("\n");
}

/* Main function */
int main() {
    int n;
    factorial[0].digit[0] = 1, factorial[0].num_digits = 1;
    last_factorial = 0;
    while (scanf("%d", &n) != EOF) {
        for (; n > last_factorial; last_factorial++) {
            int next = last_factorial + 1;
            multiply(&factorial[next], &factorial[last_factorial], next);
        }
        printf("%d!\n", n);
        print_bigint(&factorial[n]);
    }
    return 0;
}
