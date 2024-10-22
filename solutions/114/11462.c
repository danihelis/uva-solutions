/* 11462
 * Age Sort
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_LENGTH 100

/* Main function */
int main() {
    int bucket[MAX_LENGTH];
    int size, i, j, first;
    while (scanf("%d", &size) != EOF) {
        if (size == 0) {
            break;
        }
        memset(bucket, 0, MAX_LENGTH * sizeof (int));
        for (i = 0; i < size; i++) {
            int age;
            assert(scanf("%d", &age) != EOF);
            bucket[--age]++;
        }
        for (first = 1, i = 0; i < MAX_LENGTH; i++) {
            for (j = 0; j < bucket[i]; j++) {
                (first ? first = 0 : printf(" "));
                printf("%d", i + 1);
            }
        }
        printf("\n");
    }
    return 0;
}
