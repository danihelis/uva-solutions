/* 10127
 * Ones
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

/* Main function */
int main() {
    int number;
    while (scanf("%d", &number) != EOF) {
        int ones = 1, count = 1;
        while (ones != 0) {
            while (ones < number) {
                ones = ones * 10 + 1;
                count++;
            }
            ones = ones % number;
        }
        printf("%d\n", count);
    }
    return 0;
}
