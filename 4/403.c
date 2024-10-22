/* 403
 * Postscript
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define NUM_LETTERS     26
#define NUM_C5_LINES    5
#define NUM_C5_COLS     6

#define NUM_COLS        60
#define NUM_LINES       60
#define MAX_STRING      (NUM_COLS + 2)

#define RIN(r)          ((r) >= 0 && (r) < NUM_LINES)
#define CIN(c)          ((c) >= 0 && (c) < NUM_COLS)

char matrix[NUM_C5_LINES][NUM_LETTERS * NUM_C5_COLS] = {
    ".***..****...****.****..*****.*****..****.*...*.*****...***.*...*.*.....*...*."
        "*...*..***..****...***..****...****.*****.*...*.*...*.*...*.*...*.*...*.*****.",
    "*...*.*...*.*...*.*...*.*.....*.....*.....*...*...*......*..*..*..*.....**.**."
        "**..*.*...*.*...*.*...*.*...*.*.....*.*.*.*...*.*...*.*...*..*.*...*.*.....*..",
    "*****.****..*.....*...*.***...***...*..**.*****...*......*..***...*.....*.*.*."
        "*.*.*.*...*.****..*...*.****...***....*...*...*..*.*..*.*.*...*.....*.....*...",
    "*...*.*...*.*.....*...*.*.....*.....*...*.*...*...*...*..*..*..*..*.....*...*."
        "*..**.*...*.*.....*..**.*..*......*...*...*...*..*.*..**.**..*.*....*....*....",
    "*...*.****...****.****..*****.*......***..*...*.*****..**...*...*.*****.*...*."
        "*...*..***..*......****.*...*.****...***...***....*...*...*.*...*...*...*****."
};
char page[NUM_LINES][MAX_STRING];

/* Print a string in the page */
void print(int font1, int row, int col, char *string) {
    int i, j;
    char *c;
    if (font1) {
        for (i = row, j = col, c = string; RIN(i) && CIN(j) && *c != 0; c++, j++) {
            if (!isspace(*c)) {
                page[i][j] = *c;
            }
        }
    }
    else {
        for (i = row, j = col, c = string; *c != 0; c++, j += NUM_C5_COLS) {
            if (isupper(*c)) {
                int fi, fj, offset = NUM_C5_COLS * (*c - 'A');
                for (fi = 0; RIN(i + fi) && fi < NUM_C5_LINES; fi++) {
                    for (fj = 0; fj < NUM_C5_COLS - 1; fj++) {
                        char glyph = matrix[fi][fj + offset];
                        if (CIN(j + fj) && glyph == '*') {
                            page[i + fi][j + fj] = glyph;
                        }
                    }
                }
            }
        }
    }
}

/* Main function */
int main() {
    char command[MAX_STRING];
    memset(page, '.', NUM_LINES * MAX_STRING);
    while (scanf(".%s ", command) != EOF) {
        char wh, string[MAX_STRING];
        int font, row, column;
        wh = command[0];
        switch (wh) {
            case 'E':
                for (row = 0; row < NUM_LINES; row++) {
                    page[row][NUM_COLS] = 0;
                    printf("%s\n", page[row]);
                }
                printf("\n");
                for (column = 0; column < NUM_COLS; column++) {
                    printf("-");
                }
                printf("\n\n");
                memset(page, '.', NUM_LINES * MAX_STRING);
                break;
            case 'P':
                assert(scanf("C%d %d %d |%[^|]| ", &font, &row, &column, string) != EOF);
                print(font == 1, row - 1, column - 1, string);
                break;
            case 'R':
            case 'L':
            case 'C':
                assert(scanf("C%d %d |%[^|]| ", &font, &row, string) != EOF);
                font = font == 5 ? NUM_C5_COLS : 1;
                column = wh == 'L' ? 0 : wh == 'R' ? NUM_COLS - strlen(string) * font :
                        NUM_COLS / 2 - strlen(string) * font / 2;
                print(font == 1, row - 1, column, string);
        }
    }
    return 0;
}
