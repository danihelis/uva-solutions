/* 340
 * Master-Mind Hints
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_CODES   1000
#define MAX_VALUE   9

/* Main function */
int main() {
    int code[MAX_CODES], guess[MAX_CODES], count[MAX_VALUE], used[MAX_VALUE];
    int game = 0, n, i, valid, hard, soft;
    while (scanf("%d", &n) != EOF && n > 0) {
        memset(count, 0, MAX_VALUE * sizeof (int));
        for (i = 0; i < n; i++) {
            assert(scanf("%d", &code[i]) != EOF);
            count[code[i] - 1]++;
        }
        printf("Game %d:\n", ++game);
        for (valid = 1; valid; ) {
            for (i = 0; i < n; i++) {
                assert(scanf("%d", &guess[i]) != EOF);
            }
            if ((valid = guess[0] != 0)) {
                memcpy(used, count, MAX_VALUE * sizeof (int));
                for (i = 0, hard = 0; i < n; i++) {
                    if (code[i] == guess[i]) {
                        hard++;
                        used[guess[i] - 1]--;
                        guess[i] = 0;
                    }
                }
                for (i = 0, soft = 0; i < n; i++) {
                    if (guess[i] > 0 && used[guess[i] - 1] > 0) {
                        soft++, used[guess[i] - 1]--;
                    }
                }
                printf("    (%d,%d)\n", hard, soft);
            }
        }
    }
    return 0;
}
