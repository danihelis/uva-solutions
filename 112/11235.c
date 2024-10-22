/* 11235
 * Frequent values
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_LIMIT 100000
#define NUM_TYPES 3

typedef enum {
    LEFT_BOUNDARY,
    RIGHT_BOUNDARY,
    GENERAL
} type_t;

typedef struct interval_s {
    struct interval_s *left, *right;
    int start, end;
    int count[NUM_TYPES], *best;
} interval_t, *interval_p;

int number[MAX_LIMIT];

/* Build interval tree recursively */
void build_tree(interval_p *interval, int start, int end) {
    *interval = (interval_p) malloc(sizeof (interval_t));
    (*interval)->start = start, (*interval)->end = end;
    if (start == end - 1) {
        (*interval)->count[LEFT_BOUNDARY] = 1, (*interval)->count[RIGHT_BOUNDARY] = 1,
            (*interval)->count[GENERAL] = 1;
        (*interval)->best = &number[start];
        (*interval)->left = NULL, (*interval)->right = NULL;
    }
    else {
        int half = (start + end) / 2;
        build_tree(&(*interval)->left, start, half);
        build_tree(&(*interval)->right, half, end);
        (*interval)->count[LEFT_BOUNDARY] = (*interval)->left->count[LEFT_BOUNDARY] +
            (number[start] == number[half] ? (*interval)->right->count[LEFT_BOUNDARY] : 0);
        (*interval)->count[RIGHT_BOUNDARY] = (*interval)->right->count[RIGHT_BOUNDARY] +
            (number[half - 1] == number[end - 1] ? (*interval)->left->count[RIGHT_BOUNDARY] : 0);
        if (*(*interval)->left->best == *(*interval)->right->best) {
            (*interval)->count[GENERAL] = (*interval)->left->count[GENERAL] +
                (*interval)->right->count[GENERAL];
            (*interval)->best = (*interval)->left->best;
        }
        else if ((*interval)->left->count[GENERAL] > (*interval)->right->count[GENERAL]) {
            (*interval)->count[GENERAL] = (*interval)->left->count[GENERAL];
            (*interval)->best = (*interval)->left->best;
        }
        else {
            (*interval)->count[GENERAL] = (*interval)->right->count[GENERAL];
            (*interval)->best = (*interval)->right->best;
        }
        if ((*interval)->count[LEFT_BOUNDARY] > (*interval)->count[GENERAL]) {
            (*interval)->count[GENERAL] = (*interval)->count[LEFT_BOUNDARY];
            (*interval)->best = &number[start];
        }
        if ((*interval)->count[RIGHT_BOUNDARY] > (*interval)->count[GENERAL]) {
            (*interval)->count[GENERAL] = (*interval)->count[RIGHT_BOUNDARY];
            (*interval)->best = &number[end - 1];
        }
        if (number[half - 1] == number[half] && (*interval)->left->count[RIGHT_BOUNDARY] +
                (*interval)->right->count[LEFT_BOUNDARY] > (*interval)->count[GENERAL]) {
            (*interval)->count[GENERAL] = (*interval)->left->count[RIGHT_BOUNDARY] +
                (*interval)->right->count[LEFT_BOUNDARY];
            (*interval)->best = &number[half];
        }
    }
}

/* Find most count in interval */
#define MINIMUM(x, y) ((x) < (y) ? (x) : (y))
#define MAXIMUM(x, y) ((x) > (y) ? (x) : (y))
int find_most_count(interval_p interval, int start, int end) {
    assert(start >= interval->start && end <= interval->end && start < end);
    if (interval->start == start && interval->end == end) {
        return interval->count[GENERAL];
    }
    else {
        int half = interval->right->start;
        if (start >= half) {
            return find_most_count(interval->right, start, end);
        }
        else if (end <= half) {
            return find_most_count(interval->left, start, end);
        }
        else {
            int best_left, best_right, center = 0;
            best_left = find_most_count(interval->left, start, half);
            best_right = find_most_count(interval->right, half, end);
            if (number[half - 1] == number[half]) {
                center = MINIMUM(interval->left->count[RIGHT_BOUNDARY], half - start) +
                    MINIMUM(interval->right->count[LEFT_BOUNDARY], end - half);
            }
            return MAXIMUM(MAXIMUM(best_left, best_right), center);
        }
    }
}

/* Deallocate tree */
void free_tree(interval_p tree) {
    if (tree != NULL) {
        free_tree(tree->left);
        free_tree(tree->right);
        free(tree);
    }
}

/* Main function */
int main() {
    int num_numbers;
    while (scanf("%d", &num_numbers) != EOF && num_numbers > 0) {
        int i, num_queries;
        interval_p root;
        assert(scanf("%d", &num_queries));
        for (i = 0; i < num_numbers; i++) {
            assert(scanf("%d", &number[i]) != EOF);
        }
        build_tree(&root, 0, num_numbers);
        for (i = 0; i < num_queries; i++) {
            int start, end;
            assert(scanf("%d %d", &start, &end) != EOF);
            printf("%d\n", find_most_count(root, --start, end));
        }
        free_tree(root);
    }
    return 0;
}
