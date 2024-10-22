/* 12626
 * I ❤ Pizza
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  610
#define NUM_ING     6

const char ingredients[] = "MARGIT";
const int required[NUM_ING] = {1, 3, 2, 1, 1, 1};

/* Main function */
int main() {
    char input[MAX_STRING], *c, *p;
    assert(scanf("%*d") != EOF);
    while (scanf(" %s", input) == 1) {
        int i, min, count[NUM_ING] = {0, 0, 0, 0, 0, 0};
        for (c = input; *c != 0; c++) {
            p = strchr(ingredients, *c);
            if (p != NULL)
                count[p - ingredients]++;
        }
        for (i = 0, min = MAX_STRING; i < NUM_ING; i++)
            if (count[i] / required[i] < min)
                min = count[i] / required[i];
        printf("%d\n", min);        
    }
    return EXIT_SUCCESS;
}
