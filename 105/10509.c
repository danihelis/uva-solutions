/* 10509
 * R U Kidding Mr. Feynman?
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   100

/* Main function */
int main() {
    double n;
    while (scanf("%lf", &n) == 1 && n > 0) {
        int low, high;
        double a, result;
        low = 0, high = MAX_N;
        while (low <= high) {
            int mid = (low + high) / 2;
            double cmp = n - mid * mid * mid;
            if (cmp >= 0)
                low = mid + 1;
            else 
                high = mid - 1;
        }
        a = high;
        result = a + (n - a * a * a) / (3.0 * a * a);
        printf("%.4f\n", result);
    }
    return EXIT_SUCCESS;
}
