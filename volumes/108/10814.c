/* 10814
 * Simplifying Fractions
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIGITS  10
#define BASE        10000
#define BASE_LEN    4
#define FORMAT      "%04d"
#define MAX_STRING  40

typedef struct {
    int digit[MAX_DIGITS], size;
} bigint_t;

bigint_t ZERO;

/* Parse string into bigint */
void parse(bigint_t *n, char *s) {
    int i;
    for (i = strlen(s) - BASE_LEN, n->size = 0; i >= 0; i -= BASE_LEN) {
        n->digit[n->size++] = atoi(s + i);
        s[i] = 0;
    }
    i = atoi(s);
    if (i > 0)
        n->digit[n->size++] = i;
}

/* Write */
void write(bigint_t *n) {
    int i;
    if (n->size == 0) {
        printf("0");
        return;
    }
    printf("%d", n->digit[n->size - 1]);
    for (i = n->size - 2; i >= 0; i--)
        printf(FORMAT, n->digit[i]);
}

/* Compare */
int compare(bigint_t *a, bigint_t *b) {
    int i;
    if (a->size != b->size)
        return a->size - b->size;
    for (i = a->size - 1; i >= 0; i--)
        if (a->digit[i] != b->digit[i])
            return a->digit[i] - b->digit[i];
    return 0;
}

/* Add */
void add(bigint_t *r, bigint_t *a, bigint_t *b, int shift, int scale) {
    int i, carry;
    for (i = 0, carry = 0; carry > 0 || i < a->size || 
            i < b->size + shift; i++) {
        carry += (i < a->size ? a->digit[i] : 0) + (i >= shift && 
                i - shift < b->size ? b->digit[i - shift] * scale : 0);
        r->digit[i] = carry % BASE;
        carry /= BASE;
    }
    while (i > 0 && r->digit[i - 1] == 0)
        i--;
    r->size = i;
}

/* Scale */
#define SCALE(r, n, shift, scale)   add(r, &ZERO, n, shift, scale)

/* Divide by factor */
int divide_by_factor(bigint_t *n, int factor) {
    int i, carry;
    for (i = n->size - 1, carry = 0; i >= 0; i--) {
        carry = carry * BASE + n->digit[i];
        n->digit[i] = carry / factor;
        carry %= factor;
    }
    for (; n->size > 0 && n->digit[n->size - 1] == 0; n->size--)
        ;
    return carry;
}

/* Subtract */
void subtract(bigint_t *r, bigint_t *a, bigint_t *b) {
    int i, deficit;
    for (i = 0, deficit = 0; i < a->size || i < b->size; i++) {
        int difference = (i < a->size ? a->digit[i] : 0) -
                (i < b->size ? b->digit[i] : 0) - deficit;
        deficit = difference >= 0 ? 0 : (BASE - 1 - difference) / BASE;
        r->digit[i] = difference + BASE * deficit;
    }
    while (i > 0 && r->digit[i - 1] == 0)
        i--;
    r->size = i;
}

/* Divide */
void divide(bigint_t *a, bigint_t *b, bigint_t *q, bigint_t *r) {
    int j, n, norm;
    bigint_t quota, op;
    
    /* Initialize */
    n = b->size;
    if (n == 1) {
        *q = *a;
        r->digit[0] = divide_by_factor(q, b->digit[0]);
        r->size = r->digit[0] > 0 ? 1 : 0;
        return;
    }

    /* Normalize */
    q->size = a->size - b->size + 1;
    norm = BASE / (b->digit[n - 1] + 1);
    SCALE(r, a, 0, norm);
    SCALE(&op, b, 0, norm);
    r->digit[r->size] = 0; /* Possible new digit on r */

    /* For each group on R (A) of size |B| + 1 */
    for (j = q->size - 1; j >= 0; j--) {
        /* Determine possible value of qj */
        int qj, rem, cmp, 
            prefix = r->digit[n + j] * BASE + r->digit[n + j - 1];
        qj = prefix / op.digit[n - 1];
        if (qj >= BASE)
            qj = BASE - 1;
        rem = prefix - qj * op.digit[n - 1];
        while (qj * op.digit[n - 2] > rem * BASE + r->digit[n + j - 2])
            qj--, rem += op.digit[n - 1];

        SCALE(&quota, &op, j, qj); /* quota = B * qj << j */
        cmp = compare(&quota, r);
        subtract(r, r, &quota);
        if (cmp > 0) { /* quota > R, must add carry */
            add(r, r, &op, j, 1);
            qj--;
            for (r->size--; r->size > 0 && r->digit[r->size - 1] == 0; 
                    r->size--) /* corrects value of R */
                ;
        }
        q->digit[j] = qj;
    }

    /* Denormalize */
    assert(divide_by_factor(r, norm) == 0);
    for (; q->size > 0 && q->digit[q->size - 1] == 0; q->size--)
        ;
}

/* Euclid's GCD, subtraction version */
void gcd(bigint_t *r, bigint_t a, bigint_t b) {
    while (b.size > 0) {
        bigint_t div, rem;
        divide(&a, &b, &div, &rem);
        a = b;
        b = rem;
    }
    *r = a;
}

/* Main function */
int main() {
    int num_tests;
    ZERO.size = 0;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        bigint_t a, b, g, d, r;
        char k, sa[MAX_STRING], sb[MAX_STRING];
        assert(scanf(" %s / %s", sa, sb) != EOF);
        parse(&a, sa), parse(&b, sb);
        gcd(&g, a, b);
        for (k = 0; k < 2; k++) {
            divide(k == 0 ? &a : &b, &g, &d, &r);
            assert(r.size == 0);
            write(&d);
            printf(k == 0 ? " / " : "\n");
        }
    }
    return EXIT_SUCCESS;
}
