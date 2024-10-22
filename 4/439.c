/* 439
 * Knight Moves
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_GRID        8
#define MAX_DIMENSION   (MAX_GRID * MAX_GRID)
#define MAX_MOVES       8
#define STRING_SIZE     4

typedef struct {
    int x, y;
} cell_t, *cell_p;

cell_t move[MAX_MOVES] = {{1, -2}, {2, -1}, {2, 1}, {1, 2}, {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}};

/* Find number of steps until goal is reached */
#define IN(x)       ((x) >= 0 && (x) < MAX_GRID)
#define VISITED(c)  (grid[(c).x][(c).y])
int find_steps(cell_p origin, cell_p goal) {
    struct {
        cell_t cell;
        int distance;
    } queue[MAX_DIMENSION], next;
    int i, front, end;
    char grid[MAX_GRID][MAX_GRID];

    queue[0].cell = *origin, queue[0].distance = 0, front = 0, end = 1;
    memset(grid, 0, MAX_DIMENSION);
    VISITED(*origin) = 1;
    while (front < end) {
        origin = &queue[front].cell;
        if (origin->x == goal->x && origin->y == goal->y) {
            return queue[front].distance;
        }
        for (i = 0; i < MAX_MOVES; i++) {
            next.cell.x = origin->x + move[i].x, next.cell.y = origin->y + move[i].y;
            next.distance = queue[front].distance + 1;
            if (IN(next.cell.x) && IN(next.cell.y) && !VISITED(next.cell)) {
                queue[end++] = next;
                VISITED(next.cell) = 1;
            }
        }
        front++;
    }
    assert(NULL);
    return -1;
}

/* Main function */
#define DECODE(c, s)    (c).x = (s)[0] - 'a'; (c).y = (s)[1] - '1';
int main() {
    char origin_str[STRING_SIZE], destiny_str[STRING_SIZE];
    while (scanf(" %s %s", origin_str, destiny_str) != EOF) {
        cell_t origin, destiny;
        DECODE(origin, origin_str);
        DECODE(destiny, destiny_str);
        printf("To get from %s to %s takes %d knight moves.\n", origin_str, destiny_str,
                find_steps(&origin, &destiny));        
    }
    return 0;
}
