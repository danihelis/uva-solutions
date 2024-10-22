/* 202
 * Repeating Decimals
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_NUMBER      3000
#define MAX_REMINDER    50
#define MAX_REM_STR     (MAX_REMINDER + 2)

int index[MAX_NUMBER];
char remind[MAX_REM_STR];

/* Main function */
int main() {
    int num, den;
    while (scanf("%d %d", &num, &den) != EOF) {
        int i, rem;
        char *p, repeat;
        printf("%d/%d = %d.", num, den, num / den);
        memset(index, -1, den * sizeof (int));
        for (i = 0, p = remind, rem = num % den; index[rem] == -1; i++) {
            index[rem] = i;
            rem *= 10;
            if (i < MAX_REMINDER) {
                *p = (rem / den) + '0';
                p++;
            }
            rem %= den;
        }
        *p = 0;
        repeat = remind[index[rem]];
        remind[index[rem]] = 0;
        printf("%s(%c%s%s)\n", remind, repeat, remind + index[rem] + 1, 
                i >= MAX_REMINDER ? "..." : "");
        printf("   %d = number of digits in repeating cycle\n\n", i - index[rem]);
    }
    return 0;
}
