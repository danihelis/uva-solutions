/* 1098
 * Robots on Ice
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIM     8
#define MAX_STACK   (MAX_DIM * MAX_DIM)
#define VISITED     -1
#define NUM_STOPS   4
#define NUM_DIRS    4

#define IN(x,v)     ((x) >= 0 && (x) < v)

typedef struct {
    int row, col;
} point_t;

char grid[MAX_DIM][MAX_DIM], degree[MAX_DIM][MAX_DIM];
int rows, columns;
int num_steps[NUM_STOPS];
point_t stops[NUM_STOPS];

/* Prune solution if there is a node with degree <= 1 */
int prune(point_t cell) {
    int i, j;
    for (i = 0; i < rows; i++)
        for (j = 0; j < columns; j++)
            if (!(i == cell.row && j == cell.col) && 
                    !(i == 0 && j == 1) && 
                    grid[i][j] != VISITED &&
                    degree[i][j] <= 1)
                return 1;
    return 0;
}

/* Look for next point */
int find_ways(point_t cell, int steps, int n) {
    static int drow[NUM_DIRS] = {0, 1, 0, -1}, 
               dcol[NUM_DIRS] = {1, 0, -1, 0};
    int i, ways = 0;
    char before_visited = grid[cell.row][cell.col];
    if (n == NUM_STOPS)
        return 1;
    else if (steps >= num_steps[n] ||
            abs(cell.row - stops[n].row) + abs(cell.col - stops[n].col) +
                steps > num_steps[n])
        return 0;
    else if (steps % 2 == 0 && prune(cell))
        return 0;
    grid[cell.row][cell.col] = VISITED;
    steps++;
    for (i = 0; i < NUM_DIRS; i++) {
        point_t next;
        next.row = cell.row + drow[i], next.col = cell.col + dcol[i];
        if (IN(next.row, rows) && IN(next.col, columns))
            degree[next.row][next.col]--;
    }
    for (i = 0; i < NUM_DIRS; i++) {
        point_t next;
        next.row = cell.row + drow[i], next.col = cell.col + dcol[i];
        if (IN(next.row, rows) && IN(next.col, columns)) {
            int status = grid[next.row][next.col];
            if (status == 0)
                ways += find_ways(next, steps, n);
            else if (status == n + 1 && num_steps[n] == steps)
                ways += find_ways(next, steps, n + 1);
        }
    }
    grid[cell.row][cell.col] = before_visited;
    for (i = 0; i < NUM_DIRS; i++) {
        point_t next;
        next.row = cell.row + drow[i], next.col = cell.col + dcol[i];
        if (IN(next.row, rows) && IN(next.col, columns))
            degree[next.row][next.col]++;
    }
    return ways;
}

/* Main function */
int main() {
    int test = 0;
    point_t start = {0, 0};
    while (scanf("%d %d", &rows, &columns) != EOF && rows > 0) {
        int i, j, max_steps = rows * columns;
        for (i = 0; i < rows; i++)
            for (j = 0; j < columns; j++) {
                grid[i][j] = 0;
                degree[i][j] = 4 - (i == 0 || i == rows - 1 ? 1 : 0)
                        - (j == 0 || j == columns - 1 ? 1 : 0);
            }
        for (i = 0; i < NUM_STOPS; i++) {
            int row, col;
            if (i == NUM_STOPS - 1)
                row = 0, col = 1;
            else
                assert(scanf("%d %d", &row, &col) != EOF);
            grid[row][col] = i + 1;
            num_steps[i] = max_steps * (i + 1) / 4;
            stops[i].row = row, stops[i].col = col;
        }
        max_steps = num_steps[0] > 1 ? find_ways(start, 1, 0) : 
                stops[0].row == 0 && stops[0].col == 0 ? 
                find_ways(start, 1, 1) :  0;
        printf("Case %d: %d\n", ++test, max_steps);
    }
    return EXIT_SUCCESS;
}
