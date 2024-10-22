/* 11547
 * Automatic Answer
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
    int tests, answer;
    assert(scanf("%d", &tests) != EOF);
    for (; tests > 0; tests--) {
        double n;
        assert(scanf("%lf", &n) != EOF);
        n = (n * 567 / 9 + 7492) * 235 / 47 - 498;
        answer = (int) (n / 10 * (n > 0 ? 1 : -1)) % 10;
        printf("%d\n", answer);
    }
    return 0;
}
