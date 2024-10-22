/* 12673
 * Football
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   100000

int score[MAX_N];
int num_scores;

/* Compare two integers in reverse order */
int compare(const void *a, const void *b) {
    return *((int *) b) - *((int *) a);
}

/* Main function */
int main() {
    int credits;
    while (scanf("%d %d", &num_scores, &credits) == 2) {
        int i, scored, received, total, index;
        for (i = 0; i < num_scores; i++) {
            assert(scanf("%d %d", &scored, &received) == 2);
            score[i] = scored - received;
        }
        qsort(score, num_scores, sizeof (int), compare);
        for (i = 0, total = 0, index = num_scores; i < num_scores; i++) {
            int s = score[i];
            if (s <= 0 && credits > -s) {
                credits -= 1 - s;
                s = 1;
            }
            if (s <= 0 && i < index) index = i;
            score[i] = s;
            total += s > 0 ? 3 : s == 0 ? 1 : 0;
        }
        for (i = index; credits > 0 && i < num_scores; i++) {
            int s = score[i];
            if (s < 0 && credits == -s) total += 1, credits = 0;
        }
        printf("%d\n", total);
    }
    return EXIT_SUCCESS;
}
