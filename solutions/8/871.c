/* 871
 * Counting Cells in a Blob
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_LINES   25
#define MAX_STRING  (MAX_LINES + 5)
#define MAX_DIM     (MAX_LINES * MAX_LINES)

#define NUM_DIR     8

#define EMPTY   '0'
#define BLOB    '1'

char map[MAX_LINES][MAX_STRING];
int rows, cols;

/* Compute blob's size */
#define IN(x, max)  ((x) >= 0 && (x) < (max))
int get_blob_size(int r, int c) {
    static int dr[NUM_DIR] = {-1, -1, 0, 1, 1, 1, 0, -1},
               dc[NUM_DIR] = {0, 1, 1, 1, 0, -1, -1, -1};
    struct {
        int row, col;
    } queue[MAX_DIM], cur, new;
    int size, front, rear, i;

    queue[0].row = r, queue[0].col = c, front = 0, rear = 1;
    map[r][c] = EMPTY;
    size = 0;

    while (front < rear) {
        cur = queue[front++];
        size++;
        for (i = 0; i < NUM_DIR; i++) {
            new.row = cur.row + dr[i], new.col = cur.col + dc[i];
            if (IN(new.row, rows) && IN(new.col, cols) &&
                    map[new.row][new.col] == BLOB) {
                queue[rear++] = new;
                map[new.row][new.col] = EMPTY;
            }
        }
    }
    return size;
}

/* Compute largest blob */
int get_largest_blob() {
    int r, c, size, largest;
    for (r = 0, largest = 0; r < rows; r++)
        for (c = 0; c < cols; c++)
            if (map[r][c] == BLOB) {
                size = get_blob_size(r, c);
                if (size > largest)
                    largest = size;
            }
    return largest;
}

/* Main function */
#define READ(x)     (fgets(x, MAX_STRING, stdin) != NULL)
int main() {
    char input[MAX_STRING];
    int num_tests;
    assert(READ(input));
    num_tests = atoi(input);
    assert(READ(input));
    for (; num_tests > 0; num_tests--) {
        rows = 0, cols = 0;
        while (READ(map[rows]) && map[rows][0] != '\n')
            rows++;
        cols = strlen(map[0]) - 1;
        printf("%d\n%s", get_largest_blob(), num_tests > 1 ? "\n" : "");
    }
    return EXIT_SUCCESS;
}
