/* 11634
 * Generate random numbers
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   10000

/* Compute max cycle */
int max_cycle(int n) {
    char visited[MAX_N];
    int cycles = 0;
    memset(visited, 0, MAX_N);
    while (!visited[n]) {
        int square = ((long) n * n) / 100;
        visited[n] = 1;
        n = square % MAX_N;
        cycles++;
    }
    return cycles;    
}

/* Main function */
int main() {
    int n;
    while (scanf("%d", &n) == 1 && n > 0)
        printf("%d\n", max_cycle(n));
    return EXIT_SUCCESS;
}
