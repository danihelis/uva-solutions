/* 10427
 * Naughty Sleepy Boys
 * By Johan Schreiber
 */
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Get N-th digit from sequence, starting from 0 */
int get_nth_digit(int n) {
    int start = 1, end = 10, digits = 1;
    int number;

    while (n >= (end - start) * digits) {
        n -= (end - start) * digits;
        start = end;
        end *= 10;
        digits++;
    }

    number = start + (n / digits);
    n = digits - (n % digits) - 1;

    while (n-- > 0) {
        number /= 10;
    }
    return number % 10;
}

/* Main function */
int main() {
    int number;
    while (scanf("%d", &number) == 1) {
        printf("%d\n", get_nth_digit(number - 1));
    }
    return EXIT_SUCCESS;
}
