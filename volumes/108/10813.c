/* 10813
 * Traditional BINGO
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIM     5
#define MAX_NUMS    75

int position[MAX_NUMS], card[MAX_DIM][MAX_DIM], used[MAX_NUMS];

/* Check if the card scored bingo */
int check_bingo(int row, int col) {
    int k, i, bingo, check_diagonal;
    check_diagonal = (row == col || row == MAX_DIM - col - 1) ? 1 : 0;
    for (k = 0; k < 2 + check_diagonal; k++) {
        for (i = 0, bingo = 1; i < MAX_DIM; i++) {
            int r, c;
            r = k == 0 ? row : k == 1 ? i : i;
            c = k == 0 ? i : k == 1 ? col : row == col ? i : MAX_DIM - i - 1;
            if ((r != 2 || c != 2) && !used[card[r][c]]) {
                bingo = 0;
                break;
            }
        }
        if (bingo) {
            return 1;
        }
    }
    return 0; 
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        int num, i, r, c, bingo;
        for (i = 0; i < MAX_NUMS; i++) {
            position[i] = -1, used[i] = 0;
        }
        for (r = 0; r < MAX_DIM; r++) {
            for (c = 0; c < MAX_DIM; c++) {
                if (r != 2 || c != 2) {
                    assert(scanf("%d", &num) != EOF);
                    card[r][c] = --num;
                    position[num] = r * MAX_DIM + c;
                }
            }
        }
        for (i = 0, bingo = 0; i < MAX_NUMS; i++) {
            assert(scanf("%d", &num) != EOF);
            used[--num] = 1;
            if (!bingo && position[num] >= 0) {
                r = position[num] / MAX_DIM;
                c = position[num] % MAX_DIM;
                bingo = check_bingo(r, c) ? (i + 1) : 0;
            }
        }
        printf("BINGO after %d numbers announced\n", bingo);
    }
    return 0;
}
