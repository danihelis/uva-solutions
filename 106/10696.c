/* 10696
 * f91
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_TABLE       100
#define NUM_RECURSION   2
#define F91(x)          ((x) <= MAX_TABLE ? 91 /* table[(x) - 1] */ : (x) - 10)

/* Main function */
int main() {
    int n;
    /*
    int table[MAX_TABLE];
    for (n = MAX_TABLE - 1; n >= 0; n--) {
        int i, f = n + 12;
        for (i = 0; i < NUM_RECURSION; i++) {
            f = F91(f);
        }
        table[n] = f;
    }
    */
    while (scanf("%d", &n) != EOF && n > 0) {
        printf("f91(%d) = %d\n", n, F91(n));
    }
    return 0;
}
