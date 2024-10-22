/* 11203
 * Can you decide it for ME?
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  55

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        char string[MAX_STRING], *s;
        int valid, x, y, z, state;
        assert(scanf(" %s", string) != EOF);
        for (x = y = z = state = 0, s = string, valid = 1; 
                valid && *s != 0; s++) {
            switch (*s) {
                case '?': (state == 0 ? x++ : state == 1 ? y++ : z++);
                          break;
                case 'M': valid = state == 0;
                          state = 1;
                          break;
                case 'E': valid = state == 1;
                          state = 2;
                          break;
                default:
                          valid = 0;
            }
        }
        valid &= x > 0 && y > 0 && x == z - y;
        printf("%stheorem\n", valid ? "" : "no-");
    }
    return EXIT_SUCCESS;
}
