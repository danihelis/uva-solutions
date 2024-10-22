/* 914
 * Jumping Champion
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       1000000
#define MAX_PRIMES  100000

#define MAX_JUMPS   120

int prime[MAX_PRIMES], num_primes;

/* Compute primes */
void compute_primes() {
    char composite[MAX_N / 2];
    int i, n;
    long k;
    memset(composite, 0, MAX_N / 2);
    prime[0] = 2, num_primes = 1;
    for (i = 1; i < MAX_N / 2; i++)
        if (!composite[i]) {
            n = 2 * i + 1;
            assert(num_primes < MAX_PRIMES);
            prime[num_primes++] = n;
            for (k = (long) n * n; k < MAX_N; k += 2 * n)
                composite[k / 2] = 1;
        }
}

/* Get index position of n in prime list */
int get_position(int n, char last) {
    int start = 0, end = num_primes;
    while (start < end) {
        int middle = (start + end) / 2;
        if (prime[middle] == n)
            return middle + (last ? 1 : 0);
        else if (prime[middle] < n)
            start = middle + 1;
        else
            end = middle;
    }
    return start;
}

/* Find largest jumping value in sequence of primes */
int find_largest_jump(int a, int b) {
    int jumps[MAX_JUMPS];
    int i, end, highest, max, which;
    memset(jumps, 0, sizeof (jumps));
    i = get_position(a, 0), end = get_position(b, 1);
    for (highest = -1, i++; i < end; i++) {
        int jump = prime[i] - prime[i - 1] - 1;
        assert(jump < MAX_JUMPS);
        jumps[jump]++;
        if (jump > highest)
            highest = jump;        
    }
    for (i = max = which = 0; i <= highest; i++) 
        if (jumps[i] > max)
            max = jumps[i], which = i + 1;
        else if (jumps[i] == max)
            which = 0;
    return which;
}

/* Main function */
int main() {
    int k, tests, start, end;
    compute_primes();
    assert(scanf("%d", &tests) == 1);
    for (; tests > 0; tests--) {
        assert(scanf("%d %d", &start, &end) == 2);
        k = find_largest_jump(start, end);
        if (k == 0)
            puts("No jumping champion");
        else
            printf("The jumping champion is %d\n", k);
    }
    return EXIT_SUCCESS;
}
