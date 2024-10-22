/* 11955
 * Binomial Theorem
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
#define MAX_DIGITS      30
#define SET(n,v)        (n).digit[0] = (v); (n).size = 1

#define MAX_N           50
#define MIN(a,b)        ((a) < (b) ? (a) : (b))
#define PASCAL(k,i)     (pascal[(k) - 1][MIN(i,(k)-(i))])

#define MAX_STRING      100

typedef struct {
    int digit[MAX_DIGITS], size;
} bigint_t;

bigint_t pascal[MAX_N][MAX_N];

/* Sum bigint */
void sum(bigint_t *r, bigint_t *a, bigint_t *b) {
    int i, carry;
    for (i = carry = 0; carry > 0 || i < a->size || i < b->size; i++) {
        carry += (i < a->size ? a->digit[i] : 0) +
                 (i < b->size ? b->digit[i] : 0);
        r->digit[i] = carry % BASE;
        carry /= BASE;
    }
    r->size = i;
}

/* Print bigint */
void print_bigint(bigint_t *n) {
    int i;
    printf("%0d", n->digit[n->size - 1]);
    for (i = n->size - 2; i >= 0; i--)
        printf(FORMAT, n->digit[i]);
}

/* Compute all Pascal values */
void compute_pascal() {
    int i, n;
    for (n = 1; n <= MAX_N; n++) {
        SET(pascal[n - 1][0], 1);
        for (i = 1; i <= n / 2; i++)
            sum(&pascal[n - 1][i], &PASCAL(n - 1, i - 1), 
                    &PASCAL(n - 1, i));
    }
}

/* Print binomial */
void print_binomial(char *v1, char *v2, int k) {
    int i;
    for (i = 0; i <= k; i++) {
        if (i > 0 && i < k) {
            print_bigint(&PASCAL(k, i));
            printf("*");
        }
        if (i < k) {
            printf("%s", v1);
            if (i < k - 1)
                printf("^%d", k - i);
        }
        if (i > 0) {
            if (i < k)
                printf("*");
            printf("%s", v2);
            if (i > 1)
                printf("^%d", i);
        }
        if (i < k)
            printf("+");
    }
    printf("\n");
}

/* Main function */
int main() {
    int test, num_tests;
    compute_pascal();
    assert(scanf("%d", &num_tests) == 1);
    for (test = 1; test <= num_tests; test++) {
        char v1[MAX_STRING], v2[MAX_STRING];
        int k;
        assert(scanf(" (%[a-z]+%[a-z])^%d", v1, v2, &k) == 3);
        printf("Case %d: ", test);
        print_binomial(v1, v2, k);
    }
    return EXIT_SUCCESS;
}
