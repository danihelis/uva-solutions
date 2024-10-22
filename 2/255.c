/* 255
 * Correct Move
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define ROW(p)      ((p) / 8)
#define COL(p)      ((p) % 8)
#define SIGNAL(p)   ((p) < 0 ? -1 : 1)
#define DROW(p,q)   (ROW(p) - ROW(q))
#define DCOL(p,q)   (COL(p) - COL(q))
#define SROW(p,q)   (SIGNAL(DROW(p, q)))
#define SCOL(p,q)   (SIGNAL(DCOL(p, q)))

/* Main function */
int main() {
    int king, queen, move;
    while (scanf("%d %d %d", &king, &queen, &move) == 3) {
        if (king == queen) printf("Illegal state\n");
        else if ((ROW(move) != ROW(queen) && COL(move) != COL(queen)) ||
                move == queen ||
                (ROW(move) == ROW(queen) && ROW(move) == ROW(king) && 
                    DCOL(move, queen) * SCOL(king, queen) >= 
                        DCOL(king, queen) * SCOL(king, queen)) ||
                (COL(move) == COL(queen) && COL(move) == COL(king) &&
                    DROW(move, queen) * SROW(king, queen) >= 
                        DROW(king, queen) * SROW(king, queen))) {
            printf("Illegal move\n");
        } else if ((ROW(move) == ROW(king) && abs(DCOL(move, king)) == 1) ||
                (COL(move) == COL(king) && abs(DROW(move, king)) == 1)) {
            printf("Move not allowed\n");                        
        } else if ((king == 0 && move == 9) || (king == 7 && move == 14) ||
                (king == 56 && move == 49) || (king == 63 && move == 54)) {
            printf("Stop\n");
        } else printf("Continue\n");
    }
    return EXIT_SUCCESS;
}
