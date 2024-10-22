/* 12952
 * Tri-du
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>

/* Main function */
int main() {
    int a, b;
    while (scanf("%d %d", &a, &b) == 2)
        printf("%d\n", a > b ? a : b);
    return EXIT_SUCCESS;
}
