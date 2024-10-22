/* 713
 * Adding Reversed Numbers
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIGITS 210

typedef char number_t[MAX_DIGITS];

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        number_t a, b, c;
        int z, carry;
        char *pa = a, *pb = b, *pc = c;

        assert(scanf(" %s %s", a, b) != EOF);
        for (carry = 0; *pa != 0 && *pb != 0; pa++, pb++, pc++) {
            int sum = (*pa - '0') + (*pb - '0') + carry;
            carry = (sum > 9 ? 1 : 0);
            *pc = (sum % 10) + '0';
        }
        for (z = 0; z < 2; z++) {
            char *p = (z ? pb : pa);
            for (; *p != 0; p++, pc++) {
                int sum = (*p - '0') + carry;
                carry = (sum > 9 ? 1 : 0);
                *pc = (sum % 10) + '0';
            }
        }
        if (carry) {
            *pc = carry + '0';
            pc++;
        }
        *pc = 0;
        
        for (pc = c; *pc == '0'; pc++)
            ;
        for (; *pc != 0; pc++) {
            printf("%c", *pc);
        }
        printf("\n");
    }
    return 0;
}
