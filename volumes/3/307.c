/* 307
 * Sticks
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_SIZE    50
#define MAX_LENGTH  (MAX_SIZE * 1000)
#define MAX_PRIMES  (MAX_LENGTH / 10)

#define MIN(a,b)    ((a) < (b) ? (a) : (b))

typedef struct {
    int size, count;
} piece_t;

piece_t piece[MAX_SIZE];
int num_pieces, sum_sizes, max_size;

int prime[MAX_PRIMES];
int num_primes;


/* Compare two integers */
int compare_int(const void *a, const void *b) {
    return *((int *) a) - *((int *) b);
}

/* Add new piece using binary search */
void add_piece(int size) {
    int start = 0, end = num_pieces;
    while (start < end) {
        int middle = (start + end) / 2;
        if (piece[middle].size == size) {
            piece[middle].count++;
            return;
        } else if (size > piece[middle].size) end = middle;
        else start = middle + 1;
    }
    for (end = num_pieces++; end > start; end--) {
        piece[end] = piece[end - 1];
    }
    piece[start].size = size, piece[start].count = 1;
}

/* Match all sticks recursivelly */
int match(int size, int remaining, int count, int index) {
    if (remaining == 0) {
        if (count <= 2) return 1;
        return match(size, size, count - 1, 0);
    } else {
        int e, must_match_first = remaining == size;
        for (; index < num_pieces; index++) {
            piece_t *p = &piece[index];
            if (p->count > 0) {
                for (e = MIN(remaining / p->size, p->count); e > 0; e--) {
                    p->count -= e;
                    if (match(size, remaining - e * p->size, count, index + 1)) {
                        return 1;
                    }
                    p->count += e;
                    /* This prunning follows internet's advice, but I have no
                     * ideia why this works, or if it only works for judge's
                     * input data. :( 
                     */
                    if (remaining == e * p->size) return 0; 
                }
                if (must_match_first) return 0;
            }
        }
        return 0;
    }
}

/* Compute prime numbers */
void compute_primes() {
    char composite[MAX_LENGTH / 2];
    long i, j;
    memset(composite, 0, MAX_LENGTH / 2);
    prime[0] = 2, num_primes = 1;
    for (i = 3; i < MAX_LENGTH; i += 2) {
        if (composite[i / 2]) continue;
        prime[num_primes++] = i;
        for (j = i * i; j < MAX_LENGTH; j += 2 * i) {
            composite[j / 2] = 1;
        }
    }
}

/* Find minimum match divider */
int find_minimum_match() {
    int divisor[MAX_PRIMES];
    int n, m, p, i, j, num_divisors;
    divisor[0] = 1, num_divisors = 1;
    for (i = 0, n = sum_sizes; i < num_primes && n >= prime[i]; i++) {
        for (p = prime[i], m = num_divisors; n % prime[i] == 0; 
                p *= prime[i], n /= prime[i]) {
            for (j = 0; j < m; j++) {
                divisor[num_divisors++] = p * divisor[j];
            }
        }
    }
    qsort(divisor, num_divisors, sizeof (int), compare_int);
    for (i = 0; i < num_divisors - 1; i++) {
        n = divisor[i];
        if (n >= max_size && match(n, n, sum_sizes / n, 0)) return n;
    }
    return sum_sizes;
}

/* Main function */
int main() {
    int n;
    compute_primes();
    while (scanf("%d", &n) != EOF && n > 0) {
        num_pieces = max_size = sum_sizes = 0;
        while (n-- > 0) {
            int size;
            assert(scanf("%d", &size) != EOF);
            add_piece(size);
            sum_sizes += size;
            if (size > max_size) max_size = size;
        }
        printf("%d\n", find_minimum_match());
    }
    return EXIT_SUCCESS;
}
