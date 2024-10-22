/* 106
 * Fermat vs. Pythagoras
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       1000000

/* Euclid's GCD */
int gcd(int a, int b) {
    while (b > 0) {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

/* All the primitive Pythagorean triples (a, b, c) such that a² + b² = c²
 * and a, b, c are coprimes, can be produced by Euclid's formula:
 *      a = m² - n²,  b = 2·m·n,  c = m² + n²,
 * where m > n and m, n are coprime and not both odd.
 */
void compute(int max, int *triples, int *unused) {
    char used[MAX_N + 1];
    int m, n, n2, rep;
    memset(used, 0, max + 1);
    for (n = n2 = 1, rep = 1, *triples = 0; rep; n++) {
        for (m = n + 1, n2 = n * n; m * m + n2 <= max; m += 2)
            if (gcd(m, n) == 1) {
                int a = m * m - n2, 
                    b = 2 * m * n, 
                    c = m * m + n2;
                int x = a, y = b, z = c;
                (*triples)++;
                for (; z <= max; x += a, y += b, z += c)
                    used[x] = used[y] = used[z] = 1;
            }
        rep = m > n + 1;
    }
    for (n = 1, *unused = 0; n <= max; n++)
        *unused += used[n] ? 0 : 1;
}

/* Main function */
int main() {
    int n, triples, unused;
    while (scanf("%d", &n) != EOF) {
        compute(n, &triples, &unused);
        printf("%d %d\n", triples, unused);
    }
    return EXIT_SUCCESS;
}
