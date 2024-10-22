/* 10487
 * Closest Sums
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       1000
#define MAX_SUM     (MAX_N * MAX_N / 2)

int sum[MAX_SUM], size;

/* Compare two ints */
int compare(const void *a, const void *b) {
    return * (int *) a - * (int *) b;
}

/* Find closest */
int closest(int n) {
    int start = 0, end = size;
    while (start < end) {
        int middle = (start + end) / 2;
        if (sum[middle] == n)
            return n;
        else if (sum[middle] > n)
            end = middle;
        else
            start = middle + 1;
    }
    if (start >= size)
        return sum[size - 1];
    if (start == 0)
        return sum[0];
    return (sum[start] - n) < (n - sum[start - 1]) ? sum[start] : 
            sum[start - 1];
}

/* Main function */
int main() {
    int test = 0, n, number[MAX_N];
    while (scanf("%d", &n) != EOF && n != 0) {
        int i, j, value, queries;
        for (i = 0, size = 0; i < n; i++) {
            assert(scanf("%d", &number[i]) != EOF);
            for (j = 0; j < i; j++)
                sum[size++] = number[i] + number[j];
        }
        qsort(sum, size, sizeof (int), compare);
        for (i = 1, j = 0; i < size; i++) {
            if (sum[i] != sum[j]) {
                sum[++j] = sum[i];
            }
        }
        size = j + 1;
        assert(scanf("%d", &queries) != EOF);
        printf("Case %d:\n", ++test);
        for (i = 0; i < queries; i++) {
            assert(scanf("%d", &value) != EOF);
            printf("Closest sum to %d is %d.\n", value, closest(value));
        }
    }
    return EXIT_SUCCESS;
}
