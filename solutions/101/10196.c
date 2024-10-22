/*
 * 10196
 * Check the Check
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define DIMENSION 8
#define STR_SIZE (DIMENSION + 5)
char table[DIMENSION][STR_SIZE];
typedef enum {
    WHITE,
    BLACK,
    NONE
} check_t;

/* Useful macros */
#define TYPE(x) (islower(x) ? BLACK : WHITE)
#define ENEMY_TYPE(t) ((t) == BLACK ? WHITE : BLACK)
#define IS_CHECK(p, t) (((p) == 'k' && (t) == WHITE) || ((p) == 'K' && (t) == BLACK))
#define BOARD_ON_CHECK(r, c, t) IS_CHECK(table[r][c], t)
#define BOARD_EMPTY(r, c) (table[(r)][(c)] == '.')
#define ON_BOARD(r, c) ((r) >= 0 && (r) < DIMENSION && (c) >= 0 && (c) < DIMENSION)


/* Pawn move */
check_t pawn(int row, int column, check_t type) {
    short row_move = (type == WHITE ? -1 : 1);
    short column_move;
    for (column_move = -1; column_move <= 1; column_move += 2) {
        if (ON_BOARD(row + row_move, column + column_move)
                && BOARD_ON_CHECK(row + row_move, column + column_move, type)) {
            return ENEMY_TYPE(type);
        }
    }
    return NONE;
}


/* Continuous move */
#define CONTINUOUS_DIRS 4
check_t continuous_move(int row, int column, check_t type, short *drow, short *dcolumn) {
    short d;
    for (d = 0; d < CONTINUOUS_DIRS; d++) {
        short new_row = row + drow[d], new_column = column + dcolumn[d];
        while (ON_BOARD(new_row, new_column)) {
            if (BOARD_ON_CHECK(new_row, new_column, type)) {
                return ENEMY_TYPE(type);
            }
            if (!BOARD_EMPTY(new_row, new_column)) {
                break;
            }
            new_row += drow[d];
            new_column += dcolumn[d];
        }
    }
    return NONE;
}


/* Rook move */
check_t rook(int row, int column, check_t type) {
    static short rook_drow[CONTINUOUS_DIRS] = {0, 1, 0, -1};
    static short rook_dcolumn[CONTINUOUS_DIRS] = {1, 0, -1, 0};
    return continuous_move(row, column, type, rook_drow, rook_dcolumn);
}


/* Bishop move */
check_t bishop(int row, int column, check_t type) {
    static short bishop_drow[CONTINUOUS_DIRS] = {1, 1, -1, -1};
    static short bishop_dcolumn[CONTINUOUS_DIRS] = {1, -1, 1, -1};
    return continuous_move(row, column, type, bishop_drow, bishop_dcolumn);
}


/* Queen move */
check_t queen(int row, int column, check_t type) {
    check_t check;
    check = rook(row, column, type);
    if (check == NONE) {
        return bishop(row, column, type);
    }
    return check;
}


/* Knight move */
#define KNIGHT_DIRS 8
check_t knight(int row, int column, check_t type) {
    static short drow[KNIGHT_DIRS] = {-1, -2, -2, -1, 1, 2, 2, 1};
    static short dcolumn[KNIGHT_DIRS] = {-2, -1, 1, 2, 2, 1, -1, -2};
    short d;
    for (d = 0; d < KNIGHT_DIRS; d++) {
        short new_row = row + drow[d], new_column = column + dcolumn[d];
        if (ON_BOARD(new_row, new_column) && BOARD_ON_CHECK(new_row, new_column, type)) {
            return ENEMY_TYPE(type);
        }
    }
    return NONE;
}


/* Main function */
int main() {
    short row, column;
    int game, empty;
    check_t check;

    for (game = 1; ; game++) {
        for (row = 0; row < DIMENSION; row++) {
            if (fgets(table[row], STR_SIZE, stdin) == NULL) {
                break;
            }
        }

        check = NONE;
        empty = 0;
        for (row = 0; row < DIMENSION && check == NONE; row++) {
            for (column = 0; column < DIMENSION && check == NONE; column++) {
                switch (tolower(table[row][column])) {
                    case 'p':
                        check = pawn(row, column, TYPE(table[row][column]));
                        break;
                    case 'r':
                        check = rook(row, column, TYPE(table[row][column]));
                        break;
                    case 'b':
                        check = bishop(row, column, TYPE(table[row][column]));
                        break;
                    case 'q':
                        check = queen(row, column, TYPE(table[row][column]));
                        break;
                    case 'n':
                        check = knight(row, column, TYPE(table[row][column]));
                        break;
                    case '.':
                        empty++;
                        break;
                }
            }
        }
        
        if (empty == (DIMENSION * DIMENSION)) {
            break;
        }
        printf("Game #%d: ", game);
        switch (check) {
            case BLACK:
                printf("black king is in check.\n");
                break;
            case WHITE:
                printf("white king is in check.\n");
                break;
            case NONE:
                printf("no king is in check.\n");
                break;
        }

        assert(fgets(table[0], STR_SIZE, stdin) != NULL);
        assert(table[0][0] == '\n');
    }
    return 0;
}
