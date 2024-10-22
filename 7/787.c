/* 787
 * Maximum Sub-sequence Product
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define BASE            10000
#define FORMAT          "%04d"
#define MAX_DIGITS      200

#define LAST            -999999

typedef struct {
    int digit[MAX_DIGITS], num_digits, signal;
} bigint_t;

/* Set bigint */
void set(bigint_t *n, int v) {
    int i;
    n->signal = v < 0 ? -1 : 1;
    for (i = 0, v = abs(v); v > 0; i++, v /= BASE)
        n->digit[i] = v % BASE;
    n->num_digits = i;
}

/* Scale */
void scale(bigint_t *r, bigint_t *n, int scalar) {
    int i, carry;
    if (scalar == 0 || n->num_digits == 0) {
        r->num_digits = 0, r->signal = 1;
        return;
    }
    r->signal = n->signal * (scalar < 0 ? -1 : 1);
    for (i = 0, carry = 0, scalar = abs(scalar); 
            carry > 0 || i < n->num_digits; i++) {
        carry += (i < n->num_digits ? n->digit[i] * scalar : 0);
        r->digit[i] = carry % BASE;
        carry /= BASE;
    }
    r->num_digits = i;
}

/* Compare */
int compare(bigint_t *a, bigint_t *b) {
    if (a->signal != b->signal)
        return a->signal - b->signal;
    else if (a->num_digits != b->num_digits)
        return a->signal * (a->num_digits - b->num_digits);
    else {
        int i;
        for (i = a->num_digits - 1; i >= 0; i--)
            if (a->digit[i] != b->digit[i])
                return a->signal * (a->digit[i] - b->digit[i]);
        return 0;
    }
}

/* Print */
void print_bigint(bigint_t *n) {
    if (n->num_digits == 0)
        printf("0");
    else {
        int i;
        printf("%s%d", n->signal < 0 ? "-" : "", 
                n->digit[n->num_digits - 1]);
        for (i = n->num_digits - 2; i >= 0; i--)
            printf(FORMAT, n->digit[i]);
    }
}

/* Main function */
int main() {
    bigint_t current, positive, negative, highest;
    int number;
    while (scanf("%d", &number) != EOF) {
        set(&positive, number);
        highest = negative = positive;
        while (scanf("%d", &number) != EOF && number != LAST) {
            current = positive;
            scale(&positive, number > 0 ? &positive : &negative, number);
            scale(&negative, number > 0 ? &negative : &current, number);
            set(&current, number);
            if (compare(&positive, &current) < 0)
                positive = current;
            if (compare(&negative, &current) > 0)
                negative = current;
            if (compare(&positive, &highest) > 0)
                highest = positive;
        }
        print_bigint(&highest);
        printf("\n");
    }
    return EXIT_SUCCESS;
}
