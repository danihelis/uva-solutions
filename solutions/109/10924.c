/* 10924
 * Prime Words
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

/* Check whether the number is prime */
int is_prime(int n) {
    if (n <= 2 || n % 2 == 0) {
        return n <= 2;
    }
    else {
        int i, p;
        for (i = 3, p = 1; p && i * i <= n; i += 2) {
            p = n % i != 0;
        }
        return p;
    }
}

/* Convert word into summation */
int into_sum(char *word) {
    int total;
    for (total = 0; *word != 0; word++) {
        total += (isupper(*word) ? *word - 'A' + 27 : *word - 'a' + 1);
    }
    return total;
}

/* Main function */
int main() {
    char word[30], p;
    while (scanf(" %s", word) != EOF) {
        p = is_prime(into_sum(word));
        printf("It is %sa prime word.\n", p ? "" : "not ");
    }
    return 0;
}
