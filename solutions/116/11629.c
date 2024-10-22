/* 11629
 * Ballot evaluation
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       50
#define MAX_NAME    25

typedef struct {
    char name[MAX_NAME];
    int win;
} party_t;

party_t party[MAX_N], *p_party[MAX_N];
int n;

/* Compare pointers for party */
int compare(const void *a, const void *b) {
    party_t *pa = *((party_t **) a), *pb = *((party_t **) b);
    return strcmp(pa->name, pb->name);
}

/* Ready parties */
void read_parties() {
    int i;
    for (i = 0; i < n; i++) {
        party_t *p = &party[i];
        int figure, cents;
        assert(scanf(" %s %d.%d", p->name, &figure, &cents) != EOF);
        p->win = figure * 10 + cents;
        p_party[i] = p;
    }
    qsort(p_party, n, sizeof (party_t *), compare);
}

/* Main function */
int main() {
    int i, guesses;
    assert(scanf("%d %d", &n, &guesses) != EOF);
    read_parties();
    for (i = 0; i < guesses; i++) {
        party_t suggestion, *p_suggestion, **p_ref;
        char symbol = '+', equal, correct = 0;
        int win_sum = 0, value;
        p_suggestion = &suggestion;
        while (symbol == '+') {
            assert(scanf(" %s %c", suggestion.name, &symbol) != EOF);
            p_ref = (party_t **) bsearch(&p_suggestion, p_party, n, 
                    sizeof  (party_t *), compare);
            win_sum += (*p_ref)->win;
        }
        assert(scanf("%c%d", &equal, &value) != EOF);
        value *= 10;
        switch (symbol) {
            case '<': correct = win_sum < value; break;
            case '>': correct = win_sum > value; break;
        }
        if (symbol == '=' || equal == '=') correct |= win_sum == value;
        printf("Guess #%d was %scorrect.\n", i + 1, correct ? "" : "in");
    }
    return EXIT_SUCCESS;
}
