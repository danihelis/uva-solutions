/* 10424
 * Love Calculator
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

/* Read a name and compute the sum */
int read_name() {
    char c;
    int sum = 0;
    while (scanf("%c", &c) != EOF && c != '\n') {
        if (isalpha(c)) {
            sum += tolower(c) - 'a' + 1;
        }
    }
    if (feof(stdin)) {
        return 0;
    }
    while (sum > 9) {
        int new_sum = 0;
        while (sum > 0) {
            new_sum += sum % 10;
            sum /= 10;
        }
        sum = new_sum;
    }
    return sum;
}

/* Main function */
int main() {
    while (1) {
        double a = read_name(), b = read_name();
        if (a <= 0 || b <= 0) {
            break;
        }
        printf("%.2f %%\n", 100 * (a <= b ? a / b : b / a));
    }
    return 0;
}
