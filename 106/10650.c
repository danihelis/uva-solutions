/* 10650
 * Determinate Prime
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       32000
#define NUM_PRIMES  5000
#define NUM_SEQS    1000

typedef struct {
    int length, index, start, end;
} sequence_t;

int prime[NUM_PRIMES];
sequence_t sequence[NUM_SEQS];
int num_primes, num_sequences;

/* Compute all primes and uni-distance sequences */
void compute_prime_sequences() {
    char composite[MAX_N / 2];
    int i, j;
    memset(composite, 0, MAX_N / 2);
    prime[0] = 2, num_primes = 1;
    for (i = 1; i < MAX_N / 2; i++) {
        if (!composite[i]) {
            int p = 2 * i + 1;
            prime[num_primes++] = p;
            assert(num_primes <= NUM_PRIMES);
            for (j = p * p / 2; j < MAX_N / 2; j += p) {
                composite[j] = 1;
            }
        }
    }
    num_sequences = 0;
    for (i = 0; i < num_primes - 2; i++) {
        int diff = prime[i + 1] - prime[i];
        if (prime[i + 2] - prime[i + 1] == diff) {
            sequence_t *s = &sequence[num_sequences++];
            assert(num_sequences < NUM_SEQS);
            s->index = i, s->start = prime[i], s->length = 3;
            for (j = i + 3; j < num_primes && 
                    prime[j] - prime[j - 1] == diff; j++, s->length++)
                ;
            s->end = prime[j - 1], i = j - 2;
        }
    }
}

/* Main function */
int main() {
    int i, j, p, cap, start, end;
    compute_prime_sequences();
    while (scanf("%d %d", &start, &end) == 2 && (start != 0 || end != 0)) {
        if (start > end) {
            int swap = start;
            start = end;
            end = swap;
        }
        for (i = 0; i < num_sequences && end >= sequence[i].end; i++) {
            if (start > sequence[i].start) continue;
            for (j = 0, p = sequence[i].index, cap = sequence[i].length; 
                    j < cap; j++, p++) {
                printf("%d%c", prime[p], j < cap - 1 ? ' ' : '\n');
            }
        }
    }
    return EXIT_SUCCESS;
}
