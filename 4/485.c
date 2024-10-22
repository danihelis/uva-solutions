/* 485
 * Pascal's Triangle of Death
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIGITS      11
#define BIGINT_BASE     1000000
#define BIGINT_PRINT    "%06d"
#define MAX_NUMBERS     500
#define LIMIT_DIGITS    11

typedef struct {
    int digit[MAX_DIGITS];
    int size;
} bigint_t;

bigint_t pascal[MAX_NUMBERS];

/* Set a initial value for bignumber */
void set_bigint(bigint_t *b, unsigned int value) {
    b->digit[0] = value;
    b->size = 1;
}

/* Sum two bignumbers */
void sum_bigint(bigint_t *c, bigint_t *a, bigint_t *b) {
    int i;
    long carry;
    for (i = 0, carry = 0; carry > 0 || i < a->size || i < b->size; i++) {
        long sum = (i < a->size ? a->digit[i] : 0) + (i < b->size ? b->digit[i] : 0) + carry;
        c->digit[i] = sum % BIGINT_BASE;
        carry = sum / BIGINT_BASE;
    }
    c->size = i;
}

/* Print bignumber */
void print_bignumber(bigint_t *n) {
    int i;
    for (i = n->size - 1; i >= 0; i--) {
        printf((i == n->size - 1 ? "%d" : BIGINT_PRINT), n->digit[i]);
    }
}

/* Main function */
int main() {
    int size = 1, exceed = 0, i;
    set_bigint(&pascal[0], 1);
    printf("1\n");
    while (!exceed) {
        assert(size < MAX_NUMBERS - 1);
        set_bigint(&pascal[size], 0);
        for (i = size; i > 0; i--) {
            sum_bigint(&pascal[i], &pascal[i], &pascal[i - 1]);
            exceed = exceed || pascal[i].size >= LIMIT_DIGITS;
        }
        size++;
        for (i = 0; i < size; i++) {
            print_bignumber(&pascal[i]);
            printf("%c", (i < size - 1 ? ' ' : '\n'));
        }
    }

    return 0;
}
