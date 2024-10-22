/* 11405
 * Can U Win?
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_PIECES  8
#define MAX_DIM     8
#define MAX_MOVES   8
#define MAX_CELLS   (MAX_DIM * MAX_DIM)
#define MAX_STRING  (MAX_DIM + 2)

#define BITS_POS    3
#define BITS_SET    MAX_PIECES
#define DP_SIZE     (1 << (BITS_POS + BITS_SET))

#define VISITED     -1
#define FREE        0

typedef struct {
    int row, col, dist;
} point_t;

int distance[MAX_PIECES + 1][MAX_PIECES];
char board[MAX_DIM][MAX_STRING];
int num_pawns;

int dp[DP_SIZE];
char defined[DP_SIZE];

/* Determine reach distance between start point and all pawns */
#define IN(x)       ((x) >= 0 && (x) < MAX_DIM)
int determine_reach() {
    int drow[MAX_MOVES] = {-1, -2, -2, -1, 1, 2, 2, 1},
        dcol[MAX_MOVES] = {-2, -1, 1, 2, 2, 1, -1, -2};
    point_t start = {-1, -1, -1};
    point_t pawn[MAX_PIECES], queue[MAX_CELLS];
    int r, c, i, j, front, rear, pawns_visited;
    char map[MAX_DIM][MAX_DIM], base[MAX_DIM][MAX_DIM];

    /* Transform board in a graph map */
    for (r = 0, num_pawns = 0; r < MAX_DIM; r++)
        for (c = 0; c < MAX_DIM; c++)
            switch (board[r][c]) {
                case 'k':
                    start.row = r, start.col = c;
                case '.': 
                    base[r][c] = FREE; 
                    break;
                case 'p':
                case 'K': 
                    base[r][c] = VISITED; 
                    break;
                case 'P': 
                    pawn[num_pawns].row = r, pawn[num_pawns].col = c;
                    board[r][c] = num_pawns++;
                    base[r][c] = FREE;
                    break;
                default: 
                    assert(NULL);
            }
    assert(start.row != -1);
    
    /* Reach every pawn from every pawn */
    for (i = 0; i < num_pawns + 1; i++) {
        queue[0] = i < num_pawns ? pawn[i] : start;
        queue[0].dist = 0;
        front = 0, rear = 1;
        pawns_visited = 0;
        memcpy(map, base, MAX_CELLS);
        map[queue[0].row][queue[0].col] = VISITED;
        while (front < rear && pawns_visited < num_pawns) {
            point_t next, cur = queue[front++];
            int p = board[cur.row][cur.col];
            if (p >= 0 && p < num_pawns) {
                distance[i][p] = cur.dist;
                pawns_visited++;
            }
            for (j = 0, next.dist = cur.dist + 1; j < MAX_MOVES; j++) {
                next.row = cur.row + drow[j];
                next.col = cur.col + dcol[j];
                if (IN(next.row) && IN(next.col) &&
                        map[next.row][next.col] != VISITED) {
                    queue[rear++] = next;
                    map[next.row][next.col] = VISITED;
                }
            }
        }
        if (pawns_visited < num_pawns)
            return 0;
    }
    return 1;
}

/* Determine number of turns to reach a set of pawns from a starting pawn */
int minimum_turns(int pawn, int set) {
    int code = pawn | (set << BITS_POS);
    if (set == 0)
        return 0;
    else if (defined[code])
        return dp[code];
    else {
        int i, pcode, minimum = MAX_CELLS;
        for (i = 0, pcode = 1; i < num_pawns; i++, pcode <<= 1)
            if (set & pcode) {
                int turn = distance[pawn][i] + minimum_turns(i, set ^ pcode);
                if (turn < minimum)
                    minimum = turn;
            }
        dp[code] = minimum;
        defined[code] = 1;
        return minimum;
    }
}

/* Find minimum number of turns to reach all pawns */
int find_minimum_turns() {
    int i, set, minimum = MAX_CELLS;
    memset(defined, 0, DP_SIZE);
    for (i = 0, set = (1 << num_pawns) - 1; i < num_pawns; i++) {
        int turn = distance[num_pawns][i] + minimum_turns(i, set);
        if (turn < minimum)
            minimum = turn;
    }
    return num_pawns > 0 ? minimum : 0;
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        int i, moves;
        assert(scanf("%d", &moves) != EOF);
        for (i = 0; i < MAX_DIM; i++)
            assert(scanf(" %s", board[i]) != EOF);
        printf("%s\n", determine_reach() && find_minimum_turns() <= moves ?
                "Yes" : "No");
    }
    return EXIT_SUCCESS;
}
