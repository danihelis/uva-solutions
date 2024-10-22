/* 352
 * The Seasonal War
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIM     25
#define MAX_STRING  (MAX_DIM + 2)
#define MAX_ELEMS   (MAX_DIM * MAX_DIM)
#define NUM_DIR     8
#define EAGLE_MARK  '1'

#define IS_IN(v, m)         ((v) >= 0 && (v) < (m))
#define INSIDE(p, m)        (IS_IN((p).row, m) && IS_IN((p).col, m))
#define GRID(p)             (grid[(p).row][(p).col])

typedef struct {
    int row, col;
} point_t, *point_p;

char grid[MAX_DIM][MAX_STRING];
int dim;

/* Fill an eagle */
void fill(int row, int col) {
    static point_t stack[MAX_ELEMS];
    static int drow[] = {-1, -1, -1, 0, 1, 1, 1, 0}, dcol[] = {-1, 0, 1, 1, 1, 0, -1, -1};
    int i, top;

    stack[0].row = row, stack[0].col = col;
    GRID(stack[0]) = 0;
    top = 1;
    while (top > 0) {
        point_t p = stack[--top];
        for (i = 0; i < NUM_DIR; i++) {
            point_t new;
            new.row = p.row + drow[i], new.col = p.col + dcol[i];
            if (INSIDE(new, dim) && GRID(new) == EAGLE_MARK) {
                stack[top++] = new;
                GRID(new) = 0;
            }
        }
    }
}

/* Count number of eagles */
int count() {
    int total, row, col;
    for (row = 0, total = 0; row < dim; row++) {
        for (col = 0; col < dim; col++) {
            if (grid[row][col] == EAGLE_MARK) {
                total++;
                fill(row, col);
            }
        }
    }
    return total;
}

/* Main function */
int main() {
    int i, image = 0;
    while (scanf("%d", &dim) != EOF) {
        for (i = 0; i < dim; i++) {
            assert(scanf(" %s", grid[i]) != EOF);        
        }
        printf("Image number %d contains %d war eagles.\n", ++image, count());
    }
    return 0;
}
