/* 10049
 * Self-describing Sequence
 * By Johan Schreiber
 */
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N   2000000000
#define MAX_F   675000

int table[MAX_F];
int size;

/* Obtain F(n)-1 using binary search */
int binary_search(int n) {
    int start = 0, end = size;
    while (start < end) {
        int middle = (start + end) / 2;
        if (table[middle] == n) return middle;
        if (table[middle] < n) start = middle + 1;
        else end = middle;
    }
    return start - 1;
}

/* Fill table with values. t[k] = min{n | F[n] = k} */
void fill_table() {
    int n, k, rep;
    table[0] = 1;
    size = 1;
    for (k = 1, n = 1; n <= MAX_N; k++, size++) {
        rep = binary_search(k) + 1;
        table[k] = table[k - 1] + rep;
        n += rep;
    }
}

/* Main function */
int main() {
    int n;
    fill_table();
    while (scanf("%d", &n) == 1 && n) {
        printf("%d\n", binary_search(n) + 1);
    }
    return EXIT_SUCCESS;
}
