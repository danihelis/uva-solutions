/* 1103
 * Ancient Messages
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIM     200
#define MAX_SIZE    (MAX_DIM * MAX_DIM)
#define MAX_FIGURES 10000
#define NUM_SHAPES  6
#define UNVISITED   -1
#define BLANK       -2

char map[MAX_DIM][MAX_DIM];
int index[MAX_DIM][MAX_DIM], figure[MAX_FIGURES], num_figures;
int width, height;

int count[NUM_SHAPES], spaces[NUM_SHAPES] = {1, 5, 3, 2, 4, 0};
char name[] = "ADJKSW";

/* Read map */
void read_map() {
    char line[MAX_DIM], *c;
    int i, j, k;
    for (i = 0; i < height; i++) {
        assert(scanf(" %s", line) != EOF);
        for (c = line, j = 0; *c != 0; c++) {
            int digit = isdigit(*c) ? *c - '0' : *c - 'a' + 10;
            for (k = 3; k >= 0; k--, j++) {
                map[i][j] = (digit >> k) & 1;
                index[i][j] = UNVISITED;
            }
        }
    }
}

/* Fill region */
#define IN(x)   ((x).row >= 0 && (x).row < height && \
                 (x).col >= 0 && (x).col < width)
int fill_region(int r, int c, int what) {
    int dr[4] = {0, 1, 0, -1}, dc[4] = {1, 0, -1, 0};
    struct {
        int row, col;
    } queue[MAX_SIZE], cur, new;
    int i, color, front, rear, border = UNVISITED;

    queue[0].row = r, queue[0].col = c;
    front = 0, rear = 1;
    color = map[r][c];
    index[r][c] = what;
    while (front < rear) {
        cur = queue[front++];
        for (i = 0; i < 4; i++) {
            new.row = cur.row + dr[i], new.col = cur.col + dc[i];
            if (IN(new)) {
                if (map[new.row][new.col] == color) {
                    if (index[new.row][new.col] == UNVISITED) {
                        queue[rear++] = new;
                        index[new.row][new.col] = what;
                    }
                }
                else if (border == UNVISITED)
                    border = index[new.row][new.col];
            }
            else
                border = BLANK;
        }
    }
    return border;
}

/* Identify figures */
void identify() {
    int i, j;
    num_figures = 0;
    for (i = 0; i < height; i++)
        for (j = 0; j < width; j++)
            if (index[i][j] == UNVISITED) {
                if (map[i][j] == 1) {
                    figure[num_figures] = 0;
                    fill_region(i, j, num_figures++);
                } 
                else {
                    int border = fill_region(i, j, BLANK);
                    if (border != BLANK)
                        figure[border]++;
                }
            }
    memset(count, 0, NUM_SHAPES * sizeof (int));
    for (i = 0; i < num_figures; i++)
        count[figure[i]]++;
}

/* Main function */
int main() {
    int i, j, total, test = 0;
    while (scanf("%d %d", &height, &width) != EOF && height > 0) {
        width *= 4;
        read_map();
        identify();
        printf("Case %d: ", ++test);
        for (i = 0; i < NUM_SHAPES; i++)
            for (j = 0, total = count[spaces[i]]; j < total; j++)
                printf("%c", name[i]);
        printf("\n");
    }
    return EXIT_SUCCESS;
}
