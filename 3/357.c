/* 357
 * Let Me Count The Ways
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_MONEY 40000
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
        result = combination[money][MAX_COINS - 1];
        printf("There %s %ld way%s to produce %d cents change.\n", 
                (result > 1 ? "are" : "is only"), result, (result > 1 ? "s" : ""), money);
    }
    return 0;
}
