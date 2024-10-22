/* 11677
 * Alarm Clock
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
    int h1, m1, h2, m2;
    while (scanf("%d %d %d %d", &h1, &m1, &h2, &m2) != EOF && 
            (h1 || m1 || h2 || m2)) {
        int hours, min = m2 - m1;
        if (min < 0)
            min += 60, h2--;
        hours = h2 - h1;
        if (hours < 0)
            hours += 24;
        min += hours * 60;
        printf("%d\n", min);
    }
    return EXIT_SUCCESS;
}
