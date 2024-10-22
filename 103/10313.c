/* 10313
 * Pay the Price
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_NUMBER 301
#define MAX_LINE 100

long count[MAX_NUMBER][MAX_NUMBER][MAX_NUMBER];
int maximum;

#define MIN(x, y) ((x) < (y) ? (x) : (y))

void complete_table(int up_to) {
    int coins, value, last, k;
    for (; maximum <= up_to; maximum++) {
        count[maximum][0][0] = 1;
        for (coins = 0; coins <= maximum; coins++) {
            count[0][coins][maximum] = 0;
            count[coins][0][maximum] = 0;
        }
        for (coins = 1; coins <= maximum; coins++) {
            long total = 0;
            for (value = maximum / coins; value <= maximum - coins + 1; value++) {
                for (k = 1; k <= coins && k * value <= maximum; k++) {
                    int money = maximum - k * value;
                    if (coins - k <= money) {
                        total += count[MIN(value - 1, money)][coins - k][money];
                    }
                } 
                count[value][coins][maximum] += total;
            }
            for (last = value; value <= maximum; value++) {
                count[value][coins][maximum] = count[last - 1][coins][maximum];
            }
        }
    }
}

/* Main function */
int main() {
    char line[MAX_LINE];
    count[0][0][0] = 1, maximum = 1;
    while (fgets(line, MAX_LINE, stdin) != NULL) {
        int value, i, first, last, parameters;
        long total;
        parameters = sscanf(line, "%d %d %d", &value, &first, &last);
        last = (parameters == 1 ? value : parameters == 2 ? first : last);
        first = (parameters == 3 ? first : 0);
        complete_table(value);
        for (i = first, total = 0; i <= MIN(last, value); i++) {
            total += count[value][i][value];
        }
        printf("%ld\n", total);
    }
    return 0;
}
