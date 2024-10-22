/* 377
 * Cowculations
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING      10
#define NUM_OPERATIONS  3
#define BASE            4

#define READ_NUMBER(n) do { \
        char _num[MAX_STRING]; \
        assert(scanf(" %s", _num) != EOF); \
        n = to_number(_num); \
    } while(0)

/* Convert a cow number from text to decimal */
int to_number(char *text) {
    static char SYMBOLS[] = "VUCD";
    int number = 0;
    for (; *text != 0; text++) {
        char *s = strchr(SYMBOLS, *text);
        assert(s != NULL);
        number = number * BASE + (s - SYMBOLS);
    }
    return number;
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    printf("COWCULATIONS OUTPUT\n");
    for (; num_tests > 0; num_tests--) {
        int num1, num2, k;
        READ_NUMBER(num1);
        READ_NUMBER(num2);
        for (k = 0; k < NUM_OPERATIONS; k++) {
            char op[MAX_STRING];
            assert(scanf(" %s", op) != EOF);
            switch (op[0]) {
                case 'A': num2 += num1; break;
                case 'R': num2 /= BASE; break;
                case 'L': num2 *= BASE; break;
            }
        }
        READ_NUMBER(num1);
        printf("%s\n", (num1 == num2 ? "YES" : "NO"));
    }
    printf("END OF OUTPUT\n");
    return 0;
}
