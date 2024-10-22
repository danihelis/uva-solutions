/* 10912
 * Simple Minded Hashing
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_SIZE    26
#define MAX_HASH    360

int total[MAX_SIZE][MAX_HASH];

/* Compute counts for hashings.
 *
 * Let C(a, L, S) stand for the number of strings starting with letter a, having
 * length L and hash value S. Then:
 *      C(a, 1, S) = 1 if |a| == S else 0
 *      C(a, L, S) = sum{a < x < 'Z'} C(x, L-1, S-a)
 */
void compute_total() {
    int count[MAX_SIZE][MAX_SIZE][MAX_HASH];
    int letter, prior, size, hash_value;
    memset(count, 0, sizeof (count));
    for (letter = 0; letter < MAX_SIZE; letter++) {
        count[letter][0][letter + 1] = 1;
        total[0][letter + 1] = 1;
    }
    for (size = 1; size < MAX_SIZE; size++) {
        for (hash_value = 1; hash_value < MAX_HASH; hash_value++) {
            for (letter = 1; letter < MAX_SIZE; letter++) {
                int c = count[letter][size - 1][hash_value];
                if (c == 0) continue;
                for (prior = 0; prior < letter; prior++) {
                    assert(hash_value + prior < MAX_HASH);
                    count[prior][size][hash_value + prior + 1] += c;
                    total[size][hash_value + prior + 1] += c;
                }
            }
        }
    }
}

/* Main function */
int main() {
    int size, hash_value, value, test = 0;
    compute_total();
    while (scanf("%d %d", &size, &hash_value) == 2 && size > 0) {
        size--;
        if (size < 0 || size >= MAX_SIZE || 
                hash_value < 0 || hash_value >= MAX_HASH) {
            value = 0;
        } else value = total[size][hash_value];
        printf("Case %d: %d\n", ++test, value);
    }
    return EXIT_SUCCESS;
}
