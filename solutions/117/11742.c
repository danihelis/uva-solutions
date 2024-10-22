/* 11742
 * Social Constraints
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       8
#define MIN(a,b)    ((a) < (b) ? (a) : (b))
#define MAX(a,b)    ((a) > (b) ? (a) : (b))

int constraint[MAX_N][MAX_N][2];
int permut[MAX_N];
char used[MAX_N];
int n, num_permuts;

/* Create a permutation */
void create_permutation(int index) {
    if (index >= n) num_permuts++;
    else {
        int i, j, allowed;
        for (i = 0; i < n; i++) {
            if (used[i]) continue;
            for (j = 0, allowed = 1; allowed && j < index; j++) {
                int *con = constraint[i][permut[j]];
                allowed = (index - j) >= con[0] && (index - j) <= con[1];
            }
            if (!allowed) continue;
            used[i] = 1, permut[index] = i;
            create_permutation(index + 1);
            used[i] = 0;
        }
    }
}

/* Main function */
int main() {
    int m;
    while (scanf("%d %d", &n, &m) != EOF && n > 0) {
        int i, j, k;
        for (i = num_permuts = 0; i < n; i++) {
            used[i] = 0;
            for (j = 0; j< n; j++) {
                constraint[i][j][0] = 0, constraint[i][j][1] = n;
            }
        }
        while (m-- > 0) {
            assert(scanf("%d %d %d", &i, &j, &k) != EOF);
            if (k < 0) {
                constraint[i][j][0] = constraint[j][i][0] = MAX(-k,
                        constraint[i][j][0]);
            } else if (k > 0) {
                constraint[i][j][1] = constraint[j][i][1] = MIN(k,
                        constraint[i][j][1]);
            }
        }
        create_permutation(0);
        printf("%d\n", num_permuts);
    }
    return EXIT_SUCCESS;
}
