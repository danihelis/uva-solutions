/* 446
 * Kibbles "n" Bits "n" Bits "n" Bits 
 * by Daniel Donadon
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define SIZE    13

void convert(unsigned int n) {
    char string[SIZE + 1], *c;
    memset(string, '0', SIZE);
    string[SIZE] = 0;
    for (c = string + SIZE - 1; n > 0; c--, n /= 2)
        *c = '0' + n % 2;
    printf("%s", string);
}

int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        unsigned int a, b;
        char op;
        assert(scanf("%x %c %x", &a, &op, &b) != EOF);
        convert(a);
        printf(" %c ", op);
        convert(b);
        printf(" = %d\n", op == '+' ? a + b : a - b);
    }
    return 0;
}
