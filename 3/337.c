/* 337
 * Interpreting Control Sequences
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIM     10
#define MAX_STRING  (MAX_DIM + 1)
#define MAX(x,y)    ((x) > (y) ? (x) : (y))
#define MIN(x,y)    ((x) < (y) ? (x) : (y))

/* Main function */
int main() {
    int input_rows, test = 0;
    while (scanf("%d ", &input_rows) == 1 && input_rows > 0) {
        char screen[MAX_DIM][MAX_STRING];
        int i, row, col, insert;
        char op, param;
        for (i = 0; i < MAX_DIM; i++) {
            memset(screen[i], ' ', MAX_DIM);
            screen[i][MAX_DIM] = 0;
        }
        insert = row = col = param = 0;
        while (input_rows > 0) {
            assert(scanf("%c", &op) == 1);
            if (op == '^')
                assert(scanf("%c", &op) == 1);
            else if (op != '\n') {
                param = op;
                op = '$';
            }
            switch (op) {
                case 'e':
                    memset(screen[row] + col, ' ', MAX_DIM - col); 
                    break;
                case 'c': 
                    for (i = 0; i < MAX_DIM; i++)
                        memset(screen[i], ' ', MAX_DIM);
                    break;
                case '^':
                    param = '^';
                case '$':
                    if (insert)
                        for (i = MAX_DIM - 1; i > col; i--)
                            screen[row][i] = screen[row][i - 1];
                    screen[row][col] = param;
                case 'r': col = MIN(col + 1, MAX_DIM - 1); break;
                case 'u': row = MAX(0, row - 1); break;
                case 'd': row = MIN(row + 1, MAX_DIM - 1); break; 
                case 'l': col = MAX(0, col - 1); break;
                case 'b': col = 0; break;
                case 'h': col = row = 0; break;
                case 'i': insert = 1; break;
                case 'o': insert = 0; break;
                case '\n': input_rows--; break;
                default:
                    assert(isdigit(op));
                    row = op - '0';
                    assert(scanf("%c", &op) == 1);
                    assert(isdigit(op));
                    col = op - '0';
            }
        }
        printf("Case %d\n+----------+\n", ++test);
        for (i = 0; i < MAX_DIM; i++)
            printf("|%s|\n", screen[i]);
        printf("+----------+\n");
    }
    return EXIT_SUCCESS;
}
