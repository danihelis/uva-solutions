/* 11879
 * Multiple of 17
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define VALUE       17
#define BASE        24137569 /* 17^6 */
#define MAX_DIGITS  20
#define MAX_STRING  110

typedef struct {
    int digit[MAX_DIGITS], num_digits;
} bigint_t;

/* Increase */
void increase(bigint_t *r, bigint_t *n, int scale, int value) {
    int i, carry;
    for (carry = value, i = 0; carry > 0 || i < n->num_digits; i++) {
        carry += (i < n->num_digits ? n->digit[i] * scale : 0);
        r->digit[i] = carry % BASE;
        carry /= BASE;
    }
    r->num_digits = i;
}

/* Main function */
int main() {
    char input[MAX_STRING], *i;
    while (scanf(" %s", input) != EOF && strcmp(input, "0") != 0) {
        bigint_t number, swap;
        number.num_digits = 0;
        for (i = input; *i != 0; i++) {
            increase(&swap, &number, 10, *i - '0');
            number = swap;
        }
        printf("%d\n", number.digit[0] % 17 == 0 ? 1 : 0); 

    }
    return EXIT_SUCCESS;
}
