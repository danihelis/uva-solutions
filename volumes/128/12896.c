/* 12896
 * Mobile SMS
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   100

char letter[10][5] = {" ", ".,?\"", "abc", "def", "ghi",
                      "jkl", "mno", "pqrs", "tuv", "wxyz"};

/* Main function */
int main() {
    int n;
    assert(scanf("%*d") != EOF);
    while (scanf("%d", &n) == 1) {
        int i, pos, index[MAX_N];
        for (i = 0; i < n; i++)
            assert(scanf("%d", &index[i]) == 1);
        for (i = 0; i < n; i++) {
            assert(scanf("%d", &pos) == 1);
            printf("%c", letter[index[i]][--pos]);
        }
        printf("\n");
    }
    return EXIT_SUCCESS;
}
