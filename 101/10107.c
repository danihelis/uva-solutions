/* 10107
 * What is the Median?
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_NUMBERS     10000

/* Main function */
int main() {
    int n = 0, read, vector[MAX_NUMBERS];
    while (scanf("%d", &read) != EOF) {
        int i, median;
        for (i = n++; i > 0 && read < vector[i - 1]; i--) {
            vector[i] = vector[i - 1];
        }
        vector[i] = read;
        median = (n % 2 == 1 ? vector[n / 2] : (vector[n / 2] + vector[n / 2 - 1]) / 2);
        printf("%d\n", median);
    }
    return 0;
}
