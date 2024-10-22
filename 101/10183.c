/* 10183
 * How Many Fibs?
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_NUMBERS 500
#define MAX_DIGITS  15
#define BASE        1000000000
#define BASE_LOG    9
#define BASE_FMT    "%09d"
#define MAX_STRING  120

typedef struct {
    int digit[MAX_DIGITS];
    int num_digits;
} bigint_t, *bigint_p;

bigint_t fibonacci[MAX_NUMBERS];
int num_fibonacci;

/* Read number from string */
void read(bigint_p n, char *string) {
    char *p;
    for (n->num_digits = 0, p = string + strlen(string); p > string + BASE_LOG; n->num_digits++) {
        *p = 0;
        p -= BASE_LOG;
        n->digit[n->num_digits] = atoi(p);
    }
    *p = 0;
    n->digit[n->num_digits++] = atoi(string);
}

/* Sum two numbers */
void sum(bigint_p r, bigint_p a, bigint_p b) {
    int i, carry;
    for (i = 0, carry = 0; carry > 0 || i < a->num_digits || i < b->num_digits; i++) {
        carry += (i < a->num_digits ? a->digit[i] : 0) + (i < b->num_digits ? b->digit[i] : 0);
        r->digit[i] = carry % BASE;
        carry /= BASE;
    }
    r->num_digits = i;
}

/* Compare two numbers */
int compare(bigint_p a, bigint_p b) {
    int i;
    if (a->num_digits != b->num_digits) {
        return a->num_digits - b->num_digits;
    }
    for (i = a->num_digits - 1; i >= 0; i--) {
        if (a->digit[i] != b->digit[i]) {
            return a->digit[i] - b->digit[i];
        }
    }
    return 0;
}

/* Compute fibonacci numbers as demanded */
void compute_fibonacci(bigint_p a) {
    while (compare(a, &fibonacci[num_fibonacci - 1]) > 0) {
        sum(&fibonacci[num_fibonacci], &fibonacci[num_fibonacci - 1], 
                &fibonacci[num_fibonacci - 2]);
        num_fibonacci++;
    }
}

/* Find the closets fibonacci number */
int find(bigint_p n, int floor) {
    int start = 0, end = num_fibonacci;
    while (start < end) {
        int middle = (start + end) / 2;
        int comp = compare(n, &fibonacci[middle]);
        if (comp < 0) {
            end = middle;
        }
        else if (comp > 0) {
            start = middle + 1;
        }
        else {
            return middle;
        }
    }
    return start + (floor ? -1 : 0);
}

/* Main function */
#define SET(f, x)  (f).digit[0] = x; (f).num_digits = 1
int main() {
    char a[MAX_STRING], b[MAX_STRING];
    SET(fibonacci[0], 1);
    SET(fibonacci[1], 2);
    num_fibonacci = 2;
    while (scanf(" %s %s", a, b) != EOF && (strcmp(a, "0") || strcmp(b, "0"))) {
        bigint_t least, most;
        int lower, upper;
        read(&least, a), read(&most, b);
        compute_fibonacci(&most);
        lower = find(&least, 0), upper = find(&most, 1);
        printf("%d\n", upper - lower + 1);
    }
    return 0;
}
