/* 1605
 * Building for UN
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define NATION(x)   ((x) < 26 ? 'A' + (x) : 'a' + (x) - 26)

/* Main function */
int main() {
    int n, first = 1;
    while (scanf("%d", &n) != EOF) {
        int r, c, k;
        first ? first = 0 : printf("\n");
        printf("2 %d %d\n", n, n);
        for (k = 0; k < 2; k++) {
            for (r = 0; r < n; r++) {
                for (c = 0; c < n; c++) {
                    char nation = k == 0 ? r : c;
                    printf("%c", NATION(nation));
                }
                printf("\n");
            }
            if (k == 0) printf("\n");
        }
    }
    return EXIT_SUCCESS;
}
