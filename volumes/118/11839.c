/* 11839
 * Optical Reader
 * By Johan Schreiber
 */
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Main function */
int main() {
    int n;
    while (scanf("%d", &n) == 1 && n > 0) {
        while (n-- > 0) {
            int i, value, answer = -1;

            for (i = 0; i < 5; i++) {
                assert(scanf("%d", &value) == 1);
                if (value <= 127) {
                    if (answer == -1) answer = i;
                    else answer = -2;
                }
            }
            printf("%c\n", answer < 0 ? '*' : answer + 'A');
        }
    }
    return EXIT_SUCCESS;
}
