/* 10106
 * Product
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define BASE            10000
#define BASE_LOG        4
#define BASE_FMT        "%04d"
#define MAX_DIGITS      200
#define MAX_STRING      300

typedef struct {
    int digit[MAX_DIGITS];
    int num_digits;
} bigint_t, *bigint_p;

/* Convert into bigint */
void convert(bigint_p b, char *n) {
    char *p;
    int i;
    for (i = 0, p = n + strlen(n); p > n + BASE_LOG; i++) {
        p -= BASE_LOG;
        b->digit[i] = atoi(p);
        *p = 0;
    }
    b->digit[i++] = atoi(n);
    b->num_digits = i;
    while (b->num_digits > 0 && b->digit[b->num_digits - 1] == 0) {
        b->num_digits--;
    }
}

/* Sum two bigints with padding */
void sum(bigint_p r, bigint_p a, bigint_p b, int scale, int shift) {
    int i, carry;
    for (i = 0, carry = 0; carry > 0 || i < a->num_digits || i < b->num_digits + shift; i++) {
        carry += (i < a->num_digits ? a->digit[i] : 0) +
                (i >= shift && i < b->num_digits + shift ? scale * b->digit[i - shift] : 0);
        r->digit[i] = carry % BASE;
        carry = carry / BASE;
    }
    r->num_digits = i;
}

/* Multiply two bigints */
void multiply(bigint_p r, bigint_p a, bigint_p b) {
    int i;
    r->num_digits = 0;
    for (i = 0; i < a->num_digits; i++) {
        sum(r, r, b, a->digit[i], i);
    }
}

/* Print non-zero bigint */
void print(bigint_p b) {
    int i;
    printf("%d", b->digit[b->num_digits - 1]);
    for (i = b->num_digits - 2; i >= 0; i--) {
        printf(BASE_FMT, b->digit[i]);
    }
    printf("\n");
}

/* Main function */
int main() {
    bigint_t a, b, m;
    char number[MAX_STRING];
    while (scanf(" %s", number) != EOF) {
        convert(&a, number);
        assert(scanf(" %s", number) != EOF);
        convert(&b, number);
        if (a.num_digits == 0 || b.num_digits == 0) {
            printf("0\n");
        }
        else {
            multiply(&m, &a, &b);
            print(&m);
        }
    }
    return 0;
}
