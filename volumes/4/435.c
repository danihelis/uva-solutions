/* 435
 * Block Voting
 * By Johan Schreiber
 */
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PARTIES     20

int votes[MAX_PARTIES];
int num_parties;
int minimum_votes;

/* Compute power index recursivelly */
int compute_power_index(int party, int index, int coallition) {
    assert(coallition < minimum_votes);

    if (index == party) {
        return compute_power_index(party, index + 1, coallition);
    } else if (index >= num_parties) {
        return votes[party] + coallition >= minimum_votes ? 1 : 0;
    } else {
        int power = compute_power_index(party, index + 1, coallition);
        if (coallition + votes[index] < minimum_votes) {
            power += compute_power_index(party, index + 1,
                    coallition + votes[index]);
        }
        return power;
    }
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) == 1);

    while (num_tests-- > 0) {
        int i;

        assert(scanf("%d", &num_parties) == 1);
        minimum_votes = 0;

        for (i = 0; i < num_parties; i++) {
            assert(scanf("%d", &votes[i]) == 1);
            minimum_votes += votes[i];
        }
        minimum_votes = (minimum_votes / 2) + 1;

        for (i = 0; i < num_parties; i++) {
            printf("party %d has power index %d\n", i + 1,
                    compute_power_index(i, 0, 0));
        }
        printf("\n");
    }

    return EXIT_SUCCESS;
}
