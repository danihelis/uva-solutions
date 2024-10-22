/* 748
 * Exponentiation
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIGITS  200
#define MAX_STRING  10

typedef struct {
    int digit[MAX_DIGITS];
    int num_digits, dot;
} bigreal_t, *bigreal_p;

/* Sum two bigints, with no concern about being reals */
void sum(bigreal_p r, bigreal_p a, bigreal_p b, int scale, int shift) {
    int i, carry;
    for (i = 0, carry = 0; carry > 0 || i < a->num_digits || i < b->num_digits + shift; i++) {
        carry += (i < a->num_digits ? a->digit[i] : 0) +
            (i >= shift && i < b->num_digits + shift ? b->digit[i - shift] * scale : 0);
        r->digit[i] = carry % 10;
        carry /= 10;
    }
    r->num_digits = i;
}

/* Multiply two bigreals */
void multiply(bigreal_p r, bigreal_p a, bigreal_p b) {
    int i;
    r->num_digits = 0;
    for (i = 0; i < a->num_digits; i++) {
        sum(r, r, b, a->digit[i], i);
    }
    r->dot = a->dot + b->dot;
}

/* Compute exponentiation recursively */
void exponentiation(bigreal_p r, bigreal_p a, int exp) {
    if (exp == 0) {
        r->num_digits = 1, r->digit[0] = 1, r->dot = 0;
    }
    else if (exp == 1) {
        *r = *a;
    }
    else {
        bigreal_t result;
        exponentiation(&result, a, exp / 2);
        multiply(r, &result, &result);
        if (exp % 2 == 1) {
            multiply(&result, r, a);
            *r = result;
        }
    }
}

/* Convert string into bigreal */
void convert(bigreal_p n, char *string) {
    char *p;
    int i;
    for (p = string + strlen(string) - 1, i = 0; p >= string; p--) {
        if (isdigit(*p)) {
            n->digit[i++] = *p - '0';
        }
        else if (*p == '.') {
            n->dot = i;
        }
    }
    n->num_digits = i;
    for (; n->num_digits > 0 && n->digit[n->num_digits - 1] == 0; n->num_digits--)
        ;
}

/* Print bigreal */
void print_bigreal(bigreal_p n) {
    int i, prune;
    if (n->dot >= n->num_digits) {
        printf(".");
        for (i = n->dot; i > n->num_digits; i--) {
            printf("0");
        }
    }
    for (prune = 0; n->digit[prune] == 0 && prune < n->dot && prune < n->num_digits; prune++)
        ;
    for (i = n->num_digits - 1; i >= prune; i--) {
        printf("%d", n->digit[i]);
        if (n->dot == i && i > prune) {
            printf(".");
        }
    }
    printf("\n");
}

/* Main function */
int main() {
    char real[MAX_STRING];
    bigreal_t base, result;
    int exp;
    while (scanf(" %s %d", real, &exp) != EOF) {
        convert(&base, real);
        exponentiation(&result, &base, exp);
        print_bigreal(&result);
    }
    return 0;
}

