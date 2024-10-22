/* 147
 * Dollars
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_VALUE 7000
#define MAX_COINS 10

long combination[MAX_VALUE][MAX_COINS];
int coin[MAX_COINS] = {2, 4, 10, 20, 40, 100, 200, 400, 1000, 2000};

/* Main function */
int main() {
    int c, last = 0, money, cents;
    memset(combination, 0, MAX_VALUE * MAX_COINS * sizeof (long));
    while (scanf("%d.%d", &money, &cents) != EOF && !(cents == 0 && money == 0)) {
        long total = 0;
        money = (money * 100 + cents) / 5;
        for (; last <= money; last++) {
            for (c = 0, total = 1; c < MAX_COINS; c++) {
                for (cents = coin[c]; cents <= last; cents += coin[c]) {
                    total += (c == 0 ? 1 : combination[last - cents][c - 1]);
                }
                combination[last][c] = total;
            }
        }
        printf("%3d.%02d%17ld\n", money / 20, (money * 5) % 100, 
                combination[money][MAX_COINS - 1]);
    }
    return 0;
}
