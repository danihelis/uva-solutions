/* 11137
 * Ingenuous Cubrency
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_COINS 20
#define MAX_VALUE 10010

long combinations[MAX_VALUE][MAX_COINS];
int coin[MAX_COINS];
int maximum;

#define CUBE(x) ((x) * (x) * (x))

/* Main function */
int main() {
    int i, k, money;
    for (i = 0; i < MAX_COINS; i++) {
        coin[i] = CUBE(i + 2);
        combinations[0][i] = 1;
    }
    maximum = 1;
    while (scanf("%d", &money) != EOF) {
        for (; maximum <= money; maximum++) {
            long total;
            for (i = 0, total = 1; i < MAX_COINS; i++) {
                for (k = 1; k * coin[i] <= maximum; k++) {
                    total += (i == 0 ? 1 : combinations[maximum - k * coin[i]][i - 1]);
                }
                combinations[maximum][i] = total;
            }
        }
        printf("%ld\n", combinations[money][MAX_COINS - 1]);
    }
    return 0;
}
