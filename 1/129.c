/**
 * 129
 * Krypton Factor
 * by Daniel Donadon
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_OUTPUT 90
#define MAX_GROUPS 16

char krypto[MAX_OUTPUT];
int pos;
int n, num_letters;


/* Check if krypto has any equal subsequence (i.e., it is not hard).
 * Since all sequences are created by appending a letter to a hard krypto,
 * the common subsequences must occur at the end of the word.
 */
int has_equal_subsequence() {
    int k, dist, d, p, q, equal = 0;
    equal = 0;
    for (k = pos - 2, dist = 1; !equal && k >= 0; k -= 2, dist++) {
        equal = 1;
        for (p = k, q = k + dist, d = 0; d < dist; d++, p++, q++) {
            if (krypto[p] != krypto[q]) {
                equal = 0;
                break;
            }
        }
    }
    return equal;
}


/* Create output by sequencially creating permutations */
#define LETTER(k) ('A' + k)
#define INDEX(k) (k - 'A')
void create_krypto() {
    int i, letter;

    pos = 0;
    for (i = 0; i < n; i++) {
        letter = 0;
        krypto[pos++] = LETTER(letter);

        /* Check if combination is hard enough */
        while (has_equal_subsequence()) {
            krypto[pos - 1]++;
            while (INDEX(krypto[pos - 1]) >= num_letters) {
                assert(--pos > 0);
                krypto[pos - 1]++;
            }
        }
    }
}


/* Print krypto result */
void print_krypto() {
    int i, group;

    group = 0;
    for (i = 0; i < pos; i++) {
        if (i > 0 && i % 4 == 0) {
            printf("%c", (++group >= MAX_GROUPS ? '\n' : ' '));
            group %= MAX_GROUPS;
        }
        printf("%c", krypto[i]);
    }
    printf("\n%d\n", pos);
}


/* Main */
int main() {
    while (scanf("%d %d", &n, &num_letters) == 2) {
        if (n == 0) {
            break;
        }
        create_krypto();
        print_krypto();
    }
    return 0;
}

