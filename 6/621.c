/* 621
 * Secret Research
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d ", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        char first[4] = "\0\0\0", last[3] = "\0\0", digit;
        int count = 0;
        while (scanf("%c", &digit) != EOF && isdigit(digit)) {
            if (count < 3) {
                first[count] = digit;
            }
            last[0] = (count > 0 ? last[1] : digit);
            last[1] = (count > 0 ? digit : 0);
            count++;
        }
        if (count <= 2 && (!strcmp(first, "1") || !strcmp(first, "4") || !strcmp(first, "78"))) {
            printf("+\n");
        }
        else if (!strcmp(last, "35")) {
            printf("-\n");
        }
        else if (first[0] == '9' && last[1] == '4') {
            printf("*\n");
        }
        else if (!strcmp(first, "190")) {
            printf("?\n");
        }
    }
    return 0;
}
