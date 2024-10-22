/* 1583
 * Digit Generator
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   100000

int generator[MAX_N];

/* Compute generators upt o MAX_N */
void create_generators() {
    int i, n, g;
    memset(generator, 0, sizeof (generator));
    for (i = 1; i < MAX_N; i++) {
        for (g = n = i; n > 0; n /= 10)
            g += n % 10;
        if (g <= MAX_N && generator[g - 1] == 0)
            generator[g - 1] = i;
    }
}

/* Main function */
int main() {
    int n;
    create_generators();
    assert(scanf("%*d") != EOF);
    while (scanf("%d", &n) == 1) {
        printf("%d\n", generator[n - 1]);
    }
    return EXIT_SUCCESS;
}
