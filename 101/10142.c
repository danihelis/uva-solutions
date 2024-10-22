/*
 * 10142
 * Australian Vote
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define STRING_SIZE 100
#define MAX_CANDIDATES 20
#define MAX_VOTES 1000

typedef struct {
    char name[STRING_SIZE];
    short votes;
    char votable;
} candidate_t;
candidate_t candidate[MAX_CANDIDATES];
int num_candidates;

short votes[MAX_VOTES][MAX_CANDIDATES];
int num_votes;

short choice[MAX_VOTES];
short tied[MAX_CANDIDATES];
int num_tied, winner;


/* Count ballot */
int ballot_count_has_winner() {
    int i;
    for (i = 0; i < num_candidates; i++) {
        candidate[i].votes = 0;
    }
    for (i = 0; i < num_votes; i++) {
        short vote_to = votes[i][choice[i]];
        assert(candidate[vote_to].votable);
        candidate[vote_to].votes++;
    }
    
    winner = 0;
    for (i = 1; i < num_candidates; i++) {
        if (candidate[i].votes > candidate[winner].votes) {
            winner = i;
        }
    }
    return (candidate[winner].votes > (num_votes / 2));
}


/* Sort out tied candidates */
#define ALL_TIED 1
int determine_ties() {
    int i;
    num_tied = 0;
    for (i = 0; i < num_candidates; i++) {
        if (candidate[i].votable) {
            if (num_tied == 0 || candidate[i].votes < candidate[tied[0]].votes) {
                tied[0] = i;
                num_tied = 1;
            }
            else if (candidate[i].votes == candidate[tied[0]].votes) {
                tied[num_tied++] = i;
            }
        }
    }
    return (num_tied * candidate[tied[0]].votes == num_votes ? ALL_TIED : !ALL_TIED);
}


/* Remove tied losers */
void remove_tied_losers() {
    int i;
    for (i = 0; i < num_tied; i++) {
        candidate[tied[i]].votable = 0;
    }
    for (i = 0; i < num_votes; i++) {
        while (!candidate[votes[i][choice[i]]].votable) {
            choice[i]++;
        }
    }
}


/* Main function */
#define NO_WINNER -1
int main() {
    char input[STRING_SIZE];
    int ballots, round, counter;

    assert(fgets(input, STRING_SIZE, stdin) != NULL);
    assert(sscanf(input, "%d", &ballots) == 1);

    for (round = 0; round < ballots; round++) {
        if (round == 0) {
            assert(fgets(input, STRING_SIZE, stdin) != NULL);
            assert(input[0] == '\n');
        }
        else {
            printf("\n");
        }
        
        assert(fgets(input, STRING_SIZE, stdin) != NULL);
        assert(sscanf(input, "%d", &num_candidates) == 1);
        for (counter = 0; counter < num_candidates; counter++) {
            assert(fgets(candidate[counter].name, STRING_SIZE, stdin) != NULL);
            candidate[counter].votable = 1;
        }


        num_votes = 0;
        while (fgets(input, STRING_SIZE, stdin) != NULL) {
            char *line = strtok(input, " \n");
            if (line == NULL) {
                break;
            }
            for (counter = 0; counter < num_candidates; counter++) {
                assert(line != NULL);
                sscanf(line, "%hd", &votes[num_votes][counter]);
                votes[num_votes][counter]--;
                line = strtok(NULL, " \n");
            }
            assert(line == NULL);
            choice[num_votes] = 0;
            num_votes++;
        }
        
        while (!ballot_count_has_winner()) {
            winner = NO_WINNER;
            if (determine_ties() == ALL_TIED) {
                break;
            }
            remove_tied_losers();
        }

        if (winner != NO_WINNER) {
            printf("%s", candidate[winner].name);
        }
        else {
            for (counter = 0; counter < num_tied; counter++) {
                printf("%s", candidate[tied[counter]].name);
            }
        }
    }

    return 0;
}
