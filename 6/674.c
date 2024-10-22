/* 674
 * Coin Change
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_MONEY 8000
#define MAX_COINS 4

int coin[MAX_COINS] = {5, 10, 25, 50};
long combination[MAX_MONEY][MAX_COINS];

/* Main function */
int main() {
    int i, k, top = 0, money;
    long result, total;
    while (scanf("%d", &money) != EOF) {
        for (; top <= money; top++) {
            for (i = 0, total = 1; i < MAX_COINS; i++) {
                for (k = 1; k * coin[i] <= top; k++) {
                    total += (i == 0 ? 1 : combination[top - k * coin[i]][i - 1]);
                }
                combination[top][i] = total;
            }
        }
        printf("%ld\n", result = combination[money][MAX_COINS - 1]);
    }
    return 0;
}
