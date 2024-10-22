/* 10790
 * How Many Points of Intersection?
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>

/* Main function */
int main() {
    long a, b, test = 0;
    while (scanf("%ld %ld", &a, &b) == 2 && a > 0)
        printf("Case %ld: %ld\n", ++test, a * b * (a - 1) * (b - 1) / 4);
    return EXIT_SUCCESS;
}
