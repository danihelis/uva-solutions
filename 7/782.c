/* 782
 * Contour Painting
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  100
#define MAX_LINES   40
#define NUM_DIR     4

#define START       '*'
#define SPACE       ' '
#define BORDER      '#'
#define END         '_'

typedef char string_t[MAX_STRING];

string_t picture[MAX_LINES];
int height, width, start_row, start_column;

/* Fill picture with spaces to accomodate border */
void fill_spaces() {
    int i, w;
    char *line;
    for (i = 0; i < height; i++) {
        for (w = 0, line = picture[i]; *line != 0; line++, w++)
            ;
        for (; w < width; w++, line++) {
            *line = SPACE;
        }
        *line = 0;
    }
}

/* Fill border */
#define IS_IN(x, v)     ((x) >= 0 && (x) < (v))
void fill_border() {
    struct { int row, col; } stack[MAX_LINES * MAX_STRING];
    int drow[NUM_DIR] = {-1, 0, 1, 0}, dcol[NUM_DIR] = {0, 1, 0, -1};
    int top, i, r, c, has_border;
    stack[0].row = start_row, stack[0].col = start_column;
    top = 1;
    picture[start_row][start_column] = SPACE;
    while (top > 0) {
        top--;
        r = stack[top].row, c = stack[top].col;
        for (i = 0, has_border = 0; i < NUM_DIR; i++) {
            int nr = r + drow[i], nc = c + dcol[i];
            if (IS_IN(nr, height) && IS_IN(nc, width)) {
                char pixel = picture[nr][nc];
                if (pixel == SPACE) {
                    picture[nr][nc] = END;
                    stack[top].row = nr, stack[top].col = nc;
                    top++;
                }
                else if (pixel != BORDER && pixel != END) {
                    has_border = 1;
                }
            }
        }
        if (has_border) {
            picture[r][c] = BORDER;
        }
    }
}

/* Remove visited characteres */
void clean_picture() {
    int i, trim;
    char *line, *start;
    for (i = 0; i < height; i++) {
        for (trim = 1, start = picture[i], line = picture[i] + width - 1; 
                line >= start; line--) {
            if (*line == END || *line == SPACE) {
                *line = (trim ? 0 : SPACE);
            }
            else {
                trim = 0;
            }
        }
    }
}

/* Main function */
int main() {
    string_t input;
    int i, num_tests;
    assert(fgets(input, MAX_STRING, stdin) != NULL);
    assert(sscanf(input, "%d", &num_tests) == 1);
    for (; num_tests > 0; num_tests--) {
        height = 0, width = 0;
        while (fgets(picture[height], MAX_STRING, stdin) != NULL && picture[height][0] != END) {
            char *start = strchr(picture[height], START);
            if (start != NULL) {
                start_row = height, start_column = start - picture[height];
            }
            i = strlen(picture[height]);
            picture[height][i - 1] = SPACE;
            if (i > width) {
                width = i;
            }
            height++;
        }
        fill_spaces();
        fill_border();
        clean_picture();
        for (i = 0; i < height; i++) {
            printf("%s\n", picture[i]);
        }
        printf("%s", picture[height]);
    }
    return 0;
}
