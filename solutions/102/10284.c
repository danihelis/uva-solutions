/* 10284
 * Chessboard in FEN
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIM     8
#define KING        'k'
#define QUEEN       'q'
#define ROOK        'r'
#define BISHOP      'b'
#define KNIGHT      'n'
#define WHITE_PEON  'P'
#define BLACK_PEON  'p'
#define SEPARATOR   '/'

#define INSIDE(r)   ((r) >= 0 && (r) < MAX_DIM)
#define IN(r,c)     (INSIDE(r) && INSIDE(c))

#define UPDATE(r,c) if (IN(r,c) && table[r][c] == 0) table[r][c] = 1

char table[MAX_DIM][MAX_DIM];

/* Check all attacks by all pieces */
void check_attack() {
    int row, column;
    int i, j, r, c, dr, dc;
    for (row = 0; row < MAX_DIM; row++) {
        for (column = 0; column < MAX_DIM; column++) {
            char piece = tolower(table[row][column]);
            switch (piece) {
                case KING:
                    for (i = -1; i <= 1; i++) {
                        for (j = -1; j <= 1; j++) {
                            r = row + i, c = column + j;
                            UPDATE(r, c);
                        }
                    }
                    break;

                case QUEEN:
                case ROOK:
                    for (i = 0; i < 4; i++) {
                        dr = i % 2 == 0 ? 0 : i / 2 == 0 ? -1 : 1;
                        dc = i % 2 == 1 ? 0 : i / 2 == 0 ? -1 : 1;
                        for (r = row + dr, c = column + dc; 
                                IN(r, c) && !isalpha(table[r][c]); r += dr, c += dc) {
                            table[r][c] = 1;
                        }
                    }
                    if (piece == ROOK) {
                        break;
                    }

                case BISHOP:
                    for (i = 0; i < 4; i++) {
                        dr = i % 2 == 0 ? -1 : 1;
                        dc = i / 2 == 0 ? -1 : 1;
                        for (r = row + dr, c = column + dc; 
                                IN(r, c) && !isalpha(table[r][c]); r += dr, c += dc) {
                            table[r][c] = 1;
                        }
                    }
                    break;

                case KNIGHT:
                    for (i = -2; i <= 2; i++) {
                        for (j = -1; i != 0 && j <= 1; j += 2) {
                            r = row + i;
                            c = column + ((i == -1 || i == 1) ? (2 * j) : j);
                            UPDATE(r, c);
                        }
                    }
                    break;

                case BLACK_PEON:
                    r = row + (table[row][column] == BLACK_PEON ? 1 : -1);
                    for (j = -1; j <= 1; j += 2) {
                        c = column + j;
                        UPDATE(r, c);
                    }
                    break;
            }
        }
    }
}

/* Main function */
int main() {
    char symbol;
    int row, column, safe;
    while (scanf(" %c", &symbol) != EOF) {
        row = 0, column = 0;
        while (row < MAX_DIM) {
            assert((row == 0 && column == 0) || scanf("%c", &symbol) != EOF);
            if (!isdigit(symbol)) {
                table[row][column++] = symbol;
            }
            else {
                int i, n;
                for (i = 0, n = symbol - '0'; i < n; i++) {
                    table[row][column++] = 0;
                }
            }
            if (column >= MAX_DIM) {
                column = 0;
                row++;
                assert(row == MAX_DIM || (scanf("%c", &symbol) != EOF && symbol == SEPARATOR));
            }
        }
        check_attack();
        for (row = 0, safe = 0; row < MAX_DIM; row++) {
            for (column = 0; column < MAX_DIM; column++) {
                if (table[row][column] == 0) {
                    safe++;
                }
            }
        }
        printf("%d\n", safe);
    }
    return 0;
}
