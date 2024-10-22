/* 714
 * Copying Books
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_BOOKS       500
#define MAX_SECTIONS    501

#define MAXIMUM(x,y)    ((x) > (y) ? (x) : (y))

typedef struct solution_s {
    long maximum_cost, cost, start;
    struct solution_s *next;
} solution_t, *solution_p;

solution_t solution[MAX_BOOKS][MAX_SECTIONS];
int pages[MAX_BOOKS];
int num_books;

/* Compute and return the book sectioning with minimum maximum cost */
solution_p get_best_solution(int start, int num_sections) {
    assert(num_sections >= 1);
    if (solution[start][num_sections].maximum_cost > 0) {
        return &solution[start][num_sections];        
    }
    else if (num_sections == 1) {
        solution_p this = &solution[start][num_sections];
        this->cost = 0, this->start = start, this->next = NULL;
        for (; start < num_books; start++) {
            this->cost += pages[start];
        }
        this->maximum_cost = this->cost;
        return this;
    }
    else {
        long this_cost = 0, maximum;
        solution_p this = &solution[start][num_sections];
        this->next = NULL, this->start = start;
        for (; start < num_books - num_sections + 1 &&
                (this->next == NULL || this_cost < this->maximum_cost); start++) {
            solution_p other = get_best_solution(start + 1, num_sections - 1);
            this_cost += pages[start];
            maximum = MAXIMUM(this_cost, other->maximum_cost);
            if (this->next == NULL || maximum < this->maximum_cost) {
                this->next = other;
                this->cost = this_cost;
                this->maximum_cost = maximum;
            }
        }
        return this;
    }
}

/* Improve solution by making the first sections shorter */
void improve_solution(solution_p solution, long limit, int min_start) {
    int i;
    assert(solution != NULL);
    if (solution->next != NULL) {
        int end = solution->next->start - 1;
        improve_solution(solution->next, limit, solution->start + 1);
        for (; end >= solution->next->start; end--) {
            solution->cost -= pages[end];
        }
    }
    for (i = solution->start; i > min_start && solution->cost + pages[i - 1] <= limit; i--) {
        solution->cost += pages[i - 1];
    }
    solution->start = i;
}

/* Print the book sectioning with solution */
void print_solution(solution_p solution) {
    int i;
    assert(solution != NULL);
    improve_solution(solution, solution->maximum_cost, 0);
    for (i = 0, solution = solution->next; i < num_books; i++) {
        if (solution != NULL && solution->start == i) {
            printf(" /");
            solution = solution->next;            
        }
        printf("%s%d", (i > 0 ? " " : ""), pages[i]);
    }
    printf("\n");
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        int i, num_sections;
        assert(scanf("%d %d", &num_books, &num_sections) != EOF);
        for (i = 0; i < num_books; i++) {
            assert(scanf("%d", &pages[i]) != EOF && pages[i] > 0);
            memset(solution[i], 0, (num_sections + 1) * sizeof (solution_t));
        }
        print_solution(get_best_solution(0, num_sections));
    }
    return 0;
}
