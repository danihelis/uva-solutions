/* 750
 * 8 Queens Chess Problem
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIMS    8
#define MAX_DIAGS   15

#define MAIN_DIAGONAL(r,c)      ((MAX_DIMS - 1) - (r) + (c))
#define SECOND_DIAGONAL(r,c)    ((r) + (c))

char main_diag[MAX_DIAGS], second_diag[MAX_DIAGS], row[MAX_DIMS];
int solution[MAX_DIMS], num_solutions, column_set;

/* Find a solution for the eight queens chess problem */
void find_solution(int column) {
    int i;
    if (column == column_set) {
        column++;
    }
    if (column >= MAX_DIMS) {
        printf("%2d     ", ++num_solutions);
        for (i = 0; i < MAX_DIMS; i++) {
            printf(" %d", solution[i] + 1);
        }
        printf("\n");
    }
    else {
        for (i = 0; i < MAX_DIMS; i++) {
            int md = MAIN_DIAGONAL(i, column), sd = SECOND_DIAGONAL(i, column);
            if (!row[i] && !main_diag[md] && !second_diag[sd]) {
                row[i] = 1, main_diag[md] = 1, second_diag[sd] = 1;
                solution[column] = i;
                find_solution(column + 1);
                row[i] = 0, main_diag[md] = 0, second_diag[sd] = 0;
            }
        }
    }
}

/* Main function */
int main() {
    int num_tests, r, c;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        assert(scanf("%d %d", &r, &c) != EOF);
        printf("SOLN       COLUMN\n #      1 2 3 4 5 6 7 8\n\n");
        r--, c--;
        memset(row, 0, MAX_DIMS);
        memset(main_diag, 0, MAX_DIAGS);
        memset(second_diag, 0, MAX_DIAGS);
        solution[c] = r, column_set = c, row[r] = 1; 
        main_diag[MAIN_DIAGONAL(r, c)] = 1, second_diag[SECOND_DIAGONAL(r, c)] = 1;
        num_solutions = 0;
        find_solution(0);
        (num_tests > 1 ? printf("\n") : 0);
    }
    return 0;
}
