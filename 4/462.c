/* 462
 * Bridge Hand Evaluator
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define NUM_SUITS   4
#define NUM_VALUES  4
#define NUM_CARDS   13
#define MAX_STRING  4

char suit[] = "SHDC";
char value[] = "AKQJ";

/* Main function */
int main() {
    char *p, card[MAX_STRING];
    while (scanf("%s ", card) != EOF) {
        int i, s, total[NUM_SUITS], have[NUM_SUITS], points, stops, max;
        for (i = 0; i < NUM_SUITS; i++) {
            total[i] = 0, have[i] = 0;
        }
        for (i = 0; i < NUM_CARDS; i++) {
            assert((p = strchr(suit, card[1])) != NULL);
            s = p - suit;
            total[s]++;
            p = strchr(value, card[0]);
            if (p != NULL) {
                have[s] |= 1 << (p - value);
            }
            if (i == NUM_CARDS - 1) {
                break;
            }
            assert(scanf("%s ", card) != EOF);
        }
        for (points = 0, stops = 0, s = 0; s < NUM_SUITS; s++) {
            int stop = 0;
            for (i = 0; i < NUM_VALUES; i++) {
                if (have[s] & (1 << i)) {
                    points += NUM_VALUES - i + (total[s] <= i ? -1 : 0);
                    stop |= (i < NUM_VALUES - 1 && total[s] >= i + 1);
                }
            }
            stops += stop ? 1 : 0;
        }
        if (points >= 16 && stops == NUM_SUITS) {
            printf("BID NO-TRUMP\n");
        }
        else {
            for (s = 0, max = 0; s < NUM_SUITS; s++) {
                points += (total[s] <= 1) ? 2 : (total[s] <= 2) ? 1 : 0;
                if (total[s] > total[max]) {
                    max = s;
                }
            }
            if (points >= 14) {
                printf("BID %c\n", suit[max]);
            }
            else {
                printf("PASS\n");
            }
        }
    }
    return 0;
}
