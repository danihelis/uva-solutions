/* 948
 * Fibonaccimal Base
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       100000000
#define MAX_FIB     100

unsigned int fibbase[MAX_FIB], size;

/* Create Fibonacci base */
void create_fibbase() {
    int i;
    fibbase[0] = 1, fibbase[1] = 2;
    for (i = 2; fibbase[i - 1] < MAX_N; i++)
        fibbase[i] = fibbase[i - 1] + fibbase[i - 2];
    size = i - 1;
}

/* Binary find base for n */
int find_base(int n, int last) {
    int start = 0, end = last < 0 ? size : last;
    while (start < end) {
        int middle = (start + end) / 2;
        if (fibbase[middle] == n)
            return middle;
        else if (fibbase[middle] > n)
            end = middle;
        else 
            start = middle + 1;
    }
    return start - 1;
}

/* Convert into Fibonacci base */
void convert(int n) {
    int p, lastp = -1;
    while (n > 0) {
        p = find_base(n, lastp);
        if (lastp > 0)
            for (lastp--; lastp > p; lastp--)
                printf("0");
        else
            lastp = p;
        printf("1");
        n -= fibbase[p];
    }
    for (; lastp > 0; lastp--)
        printf("0");
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) == 1);
    create_fibbase();
    for (; num_tests > 0; num_tests--) {
        int n;
        assert(scanf("%d", &n) == 1);
        printf("%d = ", n);
        convert(n);
        printf(" (fib)\n");
    }
    return EXIT_SUCCESS;
}
