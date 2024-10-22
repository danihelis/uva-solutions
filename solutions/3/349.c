/* 349
 * Transferable Voting (II)
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_C   5
#define MAX_N   100

typedef struct {
    int vote[MAX_C], valid, init;
} voter_t;

voter_t voter[MAX_N];

/* Read vote */
int read_vote(int index, int c) {
    int i, b, chosen[MAX_C];
    voter_t *v = &voter[index];
    v->valid = 1, v->init = 0;
    memset(chosen, 0, c * sizeof (int));
    for (i = 0; i < c; i++) {
        assert(scanf("%d", &b) == 1);
        b--;
        if (v->valid && b >= 0 && b < c) {
            v->vote[i] = b;
            v->valid &= chosen[b] == 0;
            chosen[b] = 1;
        }
        else
            v->valid = 0;
    }
    return v->valid;
}

/* Main function */
int main() {
    int n, c, test = 0;
    while (scanf("%d %d", &c, &n) == 2 && c > 0) {
        int i, valid, first, last, ended, vote[MAX_C], lost[MAX_C];
        for (i = valid = 0; i < n; i++)
            valid += read_vote(i, c) ? 1 : 0;
        memset(lost, 0, c * sizeof (int));
        ended = 0;
        while (!ended) {
            memset(vote, 0, c * sizeof (int));
            for (i = 0; i < n; i++) {
                voter_t *v = &voter[i];
                if (v->valid)
                    vote[v->vote[v->init]]++;
            }
            for (i = 0, first = last = -1; i < c; i++)
                if (!lost[i]) {
                    if (first == -1 || vote[i] > vote[first])
                        first = i;
                    if (last == -1 || vote[i] < vote[last])
                        last = i;
                }
            if (vote[first] > valid / 2)
                ended = 1;
            else if (vote[first] == vote[last])
                ended = -1;
            else {
                lost[last] = 1;
                for (i = 0; i < n; i++) {
                    voter_t *v = &voter[i];
                    if (v->valid && v->vote[v->init] == last)
                        v->init++;
                }
            }
        }
        printf("Election #%d\n", ++test);
        if (valid < n)
            printf("   %d bad ballot(s)\n", n - valid);
        if (ended > 0)
            printf("   Candidate %d is elected.\n", first + 1);
        else {
            printf("   The following candidates are tied:");
            for (i = 0; i < c; i++)
                if (!lost[i])
                    printf(" %d", i + 1);
            printf("\n");
        }
    }
    return EXIT_SUCCESS;
}
