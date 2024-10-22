/* 305
 * Joseph
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_K       14
#define MAX_SIZE    (MAX_K * 2)

int result[MAX_K];

/* Simulate Joseph-go-round and check if last K elements are removed first */
int can_remove_last_ones(int n, int m) {
    int i, size, pos, who[MAX_SIZE];
    for (i = 0, size = 2 * n; i < size; i++) {
        who[i] = i;
    }
    pos = size - 1;
    while (size > n) {
        pos = (pos + m) % size;
        if (who[pos] < n) {
            return 0;
        }
        for (i = pos; i < size - 1; i++) {
            who[i] = who[i + 1];
        }
        size--;
        pos = (pos + size - 1) % size;
    }
    return 1;
}

/* Main function */
int main() {
    int k, m;
    memset(result, 0, sizeof (int) * MAX_K);
    while (scanf("%d", &k) != EOF && k > 0) {
        if (result[k] == 0) {
            for (m = k; !can_remove_last_ones(k, m); m++)
                ;
            result[k] = m;
        }
        printf("%d\n", result[k]);
    }
    return 0;
}
