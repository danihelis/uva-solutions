/* 1388
 * Graveyard
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define LENGTH      10000.0
#define MIN(x,y)    ((x) < (y) ? (x) : (y))

/* Main function */
int main() {
    int n, m;
    while (scanf("%d %d", &n, &m) == 2) {
        if (m % n == 0)
            puts("0.0000");
        else {
            double total, post, last_post;
            int i, step;
            total = last_post = post = step = 0;
            m += n;
            for (i = 1; i < n; i++) {
                double place = LENGTH * i / n;
                while (post < place) {
                    last_post = post;
                    post = LENGTH * (++step) / m;
                }
                total += MIN(post - place, place - last_post);
            }
            printf("%.4f\n", total);
        }
    }
    return EXIT_SUCCESS;
}
