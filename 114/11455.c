/* 11455
 * Behold my quadrangle
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define SIZE 4

int compare(const void *a, const void *b) {
    return * (int *) b - * (int *) a;
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        int i, len[SIZE], sum;
        for (i = sum = 0; i < SIZE; i++) {
            assert(scanf("%d", &len[i]) != EOF);
            sum += len[i];
        }
        qsort(len, SIZE, sizeof (int), compare);
        printf("%s\n", len[0] == len[1] && len[2] == len[3] ? 
                    (len[1] == len[2] ? "square" : "rectangle") :
                sum - len[0] > len[0] ? "quadrangle" : "banana");
    }
    return EXIT_SUCCESS;
}
