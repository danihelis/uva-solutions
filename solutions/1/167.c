/* 167
 * The Sultan's Successors
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIM         8
#define MAX_SOLUTIONS   100

int position[MAX_DIM], used[MAX_DIM];
int solution[MAX_SOLUTIONS][MAX_DIM];
int num_solutions;

/* Validate diagonal rules for a board position */
int validate_diagonal(int index, int pos) {
    int i;
    for (i = 0; i < index; i++)
        if (abs(position[i] - pos) == index - i)
            return 0;
    return 1;
}

/* Find all possible solutions for chess queen distribution */
void find_queen_dist(int index) {
    if (index == MAX_DIM)
        memcpy(solution[num_solutions++], position, sizeof position);
    else {
        int i;
        for (i = 0; i < MAX_DIM; i++)
            if (!used[i] && validate_diagonal(index, i)) {
                used[i] = 1;
                position[index] = i;
                find_queen_dist(index + 1);
                used[i] = 0;
            }
    }
}

/* Find best score in a wheighted chess board */
void solve_problem() {
    int board[MAX_DIM][MAX_DIM];
    int i, j, score, best;
    for (i = 0; i < MAX_DIM; i++)
        for (j = 0; j < MAX_DIM; j++)
            assert(scanf("%d", &board[i][j]) != EOF);
    for (j = 0, best = 0; j < num_solutions; j++) {
        for (i = 0, score = 0; i < MAX_DIM; i++)
            score += board[i][solution[j][i]];
        if (score > best)
            best = score;
    }
    printf("%5d\n", best);
}

/* Main function */
int main() {
    int k;
    num_solutions = 0;
    memset(used, 0, sizeof (used));
    find_queen_dist(0);
    assert(scanf("%d", &k) != EOF);
    for (; k > 0; k--)
        solve_problem();
    return EXIT_SUCCESS;
}
