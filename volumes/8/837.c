/* 837
 * Light and Transparencies
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>
#include <float.h>

#define MIN(x, y) (x < y ? x : y)
#define MAX(x, y) (x > y ? x : y)

typedef struct node_s {
    double coefficient;
    double point;
    struct node_s *next;
} node_t, *node_p;

node_t list = {1.0, - DBL_MAX, NULL};

/* Insert a new node on the list, copying the current coefficient */
node_p insert_node(node_p from, double point) {
    node_p new_node = (node_p) malloc(sizeof (node_t));
    new_node->point = point;
    new_node->coefficient = from->coefficient;
    new_node->next = from->next;
    from->next = new_node;
    return new_node;
}

/* Insert a segment in the list */
void insert_segment(double x1, double x2, double coef) {
    node_p node = &list, previous;
    double previous_coef;
    while (node->next != NULL && x1 > node->next->point) {
        node = node->next;
    }
    node = insert_node(node, x1);
    do {
        previous_coef = node->coefficient;
        node->coefficient *= coef;
        previous = node;
        node = node->next;
    } while (node != NULL && x2 > node->point);
    node = insert_node(previous, x2);
    node->coefficient = previous_coef;
}

/* Print list of segments */
void print_list() {
    node_p node = &list;
    while (node->next != NULL) {
        if (node == &list) {
            printf("-inf");
        }
        else {
            printf("%.3f", node->point);
        }
        printf(" %.3f %.3f\n", node->next->point, node->coefficient);
        node = node->next;
    }
    printf("%.3f +inf %.3f\n", node->point, node->coefficient);
}

/* Deallocate the linked list */
void free_list() {
    node_p node = list.next; 
    while (node != NULL) {
        node_p next = node->next;
        free(node);
        node = next;
    }
    list.next = NULL;
}

/* Main function */
int main() {
    int test, num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (test = 0; test < num_tests; test++) {
        int line, num_lines;
        assert(scanf("%d", &num_lines) != EOF);
        for (line = 0; line < num_lines; line++) {
            double x1, x2, coef;
            assert(scanf("%lf %*f %lf %*f %lf", &x1, &x2, &coef) != EOF);
            insert_segment(MIN(x1, x2), MAX(x1, x2), coef);
        }
        printf("%s%d\n", (test > 0 ? "\n" : ""), 2 * num_lines + 1);
        print_list();
        free_list();
    }            
    return 0;
}
