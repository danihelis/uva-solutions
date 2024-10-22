/* 11687
 * Digits
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
    while (!feof(stdin)) {
        int n = 0, prev, i, s;
        char last, read = 0;
        do {
            last = read;
            read = getchar();
            n++;
        } while (isdigit(read));
        if (read != '\n')
            break;
        assert(n > 1);
        n--, i = 1, prev = last - '0';
        while (n > 1 || prev != 1) {
            prev = n;
            for (s = 0; n > 0; s++, n /= 10)
                ;
            n = s;
            i++;
        }
        printf("%d\n", i);
    }
    return EXIT_SUCCESS;
}
