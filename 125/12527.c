/* 12527
 * Different Digits
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   5000

int distinct[MAX_N + 1];

/* Has repeated digits? */
int repeated_digits(int n) {
    char repeated[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (; n > 0; n /= 10) {
        if (repeated[n % 10])
            return 1;
        repeated[n % 10] = 1;
    }
    return 0;
}

/* Main function */
int main() {
    int i, j;
    for (i = 1, distinct[0] = 0; i <= MAX_N; i++)
        distinct[i] = (1 - repeated_digits(i)) + distinct[i - 1];
    while (scanf("%d %d", &i, &j) != EOF)
        printf("%d\n", distinct[j] - distinct[i - 1]);
    return EXIT_SUCCESS;
}
