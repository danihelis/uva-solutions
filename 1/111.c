/* 111
 * History Grading
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_NUMBERS 50

typedef int vector_t[MAX_NUMBERS + 1];

/* Main function */
int main() {
    vector_t grade, student, sequence;
    int i, j, n, input, max;
    assert(scanf("%d", &n) != EOF);
    for (i = 0; i < n; i++) {
        assert(scanf("%d", &grade[i]) != EOF);
    }
    while (scanf("%d", &input) != EOF) {
        student[--input] = 0;
        for (i = 1; i < n; i++) {
            assert(scanf("%d", &input) != EOF);
            student[--input] = i;
        }
        max = 0;
        for (i = 0; i < n; i++) {
            for (j = max - 1; j >= 0 && grade[student[i]] < sequence[j]; j--)
                ;
            sequence[j + 1] = grade[student[i]];
            if (j == max - 1) {
                max++;
            }
        }
        printf("%d\n", max);
    }
    return 0;
}
