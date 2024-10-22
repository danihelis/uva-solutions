/* 10344
 * 23 out of 5
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define N       5
#define RESULT  23

int input[N], perm[N];

/* Whether an expression can be computed or not */
int can_compute(int index, int left) {
    if (index == N)
        return left == RESULT;
    else {
        int i, right, possible;
        for (i = 0, possible = 0; !possible && i < 3; i++) {
            switch (i) {
                case 0: right = left + perm[index]; break;
                case 1: right = left - perm[index]; break;
                case 2: right = left * perm[index]; break;
            }
            possible = can_compute(index + 1, right);
        }
        return possible;
    }
}

/* Generate permutations */
int generate_perm(int index, int mask) {
    if (index == N)
        return can_compute(1, perm[0]);
    else {
        int used[N], num_used, possible, i, k;
        for (i = 0, num_used = 0, possible = 0; !possible && i < N; i++)
            if ((1 << i) & ~mask) {
                for (k = 0, possible = 1; possible && k < num_used; k++)
                    possible = used[k] != input[i];
                if (!possible)
                    continue;
                used[num_used++] = perm[index] = input[i];
                possible = generate_perm(index + 1, mask | (1 << i));
            }
        return possible;
    }        
}

/* Main function */
int main() {
    while (scanf("%d", &input[0]) == 1 && input[0] > 0) {
        int i;
        for (i = 1; i < N; i++)
            assert(scanf("%d", &input[i]) == 1);
        printf("%sossible\n", generate_perm(0, 0) ? "P" : "Imp");
    }
    return EXIT_SUCCESS;
}
