/* 10491
 * Cows and Cars
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
    int cows, cars, shown;
    while (scanf("%d %d %d", &cows, &cars, &shown) != EOF) {
        double total = cows + cars;
        double win = ((cows + cars - 1) * cars) / 
            (total * (total - shown - 1));
        printf("%.5f\n", win);
    }
    return EXIT_SUCCESS;
}
