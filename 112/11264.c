/* 11264
 * Coin Collector
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
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        int n, coin, number, amount, last;
        assert(scanf("%d", &n) != EOF);
        amount = last = number = 0;
        for (; n > 0; n--) {
            assert(scanf("%d", &coin) != EOF);
            if (coin > amount) {
                last = amount;
                amount += coin;
                number++;
            }
            else
                amount = last + coin;
        }
        printf("%d\n", number);
    }
    return EXIT_SUCCESS;
}
