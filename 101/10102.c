/* 10102
 * The path in the colored field
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIR     4
#define MAX_DIM     1000
#define MAX_STRING  (MAX_DIM + 2)
#define START       '1'
#define END         '3'
#define INFINITY    1000000000

char map[MAX_DIM][MAX_STRING];
int distance[MAX_DIM][MAX_DIM];
int size;

/* Find nearest END to any cell */
#define INSIDE(x)   ((x) >= 0 && (x) < size)
void find_all_nearest() {
    struct {
        int row, col;
    } queue[MAX_DIM * MAX_DIM], current;
    int i, j, k, front, rear;
    int drow[MAX_DIR] = {0, 1, 0, -1}, dcol[MAX_DIR] = {1, 0, -1, 0};

    for (i = 0; i < size; i++) 
        for (j = 0; j < size; j++)
            distance[i][j] = (map[i][j] == END ? 0 : INFINITY);
    for (i = front = rear = 0; i < size; i++) 
        for (j = 0; j < size; j++)
            if (map[i][j] == END)
                for (k = 0; k < MAX_DIR; k++) {
                    int pi = i + drow[k], pj = j + dcol[k];
                    if (INSIDE(pi) && INSIDE(pj) && 
                            distance[pi][pj] == INFINITY) {
                        distance[pi][pj] = 1;
                        queue[rear].row = pi, queue[rear].col = pj;
                        rear++;
                    }
                }
    while (front < rear) {
        current = queue[front++];
        for (k = 0; k < MAX_DIR; k++) {
            i = current.row + drow[k], j = current.col + dcol[k];
            if (INSIDE(i) && INSIDE(j) && distance[i][j] == INFINITY) {
                distance[i][j] = distance[current.row][current.col] + 1;
                queue[rear].row = i, queue[rear].col = j;
                rear++;
            }
        }
    }
}

/* Find longest distance from any START */
int find_longest() {
    int i, j, longest;
    find_all_nearest();
    for (i = longest = 0; i < size; i++)
        for (j = 0; j < size; j++)
            if (map[i][j] == START && distance[i][j] > longest)
                longest = distance[i][j];
    return longest;
}

/* Main function */
int main() {
    while (scanf("%d", &size) != EOF) {
        int i;
        for (i = 0; i < size; i++) 
            assert(scanf(" %s", map[i]) != EOF);
        printf("%d\n", find_longest());
    }
    return EXIT_SUCCESS;
}
