/*
 * 10152
 * ShellSort
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_NAME_SIZE 85
#define MAX_VECTOR_SIZE 200

typedef enum {
    RESULT_VECTOR,
    ORDER_VECTOR
} vector_e;

typedef struct node_s {
    struct node_s *left, *right;
    int index;
} node_t;

typedef struct {
    char name[MAX_NAME_SIZE];
    node_t *order, *result;
} turtle_t;

turtle_t turtle[MAX_VECTOR_SIZE];
int output[MAX_VECTOR_SIZE];
int num_turtles;

node_t order_head, result_head, result_tail;


/* Find name */
int find_name(char *name) {
    int i;
    for (i = 0; i < num_turtles; i++) {
        if (strcmp(turtle[i].name, name) == 0) {
            return i;
        }
    }
    assert(0);
    return -1;
}


/* Remove node from giving index, if exists */
void remove_node(node_t *remove) {
    assert(remove != NULL);
    if (remove->left != NULL) {
        remove->left->right = remove->right;
    }
    if (remove->right != NULL) {
        remove->right->left = remove->left;
    }
    if (result_tail.left == remove) {
        result_tail.left = remove->left;
    }
    remove->left = NULL;
    remove->right = NULL;
}


/* Insert node at left of given node */
void insert_node(node_t *head, node_t *insert) {
    insert->right = head->right;
    if (head->right != NULL) {
        head->right->left = insert;
    }
    head->right = insert;
    insert->left = head;
}


/* Move node of given index to left-most place of order list, updating result vector */
void move_top(int index) {
    node_t *order_node, *result_node;

    order_node = turtle[index].order;
    remove_node(order_node);
    insert_node(&order_head, order_node);

    result_node = turtle[index].result;
    if (result_node == NULL) {
        result_node = (node_t *) malloc(sizeof (node_t));
        result_node->index = index;
        turtle[index].result = result_node;
        if (result_head.right == NULL) {
            result_tail.left = result_node;
        }
    }
    else {
        remove_node(result_node);
    }
    insert_node(&result_head, result_node);
}


/* Find minimum sequence of movements */
void find_movements() {
    int i;
    result_head.right = NULL;
    result_tail.left = NULL;

    for (i = num_turtles - 1; i > 0; i--) {
        while ((i == num_turtles - 1 && turtle[output[i]].order->right != NULL) 
                || (i < num_turtles - 1 && turtle[output[i]].order->right->index != output[i + 1])) {
            move_top(turtle[output[i]].order->right->index);
        }
    }
}


/* Print result */
void print_result() {
    node_t *result = result_tail.left;
    while (result != NULL && result != &result_head) {
        printf("%s", turtle[result->index].name);
        result = result->left;
    }
    printf("\n");
}


/* Free memory */
void free_memory() {
    int i;
    for (i = 0; i < num_turtles; i++) {
        free(turtle[i].order);
        if (turtle[i].result != NULL) {
            free(turtle[i].result);
        }
    }
}


/* Read entries and prepare lists */
void read_data_input(char *line) {
    int i;
    
    assert(fgets(line, MAX_NAME_SIZE, stdin) != NULL);
    num_turtles = atoi(line);
    
    order_head.right = NULL;
    for (i = 0; i < num_turtles; i++) {
        assert(fgets(turtle[i].name, MAX_NAME_SIZE, stdin) != NULL);
        turtle[i].result = NULL;
        
        turtle[i].order = (node_t *) malloc(sizeof(node_t));
        turtle[i].order->index = i;
        insert_node((i == 0 ? &order_head : turtle[i - 1].order), turtle[i].order);
    }
    
    for (i = 0; i < num_turtles; i++) {
        assert(fgets(line, MAX_NAME_SIZE, stdin) != NULL);
        output[i] = find_name(line);
    }
}


/* Main function */
int main() {
    int num_data_sets, data_set;
    char line[MAX_NAME_SIZE];
    
    assert(fgets(line, MAX_NAME_SIZE, stdin) != NULL);
    num_data_sets = atoi(line);
    for (data_set = 0; data_set < num_data_sets; data_set++) {
        read_data_input(line);
        find_movements();
        print_result();
        free_memory();
    }
    
    return 0;
}
