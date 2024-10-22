/* 324
 * Factorial Frequencies
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define BASE            10000
#define LOG_BASE        4
#define MAX_DIGITS      500
#define MAX_FACTORIAL   370
#define NUM_DIGITS      10

typedef struct {
    int digit[MAX_DIGITS];
    int num_digits;
} bigint_t, *bigint_p;

typedef int digits_t[NUM_DIGITS];

bigint_t factorial;
int last_value;
digits_t table[MAX_FACTORIAL];

/* Set bigint value */
void set_bigint(bigint_p n, int v) {
    n->digit[0] = v;
    n->num_digits = 1;
}

/* Multiply a bigint by a scalar */
void scale_bigint(int m, bigint_p a, bigint_p c) {
    int i, carry;
    for (i = 0, carry = 0; carry > 0 || i < a->num_digits; i++) {
        int sum = carry + (i < a->num_digits ? m * a->digit[i] : 0);
        c->digit[i] = sum % BASE;
        carry = sum / BASE;
    }
    assert(i < MAX_DIGITS);
    c->num_digits = i;
}

/* Count number of digits of decimal base */
void count_digits(int n, digits_t *count, int sum_zeros) {
    int total = 0;
    while (n > 0) {
        (*count)[n % NUM_DIGITS]++;
        n /= NUM_DIGITS;
        total++;
    }
    (*count)[0] += (sum_zeros ? LOG_BASE - total : 0);
}

/* Count number of digits of bigint */
void count_digits_bigint(bigint_p n, digits_t *count) {
    int i;
    memset(*count, 0, sizeof (int) * NUM_DIGITS);
    for (i = 0; i < n->num_digits; i++) {
        count_digits(n->digit[i], count, i < n->num_digits - 1);
    }
}

/* Compute factorials up to n */
void compute_factorial(int n) {
    for (; last_value <= n; last_value++) {
        bigint_t result;
        scale_bigint(last_value, &factorial, &result);
        count_digits_bigint(&result, &table[last_value - 1]);
        factorial = result;
    }
}

/* Report the total of digits on bigint */
void report_digits(int n) {
    int i;
    printf("%d! --\n", n);
    for (i = 0; i < 10; i++) {
        printf("   (%d) %4d%s", i, table[n - 1][i], (i % 5 == 4 ? "\n" : " ")); 
    }
}

/* Main function */
int main() {
    int n;
    set_bigint(&factorial, 1), last_value = 1;
    while (scanf("%d", &n) != EOF && n > 0) {
        compute_factorial(n);
        report_digits(n);
    }
    return 0;
}
