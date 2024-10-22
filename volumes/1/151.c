/* 151
 * Power Crisis
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_NUMBERS 100
#define LAST_REGION 13

/* Determine last standing in a round-robin-josephus-whatever circle selection */
int last_standing(int n, int m) {
    int i, p, number[MAX_NUMBERS];
    for (i = 0; i < n; i++) {
        number[i] = i + 1;
    }
    p = -m;
    while (n > 1) {
        p = (p + m) % n;
        if (number[p] == LAST_REGION) {
            return 0;
        }
        for (i = p, n--; i < n; i++) {
            number[i] = number[i + 1];
        }
        p = (p == 0 ? n - 1 : p - 1);
    }
    return number[0] == LAST_REGION;
}

/* Main function */
int main() {
    int num_regions, stride;
    while (scanf("%d", &num_regions) != EOF && num_regions >= LAST_REGION) {
        stride = 1; 
        while (!last_standing(num_regions, stride)) {
            stride++;
        }
        printf("%d\n", stride);
    }
    return 0;
}
