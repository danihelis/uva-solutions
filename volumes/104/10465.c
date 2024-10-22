/* 10465
 * Homer Simpson
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#if 0
/* Dynamic programming solution */
#define MAX_N   10000
int main() {
    int v[2], c, h[MAX_N + 1], b[MAX_N + 1];
    while (scanf("%d %d %d", &v[0], &v[1], &c) != EOF) {
        int i, j, k;
        for (h[0] = b[0] = 0, i = 1; i <= c; i++) {
            h[i] = h[i - 1], b[i] = b[i - 1] + 1;
            for (k = 0; k < 2; k++) {
                j = i - v[k];
                if (j >= 0 && (b[j] < b[i] || 
                            (b[j] == b[i] && h[j] >= h[i])))
                    b[i] = b[j], h[i] = h[j] + 1;
            }
        }
        printf("%d", h[c]);
        (b[c] == 0 ? printf("\n") : printf(" %d\n", b[c]));
    }
    return EXIT_SUCCESS;
}
#endif

#define CEIL(x, y)          (((x) + (y) - 1) / (y))

/* Extended Euclid's GCD */
#define SWAP(a,b,exp)   do { int proc = exp; a = b; b = proc; } while (0)
int xgcd(int a, int b, int *x, int *y) {
    int x0 = 1, x1 = 0, y0 = 0, y1 = 1;
    while (b > 0) {
        int q = a / b;
        SWAP(a, b, a % b);
        SWAP(x0, x1, x0 - q * x1);
        SWAP(y0, y1, y0 - q * y1);
    }
    *x = x0, *y = y0;
    return a;
}

/* Main function */
int main() {
    int a, b, c;
    while (scanf("%d %d %d", &a, &b, &c) != EOF) {
        int g, x, y, nx, ny, sigx, sigy, s, k, t;
        t = 0, s = -1;
        while (s < 0) {
            g = xgcd(a, b, &x, &y);
            if (c % g != 0) {
                t += c % g;
                c -= c % g;
            }
            x *= c / g, y *= c / g;
            if (x <= 0)
                k = CEIL(abs(x), b / g), sigx = 1, sigy = -1;
            else
                k = CEIL(abs(y), a / g), sigx = -1, sigy = 1;
            nx = x + sigx * k * b / g, ny = y + sigy * k * a / g;
            while (nx >= 0 && ny >= 0 && nx + ny > s) {
                s = nx + ny;
                nx += sigx * b / g, ny += sigy * a / g;
            }
            if (s < 0)
                c -= g, t += g;
        }
        printf("%d", s);
        (t == 0 ? printf("\n") : printf(" %d\n", t));
    }
    return EXIT_SUCCESS;
}
