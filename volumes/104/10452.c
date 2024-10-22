/* 10452
 * Marcus
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       8
#define MAX_STRING  (MAX_N + 2)
#define PASS_LEN    7
#define DIRS        3

char pass[PASS_LEN + 1] = "IEHOVA#";
char maze[MAX_N][MAX_STRING];
int rows, cols;

/* Find path to exit on maze */
void find_path() {
    static int dr[DIRS]= {0, -1, 0}, dc[DIRS] = {-1, 0, 1};
    static char command[DIRS][MAX_STRING] = {"left", "forth", "right"};
    int i, k, r, c;
    r = rows - 1;
    c = strchr(maze[r], '@') - maze[r];
    for (i = 0; i < PASS_LEN; i++)
        for (k = 0; k < DIRS; k++) {
            int nr = r + dr[k], nc = c + dc[k];
            if (nr >= 0 && nc >= 0 && nc < cols && maze[nr][nc] == pass[i]) {
                r = nr, c = nc;
                printf("%s%s", i == 0 ? "" : " ", command[k]);
                break;
            }
        }
    printf("\n");
}

/* Main function */
int main() {
    assert(scanf("%*d") != EOF);
    while (scanf("%d %d", &rows, &cols) == 2) {
        int i;
        for (i = 0; i < rows; i++)
            assert(scanf(" %s", maze[i]) == 1);
        find_path();
    }
    return EXIT_SUCCESS;
}
