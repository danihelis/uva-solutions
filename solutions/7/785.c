/* 785
 * Grid Colouring
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  100
#define MAX_HEIGHT  40
#define MAX_DIM     (MAX_STRING * MAX_HEIGHT)
#define NUM_DIR     4

#define SPACE       ' '
#define END         '_'

typedef struct {
    int row, col;
} point_t, *point_p;

point_t mark[MAX_DIM];
char border, picture[MAX_HEIGHT][MAX_STRING];
int num_marks, height;

/* Fill region with a mark */
void fill_region(point_p m) {
    point_t cur, next, stack[MAX_DIM];
    int drow[NUM_DIR] = {-1, 0, 1, 0}, dcol[NUM_DIR] = {0, 1, 0, -1};
    int top, i;
    char filling = picture[m->row][m->col];
    stack[0] = *m, top = 1;
    while (top > 0) {
        cur = stack[--top];
        for (i = 0; i < NUM_DIR; i++) {
            next.row = cur.row + drow[i], next.col = cur.col + dcol[i];
            if (next.row >= 0 && next.row < height && next.col >= 0 && 
                    picture[next.row][next.col] == SPACE) {
                picture[next.row][next.col] = filling;
                stack[top++] = next;
            }
        }
    }
}

/* Main function */
int main() {
    int i;
    while (fgets(picture[0], MAX_STRING, stdin) != NULL) {
        height = 0, num_marks = 0, border = 0;
        while (picture[height][0] != END) {
            char *line;
            for (line = picture[height]; *line != '\n'; line++) {
                if (*line != SPACE) {
                    if (border == 0) {
                        border = *line;
                    }
                    else if (*line != border) {
                        mark[num_marks].row = height;
                        mark[num_marks].col = line - picture[height];
                        num_marks++;
                    }
                }
            }
            assert(fgets(picture[++height], MAX_STRING, stdin) != NULL);
        }
        for (i = 0; i < num_marks; i++) {
            fill_region(&mark[i]);
        }
        for (i = 0; i <= height; i++) {
            printf("%s", picture[i]);
        }
    }
    return 0;
}
