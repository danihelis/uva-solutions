/* 10387
 * Billiard
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
    int a, b, s, m, n;
    double pi = atan2(1, 1) * 4;
    while (scanf("%d %d %d %d %d", &a, &b, &s, &m, &n) == 5 && a) {
        double da = m * a, db = n * b;
        double ang = atan2(db, da) * 180 / pi;
        double dist = sqrt(da * da + db * db);
        printf("%.2f %.2f\n", ang, dist / s);
    }
    return EXIT_SUCCESS;
}
