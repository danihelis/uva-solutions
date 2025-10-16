/* 11327
 * Enumerating Rational Numbers
 * By Johan Schreiber
 */
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUMBER      200000
#define MAX_PRIME       500

typedef struct {
    char is_prime;
    int divisor;
    int totient;
    long index;
} number_t;

number_t numbers[MAX_NUMBER];

/* Compute primes and totients */
void compute_primes() {
    int i, j, p;
    for (i = 0; i < MAX_NUMBER; i++) {
        number_t *n = &numbers[i];
        n->is_prime = 1, n->totient = 0;
    }

    for (p = 2; p <= MAX_NUMBER; p++) {
        if (p < MAX_PRIME && numbers[p - 1].is_prime) {
            for (i = p * p; i <= MAX_NUMBER; i += p) {
                number_t *n = &numbers[i - 1];
                if (n->is_prime) {
                    n->is_prime = 0, n->divisor = 1;
                    for (j = i; j % p == 0; j /= p) {
                        n->divisor *= p;
                    }
                    if (j == 1) n->totient = i - i / p;
                }
            }
        }
    }

    /* special case for number 1 */
    numbers[0].index = 0;
    numbers[0].totient = 2;

    for (p = 2; p <= MAX_NUMBER; p++) {
        number_t *n = &numbers[p - 1], *a = &numbers[p - 2];
        if (!n->totient) {
            if (n->is_prime) {
                n->totient = p - 1;
            } else {
                n->totient = numbers[n->divisor - 1].totient *
                    numbers[p / n->divisor - 1].totient;
            }
        }
        n->index = a->index + a->totient;
    }
}

/* Find denominator using binary search */
int find_number(long index) {
    int start = 0, end = MAX_NUMBER;
    while (start < end) {
        int middle = (start + end) / 2;
        long cmp = numbers[middle].index - index;
        if (cmp == 0) return middle + 1;
        else if (cmp < 0) start = middle + 1;
        else end = middle;
    }
    return start;
}

/* Find numerator checking relative primes */
int find_nth_relative_prime(int number, long nth) {
    int i, j, p;
    char relatives[MAX_NUMBER];
    number_t *n = &numbers[number - 1];

    if (number == 1) return nth - 1;
    if (nth == 1 || n->is_prime) return nth;

    for (i = 1; i < number; i++) {
        relatives[i] = 1;
    }
    for (p = 2, i = 1; p < number; p++) {
        if (relatives[p - 1] && number % p == 0) {
            for (j = p; j < number; j += p) {
                relatives[j - 1] = 0;
            }
        }
        if (relatives[p - 1] && ++i >= nth) return p;
    }
    assert(NULL); /* couldn't find the number */
    return 0;
}

/* Main function */
int main() {
    long index;
    compute_primes();
    while (scanf("%ld", &index) == 1 && index > 0) {
        int den = find_number(index - 1);
        int num = find_nth_relative_prime(den, index - numbers[den - 1].index);
        printf("%d/%d\n", num, den);
    }
    return EXIT_SUCCESS;
}
