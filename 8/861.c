/* 861
 * Little Bishops
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       8
#define MAX_K       (MAX_N * MAX_N)
#define MAX(x,y)    ((x) > (y) ? (x) : (y))

int bin[MAX_N][MAX_K];
int empty[MAX_N][MAX_N];

/* Count bishops on board */
void count_bishops(int r, int c, int k, int d) {
    int i, m, t;
    struct {
        int row, col;
    } cols[MAX_N * 2];
    for (; r < MAX_N; r++, c = 0)
        for (; c < MAX_N; c++)
            if (empty[r][c] == 0) {
                empty[r][c] = 1;
                for (t = 0, i = 1; r + i < MAX_N; i++) {
                    if (c + i < MAX_N) {
                        empty[r + i][c + i] += -1;
                        cols[t].row = r + i, cols[t].col = c + i;
                        t++;
                    }
                    if (c - i >= 0) {
                        empty[r + i][c - i] += -1;
                        cols[t].row = r + i, cols[t].col = c - i;
                        t++;
                    }
                }
                m = MAX(r, MAX(c, d));
                for (i = m; i < MAX_N; i++)
                    bin[i][k]++;
                count_bishops(r, c + 1, k + 1, m);
                for (i = 0; i < t; i++)
                    empty[cols[i].row][cols[i].col] += 1;
                empty[r][c] = 0;
            }
}

/* Main function */
int main() {
    int n, k;
    memset(bin, 0, MAX_N * MAX_K * sizeof (int));
    memset(empty, 0, MAX_N * MAX_N * sizeof (int));
    count_bishops(0, 0, 0, 0);
    while (scanf("%d %d", &n, &k) == 2 && n > 0)
        printf("%d\n", k == 0 ? 1 : n <= MAX_N ? bin[n - 1][k - 1] : -1);
    return EXIT_SUCCESS;
}
