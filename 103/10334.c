/* 10334
 * Ray Through Glasses
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIGITS  50
#define BASE        1000000000
#define FMT_BASE    "%09d"
#define NUM_FIBBO   1001

typedef struct {
    int digit[MAX_DIGITS];
    int num_digits;
} bigint_t, *bigint_p;

bigint_t factorial[NUM_FIBBO];
int last;

/* Sum two bigints */
void sum(bigint_p r, bigint_p a, bigint_p b) {
    int carry, i;
    for (i = 0, carry = 0; carry || i < a->num_digits || i < b->num_digits; i++) {
        carry += (i < a->num_digits ? a->digit[i] : 0) + (i < b->num_digits ? b->digit[i] : 0);
        r->digit[i] = carry % BASE;
        carry /= BASE;
    }
    r->num_digits = i;
}

/* Print bigint */
void print(bigint_p n) {
    int i;
    printf("%d", n->digit[n->num_digits - 1]);
    for (i = n->num_digits - 2; i >= 0; i--) {
        printf(FMT_BASE, n->digit[i]);
    }
    printf("\n");
}

/* Main function */
#define SET(b,n)    (b).digit[0] = n; (b).num_digits = 1
int main() {
    int n;
    SET(factorial[0], 1);
    SET(factorial[1], 2);
    last = 2;
    while (scanf("%d", &n) != EOF) {
        for (; last <= n; last++) {
            sum(&factorial[last], &factorial[last - 1], &factorial[last - 2]);
        }
        print(&factorial[n]);
    }
    return 0;
}
