/* 10862
 * Connect the Cable Wires
 * By Johan Schreiber
 */
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BASE            10000
#define FORMAT          "%04d"
#define MAX_DIGITS      250

typedef struct {
    int digits[MAX_DIGITS];
    int num_digits;
} bigint_t;


/* Sum bigint with another after shift and multiplication by scalar */
void shift_sum(bigint_t *r, bigint_t *a, int shift, bigint_t *b, int scalar) {
    int i, carry;
    for (i = carry = 0; carry || i < a->num_digits ||
            i - shift < b->num_digits; i++) {
        carry += (i < a->num_digits ? a->digits[i] : 0) +
            (i >= shift && i - shift < b->num_digits ?
             b->digits[i - shift] * scalar : 0);
        r->digits[i] = carry % BASE;
        carry /= BASE;
    }
    r->num_digits = i;
}


/* Multiply bigints and a scalar */
void multiply(bigint_t *r, bigint_t *a, bigint_t *b, int scalar) {
    int i;
    r->num_digits = 0;
    for (i = 0; i < b->num_digits; i++) {
        shift_sum(r, r, i, a, b->digits[i] * scalar);
    }
}


/* Compute Fibonacci sequence using recurrence:
 * F(2n) = 2·F(n)·F(n-1) + F(n)²
 * F(2n-1) = F(n-1)² + F(n)²
 */
void fibonacci(int n, bigint_t *f2n, bigint_t *f2n1) {
    if (n <= 1) {
        f2n->num_digits = 1, f2n->digits[0] = 1;
        f2n1->num_digits = 1, f2n1->digits[0] = 1;
    } else {
        bigint_t fn, fn1, fnsq;
        if (n % 2 == 0) {
            fibonacci(n / 2, &fn, &fn1);
        } else {
            bigint_t ignore;
            fibonacci(n / 2, &fn1, &ignore);
            fibonacci(n / 2 + 1, &ignore, &fn);
        }

        multiply(&fnsq, &fn, &fn, 1);       /* F(n)² = F(n)·F(n) */
        multiply(f2n1, &fn1, &fn1, 1);      /* F(2n-1) = F(n-1)² */
        shift_sum(f2n1, f2n1, 0, &fnsq, 1); /*          + F(n)²  */

        multiply(f2n, &fn, &fn1, 2);        /* F(2n) = F(n)·F(n-1)·2 */
        shift_sum(f2n, f2n, 0, &fnsq, 1);   /*         + F(n)²       */
    }
}


/* Print bigint */
void print_bigint(bigint_t *n) {
    int i;
    printf("%d", n->num_digits > 0 ? n->digits[n->num_digits - 1] : 0);
    for (i = n->num_digits - 2; i >= 0; i--) {
        printf(FORMAT, n->digits[i]);
    }
    printf("\n");
}


/* Main function */
int main() {
    bigint_t f2n1, f2n;
    int n;

    while (scanf("%d", &n) == 1 && n > 0) {
        fibonacci(n, &f2n, &f2n1);
        print_bigint(&f2n);
    }
    return EXIT_SUCCESS;
}
