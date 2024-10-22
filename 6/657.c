/* 657
 * The die is cast
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIM     50
#define MAX_STRING  (MAX_DIM + 2)
#define MAX_DICE    (MAX_DIM * MAX_DIM)
#define NUM_DIR     4

#define BACKGROUND  '.'
#define DIE         '*'
#define DOT         'X'

typedef char string_t[MAX_STRING];

string_t picture[MAX_DIM];
int dice[MAX_DICE];
int width, height, num_dice;

/* Fill a region marked by a specific char */
#define IS_IN(x, m) ((x) >= 0 && (x) < (m))
int fill_region(int r, int c, int is_die) {
    int drow[] = {-1, 0, 1, 0}, dcol[] = {0, 1, 0, -1};
    struct { int row, col; } stack[MAX_DICE];
    int top, i, dots;
    
    stack[0].row = r, stack[0].col = c;
    top = 1, dots = 0;

    if (is_die && picture[r][c] == DOT) {
        dots++;
        fill_region(r, c, 0);
    }
    picture[r][c] = (is_die ? BACKGROUND : DIE);

    while (top > 0) {
        --top;
        r = stack[top].row, c = stack[top].col;
        for (i = 0; i < NUM_DIR; i++) {
            int nr = r + drow[i], nc = c + dcol[i];
            if (IS_IN(nr, height) && IS_IN(nc, width) && 
                    (picture[nr][nc] == DOT || (is_die && picture[nr][nc] == DIE))) {
                if (is_die && picture[nr][nc] == DOT) {
                    dots++;
                    fill_region(nr, nc, 0);
                }
                stack[top].row = nr, stack[top].col = nc;
                picture[nr][nc] = (is_die ? BACKGROUND : DIE);
                top++;
            }
        }
    }
    return dots;
}

/* Find all dice in the picture */
void find_dice() {
    int r, c;
    num_dice = 0;
    for (r = 0; r < height; r++) {
        for (c = 0; c < width; c++) {
            if (picture[r][c] != BACKGROUND) {
                dice[num_dice++] = fill_region(r, c, 1);
            }
        }
    }
}

/* Compare two integers */
int compare(const void *a, const void *b) {
    return *((int *) a) - *((int *) b);
}

/* Main function */
int main() {
    int i, throw = 0;
    while (scanf("%d %d", &width, &height) != EOF && width > 0) {
        printf("Throw %d\n", ++throw);
        for (i = 0; i < height; i++) {
            assert(scanf(" %s", picture[i]) != EOF);
        }
        find_dice();
        qsort(dice, num_dice, sizeof (int), compare);
        for (i = 0; i < num_dice; i++) {
            printf("%d%s", dice[i], (i < num_dice - 1 ? " " : "\n\n"));
        }
    }
    return 0;
}
