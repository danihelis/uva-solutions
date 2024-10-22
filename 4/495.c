/* 495
 * Fibonacci Freeze
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIGITS  500
#define BASE        1000000000
#define BASE_REP    "%09d"
#define MAX_NUMBERS 5001

typedef struct {
    int digit[MAX_DIGITS];
    int num_digits;
} bigint_t, *bigint_p;

bigint_t fibonacci[MAX_NUMBERS];
int last;

/* Set single digit */
void set_digit(bigint_p n, int v) {
    n->digit[0] = v;
    n->num_digits = 1;
}

/* Add two bigints a, b and store value on c */
void add(bigint_p a, bigint_p b, bigint_p c) {
    int i, carry;
    for (i = 0, carry = 0; carry > 0 || i < a->num_digits || i < b->num_digits; i++) {
        int sum = carry + (i < a->num_digits ? a->digit[i] : 0) +
                          (i < b->num_digits ? b->digit[i] : 0);
        c->digit[i] = sum % BASE;
        carry = sum / BASE;
    }
    assert(i < MAX_DIGITS);
    c->num_digits = i;
}

/* Print a bigint */
void print_bigint(bigint_p n) {
    int i;
    assert(n->num_digits > 0);
    printf("%d", n->digit[n->num_digits - 1]);
    for (i = n->num_digits - 2; i >= 0; i--) {
        printf(BASE_REP, n->digit[i]);
    }
}

/* Main function */
int main() {
    int n;
    set_digit(&fibonacci[0], 0);
    set_digit(&fibonacci[1], 1);
    last = 2;
    while (scanf("%d", &n) != EOF) {
        for (; last <= n; last++) {
            add(&fibonacci[last - 2], &fibonacci[last - 1], &fibonacci[last]);
        }
        printf("The Fibonacci number for %d is ", n);
        print_bigint(&fibonacci[n]);
        printf("\n");
    }
    return 0;
}
