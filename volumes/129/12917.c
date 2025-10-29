/* 12917
 * Prop hunt!
 * By Johan Schreiber
 */
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Main function */
int main() {
    int p, h, o;
    while (scanf("%d %d %d", &p, &h, &o) == 3) {
        o -= p;
        printf("%s win!\n", h > o ? "Hunters" : "Props");
    }
    return EXIT_SUCCESS;
}
