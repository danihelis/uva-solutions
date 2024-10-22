/* 12532
 * Interval Product
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_ELEMS       100000
#define MIN(x, y)       ((x) < (y) ? (x) : (y))
#define MAX(x, y)       ((x) > (y) ? (x) : (y))

#define DEFINE(a)       ((a) == 0 ? '0' : (a) > 0 ? '+' : '-')
#define COMBINE(a, b)   (((a) == '0' || (b) == '0') ? '0' : \
                                (a) == (b) ? '+' : '-')

typedef struct interval_s {
    struct interval_s *left, *right;
    int start, end, middle;
    char leaf, value;
} interval_t;

int elem[MAX_ELEMS], size;

/* Build interval tree */
interval_t * build_tree(int start, int end) {
    interval_t *inter = (interval_t *) malloc(sizeof (interval_t));
    assert(start < end);
    inter->start = start, inter->end = end;
    if (end - start == 1) {
        inter->leaf = 1;
        inter->value = DEFINE(elem[start]);
    }
    else {
        inter->leaf = 0;
        inter->middle = (start + end) / 2;
        inter->left = build_tree(start, inter->middle);
        inter->right = build_tree(inter->middle, end);
        inter->value = COMBINE(inter->left->value, inter->right->value);
    }
    return inter;
}

/* Query for an interval */
char query(interval_t *inter, int start, int end) {
    char left = '+', right = '+';
    assert(inter->start <= start && inter->end >= end);
    if (inter->start == start && inter->end == end) {
        return inter->value;
    }
    if (start < inter->middle)
        left = query(inter->left, start, MIN(inter->middle, end));
    if (end > inter->middle)
        right= query(inter->right, MAX(start, inter->middle), end);
    return COMBINE(left, right);
}

/* Change value */
void change(interval_t *inter, int index, int value) {
    assert(inter->start <= index && inter->end > index);
    if (inter->leaf) {
        inter->value = DEFINE(value);
    }
    else {
        if (index < inter->middle)
            change(inter->left, index, value);
        else
            change(inter->right, index, value);
        inter->value = COMBINE(inter->left->value, inter->right->value);
    }
}

/* Free tree */
void free_interval(interval_t *inter) {
    if (!inter->leaf) {
        free_interval(inter->left);
        free_interval(inter->right);
    }
    free(inter);
}

/* Main function */
int main() {
    int i, ops;
    interval_t *tree = NULL;
    while (scanf("%d %d", &size, &ops) != EOF) {
        for (i = 0; i < size; i++) {
            assert(scanf("%d", &elem[i]) != EOF);
        }
        if (tree) 
            free_interval(tree);
        tree = build_tree(0, size);
        for (i = 0; i < ops; i++) {
            char command;
            int p1, p2;
            assert(scanf(" %c %d %d", &command, &p1, &p2) != EOF);
            if (command == 'C')
                change(tree, --p1, p2);
            else
                printf("%c", query(tree, --p1, p2));
        }
        printf("\n");
    }
    return 0;
}
