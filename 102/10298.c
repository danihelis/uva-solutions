/* 10298
 * Power Strings
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_SIZE    1000010

/* Main function */
int main() {
    char input[MAX_SIZE], pattern[MAX_SIZE];
    while (scanf(" %s", input) != EOF && input[0] != '.') {
        int size = 0, repeat = 0, common = 0;
        char *head;
        for (head = input; *head != 0; head++) {
            if (pattern[common] == *head) {
                common++;
                if (common == size)
                    repeat++, common = 0;
            }
            else {
                int pos, i;
                for (pos = size; repeat > 0; repeat--)
                    for (i = 0; i < size; i++, pos++)
                        pattern[pos] = pattern[i];
                size = pos;
                pattern[size++] = *(head - common);
                head -= common;
                common = 0;
            }
        }
        printf("%d\n", common == 0 ? repeat + 1 : 1);
    }
    return EXIT_SUCCESS;
}
