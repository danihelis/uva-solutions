/* 11342
 * Three-square
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_NUMBER  50000
#define LIMIT_ONE   130
#define LIMIT_TWO   160

typedef struct {
    int a, b, c;
} triple_t, *triple_p;

triple_t triple[MAX_NUMBER];

/* Main function */
int main() {
    int a, a2, b, b2, c, c2, ps, s;
    triple_p t;
    memset(triple, 0, MAX_NUMBER * sizeof (triple_t));
    for (a = 0; a < LIMIT_ONE; a++) {
        a2 = a * a;
        for (b = a; b < LIMIT_TWO; b++) {
            b2 = b * b;
            c = b, c2 = b2, ps = a2 + b2;
            while ((s = ps + c2) <= MAX_NUMBER) {
                t = &triple[s - 1];
                if (t->c == 0) {
                    t->a = a, t->b = b, t->c = c;
                }
                c++;
                c2 = c * c;
            }
        }
    }
    assert(scanf("%*d") != EOF);
    while (scanf("%d", &s) != EOF) {
        t = &triple[s - 1];
        (t->c == 0 ? printf("-1\n") : printf("%d %d %d\n", t->a, t->b, t->c));
    }
    return 0;
}
