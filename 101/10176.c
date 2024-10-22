/* 10176
 * Ocean Deep! - Make it shallow!!
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define BASE        131071
#define MAX_DIGITS  1000

typedef struct {
    long digit[MAX_DIGITS];
    int num_digits;
} bigint_t;

/* Shift number and sum a value: R = 2*N + V */
void shift_and_sum(bigint_t *r, bigint_t *n, int value) {
    int i;
    long carry, sum;
    for (i = 0, carry = value; carry > 0 || i < n->num_digits; i++) {
        sum = carry + (i < n->num_digits ? n->digit[i] * 2 : 0);
        r->digit[i] = sum % BASE;
        carry /= BASE;
    }
    r->num_digits = i;
}

/* Read a number, change to base 131071 and check if is multiple */
int read_number_is_divisible(char digit) {
    bigint_t n, temp;
    n.num_digits = 0;
    do {
        shift_and_sum(&temp, &n, digit - '0');
        n = temp;
    } while (scanf(" %c", &digit) != EOF && digit != '#');
    return n.digit[0] == 0;
}

/* Main function */
int main() {
    char digit;
    while (scanf(" %c", &digit) != EOF)
        printf("%s\n", read_number_is_divisible(digit) ? "YES" : "NO");
    return EXIT_SUCCESS;
}
