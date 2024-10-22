/* 332
 * Rational Numbers from Repeating Fractions
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIGITS  9
#define MAX_STRING  (MAX_DIGITS + 4)

/* Calculates the greatest common divisor */
int gcd(int a, int b) {
    int remain;
    do {
        remain = a % b;
        a = b;
        b = remain;
    } while (remain > 0);
    return a;
}

/* Main function */
int main() {
    int test, j;
    test = 0;
    while (scanf("%d", &j) != EOF && j > -1) {
        char number[MAX_STRING], *p;
        int ten_size, ten_j, ten_k, i, dec, num, den;
        assert(scanf(" %s", number) != EOF);
        for (ten_size = 1,  ten_k = 1, ten_j = 1, i = 0, p = number + 2, dec = 0; 
                *p != 0; p++, i++) {
            dec = dec * 10 + *p - '0';
            ten_size *= 10;
            (i < j ? (void) (ten_j *= 10) : (void) (ten_k *= 10));
        }
        if (dec == 0) {
            printf("Case %d: 0/1\n", ++test);
            continue;
        }
        if (j > 0) {
            num = dec - dec / ten_j;
            den = ten_size - ten_k;
        }
        else {
            num = dec;
            den = ten_size;
        }
        dec = gcd(den, num);
        num /= dec, den /= dec;
        printf("Case %d: %d/%d\n", ++test, num, den);
    }
    return 0;
}
