/* 413
 * Up and Down Sequences
 * By Johan Schreiber
 */
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UP              0
#define DOWN            1
#define UNDEFINED       2

/* Main function */
int main() {
    int value;
    while (scanf("%d", &value) == 1 && value) {
        int series[2] = {0, 0}, count[3] = {0, 0, 0};
        int i, previous = value, current = UNDEFINED, total = 1;

        while (scanf("%d", &value) == 1 && value) {
            int next = value < previous ? DOWN : value > previous ? UP :
                current;
            count[next]++, total++;
            if (next != current) {
                series[next]++;
                if (current == UNDEFINED) count[next] += count[UNDEFINED];
            }
            current = next, previous = value;
        }

        printf("Nr values = %d: ", total);
        for (i = 0; i < 2; i++) {
            double average = series[i] > 0 ? count[i] / (double) series[i] : 0;
            printf(" %.6f", average);
        }
        printf("\n");
    }
    return EXIT_SUCCESS;
}
