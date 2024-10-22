/* 10276
 * Hanoi Tower Troubles Again!
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   50

int peg[MAX_N + 1];

/* Fill pegs so that the sum of its first two numbers is perfect */
void fill_pegs() {
    int stack[MAX_N + 1], n, i, k, found;
    peg[0] = stack[0] = 1, n = 1;
    for (i = 2; n <= MAX_N; i++) {
        for (k = 0, found = 0; !found && k < n; k++) {
            int sum = i + stack[k];
            int root = sqrt(sum);
            found = root * root == sum;
        }
        if (found)
            stack[k - 1] = i;
        else {
            stack[n] = peg[n] = i;
            n++;
        }
    }
}


/* Main function */
int main() {
    int n;
    fill_pegs();
    assert(scanf("%*d") != EOF);
    while (scanf("%d", &n) != EOF)
        printf("%d\n", peg[n] - 1);
    return EXIT_SUCCESS;
}
