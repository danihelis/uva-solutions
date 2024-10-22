/* 537
 * Artificial Intelligence?
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

/* Main function */
int main() {
    int test, num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (test = 1; test <= num_tests; test++) {
        double val, power = 0, current = 0, voltage = 0;
        int p_def = 0, i_def = 0, u_def = 0;
        char b, c, value[20];
        for (assert(scanf(" %c", &c) != EOF), b = 0; c != '\n'; assert(scanf("%c", &c) != EOF)) {
            if (c == '=') {
                char *v = value;
                while (scanf("%c", &c) != EOF && !isalpha(c)) {
                    *v = c;
                    v++;
                }
                *v = 0;
                sscanf(value, "%lf", &val);
                switch (c) {
                    case 'm': val /= 1e3; break;
                    case 'k': val *= 1e3; break;
                    case 'M': val *= 1e6; break;
                }
                switch (b) {
                    case 'P': power = val, p_def = 1; break;
                    case 'U': voltage = val, u_def = 1; break;
                    case 'I': current = val, i_def = 1; break;
                    default: assert(NULL);
                }
            }
            b = c;
        }
        printf("Problem #%d\n", test);
        if (!p_def) {
            printf("P=%.2fW\n\n", voltage * current);
        } 
        else if (!i_def) {
            assert(voltage != 0);
            printf("I=%.2fA\n\n", power / voltage);
        }
        else {
            assert(!u_def && current != 0);
            printf("U=%.2fV\n\n", power / current);
        }
    }
    return 0;
}
