/* 637
 * Booklet Printing
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_PAGES       100
#define PRINT_PAGE(i)   (i == 0 ? printf("Blank") : printf("%d", i))

/* Main function */
int main() {
    struct {
        int left, right;
    } page[MAX_PAGES];
    int n, c, i, max;
    while (scanf("%d", &n) != EOF && n > 0) {
        if (n == 1) {
            printf("Printing order for 1 pages:\nSheet 1, front: Blank, 1\n");
            continue;
        }
        for (i = 0, c = 0; 2 * c < n; i += 2, c += 2) {
            page[i].left = 0, page[i + 1].right = 0;
            page[i].right = c + 1, page[i + 1].left = c + 2;
        }
        max = i;
        for (i -= 2; i >= 0; i -= 2, c += 2) {
            page[i + 1].right = (c < n ? c + 1 : 0);
            page[i].left = (c + 1 < n ? c + 2 : 0);
        }
        printf("Printing order for %d pages:\n", n);
        for (i = 0; i < max; i += 2) {
            for (c = 0; c < 2; c++) {
                if (page[i + c].left != 0 || page[i + c].right != 0) {
                    printf("Sheet %d, %s: ", i / 2 + 1, c == 0 ? "front" : "back ");
                }
                PRINT_PAGE(page[i + c].left);
                printf(", ");
                PRINT_PAGE(page[i + c].right);
                printf("\n");
            }
        }
    }
    return 0;
}
