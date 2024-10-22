/* 10579
 * Fibonacci Numbers
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_FIBOS   5000
#define MAX_DIGITS  150
#define BASE        1000000000
#define FMT_BASE    "%09d"

#define SET_ONE(f)  (f).digit[0] = 1; (f).num_digits = 1

typedef struct {
    int digit[MAX_DIGITS];
    int num_digits;
} bigint_t, *bigint_p;

bigint_t fibonacci[MAX_FIBOS];
int last;

/* Sum two big integers */
void sum(bigint_p r, bigint_p a, bigint_p b) {
    int i, carry;
    for (i = 0, carry = 0; carry > 0 || i < a->num_digits || i < b->num_digits; i++) {
        carry += (i < a->num_digits ? a->digit[i] : 0) + (i < b->num_digits ? b->digit[i] : 0);
        r->digit[i] = carry % BASE;
        carry /= BASE;
    }
    r->num_digits = i;
}

/* Print big integer */
void print(bigint_p n) {
    int i;
    printf("%d", n->digit[n->num_digits - 1]);
    for (i = n->num_digits - 2; i >= 0; i--) {
        printf(FMT_BASE, n->digit[i]);
    }
    printf("\n");
}

/* Main function */
int main() {
    int n;
    SET_ONE(fibonacci[0]);
    SET_ONE(fibonacci[1]);
    last = 2;
    while (scanf("%d", &n) != EOF) {
        for (; last < n; last++) {
            sum(&fibonacci[last], &fibonacci[last - 1], &fibonacci[last - 2]);
        }
        print(&fibonacci[n - 1]);
    }
    return 0;
}
