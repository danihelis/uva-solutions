/* 989
 * Su Doku
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIM     3
#define MAX_N       (MAX_DIM * MAX_DIM)
#define MAX_SIZE    (MAX_N * MAX_N)

#define ROW         0
#define COLUMN      1
#define GRID        2
#define MAX_REGIONS 3

#define FOUND       1
#define ERROR       -1
#define NOT_FOUND   0

#define BIT(a)      (1 << ((a) - 1))

typedef struct {
    int solution, candidates, num_candidates;
} cell_t;

typedef struct {
    int num_free;
    cell_t previous[MAX_SIZE];
} solution_t;

typedef struct {
    int place, index;
} coord_t;

cell_t cell[MAX_SIZE];
solution_t solution[MAX_SIZE];
int dim, n, size, num_solutions, num_free;


/* Convert position into region coordinate */
coord_t into_coord(int region, int position) {
    coord_t coord;
    if (region == ROW) {
        coord.place = position / n;
        coord.index = position % n;
    } else if (region == COLUMN) {
        coord.place = position % n;
        coord.index = position / n;
    } else {
        int r = position / n, c = position % n;
        coord.place = (r / dim) * dim + (c / dim);
        coord.index = (r % dim) * dim + (c % dim);
    }
    return coord;
}

/* Convert region coordinate into position */
int into_pos(int region, coord_t coord) {
    int r, c;
    if (region == ROW) return coord.place * n + coord.index;
    if (region == COLUMN) return coord.place + coord.index * n;
    r = (coord.place / dim) * dim + coord.index / dim;
    c = (coord.place % dim) * dim + coord.index % dim;
    return r * n + c;
}

/* Mark solution in a cell position */
void mark_solution(int pos, int answer) {
    int r, p;
    coord_t base, coord;
    cell[pos].solution = answer;
    num_free--;
    for (r = 0; r < MAX_REGIONS; r++) {
        coord = base = into_coord(r, pos);
        for (coord.index = 0; coord.index < n; coord.index++) {
            if (coord.index == base.index) continue;
            p = into_pos(r, coord);
            if (cell[p].solution == 0 && (cell[p].candidates & BIT(answer))) {
                cell[p].candidates -= BIT(answer);
                cell[p].num_candidates--;
            }
        }
    }
}

/* Record solution */
void record_solution() {
    int p;
    solution_t *sol = &solution[num_solutions++];
    sol->num_free = num_free;
    for (p = 0; p < size; p++) {
        sol->previous[p] = cell[p];
    }
}

/* Restore last solution */
void restore_solution() {
    int p;
    solution_t *sol = &solution[num_solutions - 1];
    for (p = 0; p < size; p++) {
        cell[p] = sol->previous[p];
    }
    num_free = sol->num_free;
}

/* Find cell with single candidate */
int find_single_candidate() {
    int pos, ans;
    for (pos = 0; pos < size; pos++) {
        if (cell[pos].solution > 0) continue;
        if (cell[pos].num_candidates == 0) return ERROR;
        else if (cell[pos].num_candidates == 1) {
            for (ans = 1; ans <= n; ans++) {
                if (cell[pos].candidates & BIT(ans)) {
                    mark_solution(pos, ans);
                    return FOUND;
                }
            }
        }
    }
    return NOT_FOUND;
}

/* Find smallest solution */
int find_smallest_solution(int pos) {
    int ans, result = NOT_FOUND;
    while (num_free > 0) {
        result = find_single_candidate();
        if (result != FOUND) break;
    }
    if (num_free == 0) return FOUND;
    if (result == ERROR) return ERROR;
    record_solution();
    for (; cell[pos].solution > 0; pos++)
        ;
    for (ans = 1; ans <= n; ans++) {
        if (cell[pos].candidates & BIT(ans)) {
            mark_solution(pos, ans);
            result = find_smallest_solution(pos + 1);
            if (result == FOUND) return FOUND;
            restore_solution();
        }
    }
    num_solutions--;
    return NOT_FOUND;
}

/* Validate integrity of cell */
int validate_integrity(int pos) {
    int r, p;
    coord_t base, coord;
    for (r = 0; r < MAX_REGIONS; r++) {
        coord = base = into_coord(r, pos);
        for (coord.index = 0; coord.index < n; coord.index++) {
            if (coord.index == base.index) continue;
            p = into_pos(r, coord);
            if (cell[p].solution == cell[pos].solution) return 0;
        }
    }
    return 1;
}

/* Read board and check validity */
int read_board_and_check() {
    int pos, given, valid;
    n = dim * dim;
    size = n * n;
    num_solutions = 0, num_free = size;
    for (pos = 0; pos < size; pos++) {
        cell_t *c = &cell[pos];
        c->solution = 0;
        c->candidates = (1 << n) - 1;
        c->num_candidates = n;
    }
    for (pos = 0, valid = 1; pos < size; pos++) {
        assert(scanf("%d", &given) != EOF);
        if (given > 0) {
            mark_solution(pos, given);
            valid &= validate_integrity(pos);
        }
    }
    return valid ? FOUND : ERROR;
}

/* Print solution */
void print_solution() {
    int p;
    for (p = 0; p < size; p++) {
        printf("%d%c", cell[p].solution, (p + 1) % n == 0 ? '\n' : ' ');
    }
}

/* Main function */
int main() {
    int result, first = 1;
    while (scanf("%d", &dim) != EOF) {
        first ? (first = 0) : printf("\n");
        result = read_board_and_check();
        if (result != ERROR) result = find_smallest_solution(0);
        if (result == FOUND) print_solution(); 
        else printf("NO SOLUTION\n");
    }
    return EXIT_SUCCESS;
}
