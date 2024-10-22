/* 299
 * Train Swapping
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_SIZE 50

/* Main function */
int main() {
    int train[MAX_SIZE];
    int i, j, size, num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        int swaps = 0; 
        assert(scanf("%d", &size) != EOF);
        for (i = 0; i < size; i++) {
            assert(scanf("%d", &train[i]) != EOF);
        }
        for (i = 0; i < size; i++) {
            for (j = 1; j < size - i; j++) {
                if (train[j - 1] > train[j]) {
                    int temp = train[j - 1];
                    train[j - 1] = train[j];
                    train[j] = temp;
                    swaps++;
                }
            }
            assert(train[j - 1] == j);
        }
        printf("Optimal train swapping takes %d swaps.\n", swaps);
    }
    return 0;
}
