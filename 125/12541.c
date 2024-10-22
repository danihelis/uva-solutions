/* 12541
 * Birthdates
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       100
#define MAX_STRING  20
#define MONTH       31
#define YEAR        (MONTH * 12)

/* Main function */
int main() {
    char younger[MAX_STRING], older[MAX_STRING];
    int n, max, min;
    assert(scanf("%d", &n) == 1);
    for (max = min = 0; n > 0; n--) {
        char name[MAX_STRING];
        int key, d, m, y;
        assert(scanf(" %s %d %d %d", name, &d, &m, &y) == 4);
        key = d + MONTH * m + YEAR * y;
        if (max == 0 || key > max)
            max = key, strcpy(younger, name);
        if (min == 0 || key < min)
            min = key, strcpy(older, name);
    }
    printf("%s\n%s\n", younger, older); 
    return EXIT_SUCCESS;
}
