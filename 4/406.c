/* 406
 * Prime Cuts
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_NUMBERS     1000
#define MAX(x,y)        ((x) > (y) ? (x) : (y))

int prime[MAX_NUMBERS];
int list_size[MAX_NUMBERS];
int num_primes, num_list;

/* Whether a number is prime or not */
int is_prime(int n) {
    int f;
    if (n <= 3) {
        return 1;
    }
    if (n % 2 == 0) {
        return 0;
    }
    for (f = 3; f * f <= n; f += 2) {
        if (n % f == 0) {
            return 0;
        }
    }
    return 1;
}

/* Main function */
int main() {
    int n, c, size, start;
    prime[0] = 1, list_size[0] = 1, num_primes = 1, num_list = 2;
    while (scanf("%d %d", &n, &c) != EOF) {
        for (; num_list <= n; num_list++) {
            if (is_prime(num_list)) {
                prime[num_primes++] = num_list;
            }
            list_size[num_list - 1] = num_primes;
        }
        start = (list_size[n - 1] + 1) / 2 - c;
        size = 2 * c - (list_size[n - 1] % 2 == 0 ? 0 : 1);
        printf("%d %d:", n, c);
        for (start = MAX(start, 0); size > 0 && start < list_size[n - 1]; size--, start++) {
            printf(" %d", prime[start]);
        }
        printf("\n\n");
    }
    return 0;
}
