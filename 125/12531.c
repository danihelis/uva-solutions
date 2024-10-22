/* 12531
 * Hours and Minutes
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>

/* Main function */
int main() {
    int n;
    while (scanf("%d", &n) != EOF)
        printf("%c\n", n % 6 == 0 ? 'Y' : 'N');
    return EXIT_SUCCESS;
}
