/* 424
 * Integer Inquiry
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING      110
#define MAX_DIGITS      20
#define BASE            1000000000
#define LOGBASE         9
#define BASE_FMT        "%09d"

typedef struct {
    int digit[MAX_DIGITS];
    int num_digits;
} bigint_t, *bigint_p;

/* Sum */
void sum(bigint_p c, bigint_p a, bigint_p b) {
    int carry, i;
    for (i = 0, carry = 0; carry > 0 || i < a->num_digits || i < b->num_digits; i++) {
        carry += (i < a->num_digits ? a->digit[i] : 0) + (i < b->num_digits ? b->digit[i] : 0);
        c->digit[i] = carry % BASE;
        carry /= BASE;
    }
    c->num_digits = i;
}

/* Parse bigint */
void parse(bigint_p n, char *string) {
    char *p;
    int i;
    for (i = 0, p = string + strlen(string); p > string; i++) {
        *p = 0;
        p = (p - string >= LOGBASE ? p - LOGBASE : string);
        n->digit[i] = atoi(p);
    }
    n->num_digits = i;
}

/* Print bigint */
void print(bigint_p n) {
    int i = n->num_digits - 1;
    printf("%d", n->digit[i]);
    for (i -= 1; i >= 0; i--) {
        printf(BASE_FMT, n->digit[i]);
    }
    printf("\n");
}

/* Main function */
int main() {
    char line[MAX_STRING];
    bigint_t result, value;
    result.digit[0] = 0, result.num_digits = 1;
    while (scanf(" %s", line) != EOF) {
        parse(&value, line);
        sum(&result, &value, &result);
    }
    print(&result);
    return 0;
}
