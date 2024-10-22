/*
 * 10105
 * Polynomial Coefficients
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_PRIMES 5
#define MAX_NUMBER 12

const int prime_value[MAX_PRIMES] = {2, 3, 5, 7, 11};
const int prime_factor[MAX_NUMBER][MAX_PRIMES] = {
        /* 2  3  5  7  11 */
/*  1 */ { 0, 0, 0, 0, 0 },
/*  2 */ { 1, 0, 0, 0, 0 },
/*  3 */ { 0, 1, 0, 0, 0 },
/*  4 */ { 2, 0, 0, 0, 0 },
/*  5 */ { 0, 0, 1, 0, 0 },
/*  6 */ { 1, 1, 0, 0, 0 },
/*  7 */ { 0, 0, 0, 1, 0 },
/*  8 */ { 3, 0, 0, 0, 0 },
/*  9 */ { 0, 2, 0, 0, 0 },
/* 10 */ { 1, 0, 1, 0, 0 },
/* 11 */ { 0, 0, 0, 0, 1 },
/* 12 */ { 2, 1, 0, 0, 0 } };

int prime_fatorial[MAX_NUMBER][MAX_PRIMES];
int variables, exponent;


/* Calculate all fatorials */
void calculate_fatorials() {
    int i, f;
    for (f = 0; f < MAX_PRIMES; f++) {
        prime_fatorial[0][f] = 0;
    }
    for (i = 1; i < MAX_NUMBER; i++) {
        for (f = 0; f < MAX_PRIMES; f++) {
            prime_fatorial[i][f] = prime_fatorial[i - 1][f] + prime_factor[i][f];
        }
    }
}


/* Multiply or divide (when power is -1) a factorial by another one */
void multiply_by_factorial(int *a, int *b, int power) {
    int f;
    for (f = 0; f < MAX_PRIMES; f++) {
        a[f] += b[f] * power;
    }
}


/* Convert vector of primes into an integer variable */
unsigned int vector_to_number(int *a) {
    unsigned int number = 1;
    int f;
    for (f = 0; f < MAX_PRIMES; f++) {
        int i;
        for (i = 0; i < a[f]; i++) {
            number *= prime_value[f];
        }
    }
    return number;
}


/* Calculate coefficient of a monomial */
unsigned int monomial_coefficient() {
    int numerator[MAX_PRIMES];
    int denominator[MAX_PRIMES] = {0, 0, 0, 0, 0};
    int i;
    for (i = 0; i < variables; i++) {
        int monomial_power;
        assert(scanf("%d", &monomial_power) != EOF);
        if (monomial_power > 0) {
            multiply_by_factorial(denominator, prime_fatorial[monomial_power - 1], 1);
        }
    }
    memcpy(numerator, prime_fatorial[exponent - 1], sizeof (int) * MAX_PRIMES);
    multiply_by_factorial(numerator, denominator, -1);
    return vector_to_number(numerator);
}


/* Main function */
int main() {
    calculate_fatorials();
    while (scanf("%d %d", &exponent, &variables) != EOF) {
        printf("%d\n", monomial_coefficient());
    }
    return 0;
}
