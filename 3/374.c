/* 374
 * Big Mod
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

long expmod(long b, long p, long m) {
    if (p == 0) {
        return 1;
    }
    else if (p == 1) {
        return b % m;
    }
    else {
        long res = expmod(b, p / 2, m);
        res = (res * res) % m;
        if (p % 2 == 1) {
            res = (res * (b % m)) % m;
        }
        return res;
    }
}

/* Main function */
int main() {
    long b, p, m;
    while (scanf("%ld %ld %ld", &b, &p, &m) != EOF) {
        printf("%ld\n", expmod(b, p, m));
    }
    return 0;
}
