/* 10128
 * Queue
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       13
#define MAX_SIZE    (MAX_N + 3)

long seen[MAX_SIZE][MAX_SIZE];
long answer[MAX_SIZE][MAX_SIZE][MAX_SIZE];

/* Compute combinations of sequences of N heights, with K seen.
 * s(0,N) = 0 if N != 0, else 1
 * s(K,N) = sum{i=K-1..N-1} (N-1)! / i! · s(K-1,i)
 */
void compute_seen() {
    int i, k, n;
    long fat;
    for (k = 0; k <= MAX_N; k++) {
        for (n = 0; n <= MAX_N; n++) {
            if (k == 0) seen[k][n] = n == 0 ? 1 : 0;
            else {
                seen[k][n] = 0;
                for (i = n - 1, fat = 1; i >= k - 1; fat *= i--) {
                    seen[k][n] += fat * seen[k - 1][i];
                }
            }
        }
    }
}

/* Compute answers of sequences of N heights, W seen from west, E seen for east.
 * a(N,W,E) = sum{i=0..N-1} s(W-1,i) · s(E-1,N-1-i) · (n-1)! / i! / (n-1-i)!
 */
void compute_answers() {
    int n, w, e, i;
    long fat[MAX_SIZE];
    compute_seen();
    for (n = 1, fat[0] = 1; n <= MAX_N; n++) {
        fat[n] = fat[n - 1] * n;
        for (w = 0; w <= MAX_N; w++) {
            for (e = 0; e <= MAX_N; e++) {
                answer[n][w][e] = 0;
                for (i = 0; i < n; i++) {
                    long term = fat[n - 1] / fat[i] / fat[n - 1 - i];
                    answer[n][w][e] += term * seen[w - 1][i] * 
                        seen[e - 1][n - 1 - i];
                }
            }
        }
    }
}

/* Main function */
int main() {
    int num_tests, n, w, e;
    compute_answers();
    assert(scanf("%d", &num_tests) != EOF);
    while (num_tests-- > 0) {
        assert(scanf("%d %d %d", &n, &w, &e) != EOF);
        assert(n >= 1 && n <= MAX_N);
        if (w <= 0 || w > MAX_N || e <= 0 || w > MAX_N) printf("0\n");
        else printf("%ld\n", answer[n][w][e]);
    }
    return EXIT_SUCCESS;
}
