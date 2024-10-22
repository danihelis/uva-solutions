/* 10946
 * You want what filled?
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       50
#define MAX_HOLES   (MAX_N * MAX_N)
#define MAX_STR     (MAX_N + 2)

#define NUM_DIR     4
#define LAND        '.'

typedef struct {
    char id;
    int size;
} hole_t;

hole_t hole[MAX_HOLES];
char map[MAX_N][MAX_STR];
int num_holes, rows, cols;

/* Fill a hole */
#define IN(x,lim)   ((x) >= 0 && (x) < lim)
void fill_hole(int r, int c) {
    static int drow[NUM_DIR] = {-1, 0, 1, 0}, dcol[NUM_DIR] = {0, 1, 0, -1};
    struct {
        int row, col;
    } queue[MAX_HOLES], cur, new;
    int i, front, rear, total;
    char id = map[r][c];
    queue[0].row = r, queue[0].col = c, front = 0, rear = 1;
    map[r][c] = LAND;
    total = 0;

    while (front < rear) {
        cur = queue[front++];
        total++;
        for (i = 0; i < NUM_DIR; i++) {
            new.row = cur.row + drow[i], new.col = cur.col + dcol[i];
            if (IN(new.row, rows) && IN(new.col, cols) &&
                    map[new.row][new.col] == id)
                queue[rear++] = new, map[new.row][new.col] = LAND;
        }
    }

    hole[num_holes].id = id;
    hole[num_holes].size = total;
    num_holes++;
}

/* Fill all holes */
void fill_all_holes() {
    int r, c;
    for (r = num_holes = 0; r < rows; r++)
        for (c = 0; c < cols; c++)
            if (map[r][c] != LAND)
                fill_hole(r, c);
}

/* Compare holes */
int compare(const void *a, const void *b) {
    hole_t *x = (hole_t *) a, *y = (hole_t *) b;
    if (x->size == y->size)
        return x->id - y->id;
    return y->size - x->size;
}

/* Main function */
int main() {
    int test = 0;
    while (scanf("%d %d", &rows, &cols) == 2 && rows > 0) {
        int i;
        for (i = 0; i < rows; i++)
            assert(scanf(" %s", map[i]) == 1);
        fill_all_holes();
        qsort(hole, num_holes, sizeof (hole_t), compare);
        printf("Problem %d:\n", ++test);
        for (i = 0; i < num_holes; i++)
            printf("%c %d\n", hole[i].id, hole[i].size);
    }
    return EXIT_SUCCESS;
}
