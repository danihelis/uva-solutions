/* 408
 * Uniform Generator
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

/* Greatest common divisor */
int gcd(int a, int b) {
    while (b > 0) {
        int rem = a % b;
        a = b;
        b = rem;
    }
    return a;
}

/* Main function */
int main() {
    int a, b;
    while (scanf("%d %d", &a, &b) != EOF)
        printf("%10d%10d    %s Choice\n\n", a, b, 
                gcd(a, b) > 1 ? "Bad" : "Good");
    return EXIT_SUCCESS;
}
