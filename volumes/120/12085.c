/* 12085
 * Mobile Casanova
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  15

/* Main function */
int main() {
    char first[MAX_STRING], last[MAX_STRING], current[MAX_STRING];
    int first_num, last_num, current_num, index, i, n, test = 0;
    while (scanf("%d ", &n) != EOF && n > 0) {
        printf("Case %d:", ++test);
        for (i = 0, first_num = 0, last_num = 0, index = 0; i < n; i++) {
            assert(scanf("%s ", current) != EOF);
            current_num = atoi(current);
            if (current_num > last_num + 1) {
                (last_num > first_num ? printf("-%s\n", last + index) : printf("\n"));
                printf("%s", current);
                strcpy(first, current);
                first_num = current_num;
                index = strlen(current);
            }
            else {
                while (index > 0 && first[index - 1] != current[index - 1]) {
                    index--;
                }
            }
            strcpy(last, current);
            last_num = current_num;
        }
        (last_num > first_num ? printf("-%s\n\n", last + index) : printf("\n\n"));
    }
    return 0;
}
