/* 469
 * Wetlands of Florida
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_ROWS    100
#define MAX_STRING  110
#define MAX_ELEMS   (MAX_ROWS * MAX_STRING)
#define NUM_DIRS    8
#define CHAR_WATER  'W'

#define IS_IN(x,m)  ((x) >= 0 && (x) < (m))
#define INSIDE(p)   (IS_IN((p).row, num_rows) && IS_IN((p).col, num_cols))
#define GRID(p)     (grid[(p).row][(p).col])
#define LAKE(p)     (lake[(p).row][(p).col])

typedef struct {
    int row, col;
} point_t;

typedef char string_t[MAX_STRING];
string_t grid[MAX_ROWS];
int *lake[MAX_ROWS][MAX_STRING];
int area[MAX_ELEMS];
int num_rows, num_cols, num_areas;

/* Find area of continuous water */
int get_water_area(int row, int col) {
    static point_t stack[MAX_ELEMS];
    static int drow[] = {-1, -1, -1, 0, 1, 1, 1, 0}, dcol[] = {-1, 0, 1, 1, 1, 0, -1, -1};
    int i, top, *area_ptr;
    stack[0].row = row, stack[0].col = col;
    if (GRID(stack[0]) != CHAR_WATER) {
        return 0;
    }
    if (LAKE(stack[0]) != NULL) {
        return *(LAKE(stack[0]));
    }
    area_ptr = &area[num_areas++];
    LAKE(stack[0]) = area_ptr;
    *area_ptr = 0, top = 1;
    while (top > 0) {
        point_t p = stack[--top];
        (*area_ptr)++;
        for (i = 0; i < NUM_DIRS; i++) {
            point_t new;
            new.row = p.row + drow[i], new.col = p.col + dcol[i];
            if (INSIDE(new) && GRID(new) == CHAR_WATER && LAKE(new) == NULL) {
                stack[top++] = new;
                LAKE(new) = area_ptr;
            }
        }
    }
    return *area_ptr;
}

/* Main function */
int main() {
    string_t line;
    int first, num_tests;
    assert(fgets(line, MAX_STRING, stdin) != NULL);
    assert(sscanf(line, "%d", &num_tests) == 1);
    for (first = 1; num_tests > 0; num_tests--) {
        if (first) {
            assert(fgets(line, MAX_STRING, stdin) != NULL && line[0] == '\n');
            first = 0;
        }
        else {
            printf("\n");
        }
        num_rows = 0, num_cols = 0, num_areas = 0;
        while (fgets(line, MAX_STRING, stdin) != NULL && !isdigit(line[0])) {
            strcpy(grid[num_rows], line);
            if (num_cols == 0) {
                num_cols = strlen(line);
            }
            memset(lake[num_rows], 0, num_cols * sizeof (int *));
            num_rows++;
        }
        do {
            int row, col;
            assert(sscanf(line, "%d %d", &row, &col) == 2);
            printf("%d\n", get_water_area(--row, --col));
        } while (fgets(line, MAX_STRING, stdin) != NULL && line[0] != '\n');
    }
    return 0;
}
