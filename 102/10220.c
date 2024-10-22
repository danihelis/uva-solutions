/* 10220
 * I Love Big Numbers !
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIGITS  1000
#define BASE        10000

typedef struct {
    int digit[MAX_DIGITS], size;
} bigint_t;

/* Scale */
void scale(bigint_t *n, int factor) {
    int i, carry;
    for (i = 0, carry = 0; carry > 0 || i < n->size; i++) {
        carry += i < n->size ? n->digit[i] * factor : 0;
        n->digit[i] = carry % BASE;
        carry /= BASE;
    }
    n->size = i;
    assert(i < MAX_DIGITS);
}

/* Sum digits */
int sum_digits(bigint_t *n) {
    int i, k, sum;
    for (i = 0, sum = 0; i < n->size; i++)
        for (k = n->digit[i]; k > 0; k /= 10)
            sum += k % 10;
    return sum;
}

/* Main function */
int main() {
    int sum[MAX_DIGITS], number, last;
    bigint_t bigint;
    bigint.digit[0] = 1, bigint.size = 1;
    last = 0;
    while (scanf("%d", &number) != EOF) {
        for (; last < number; last++) {
            scale(&bigint, last + 1);
            sum[last] = sum_digits(&bigint);
        }
        printf("%d\n", sum[number - 1]);
    }
    return EXIT_SUCCESS;
}
