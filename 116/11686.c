/* 11686
 * Pick up sticks
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       1000000
#define UNVISITED   0
#define ENQUEUED    1
#define FREE        2

typedef struct node_s {
    int top;
    struct node_s *next;
} node_t;

node_t *required[MAX_N];
int sequence[MAX_N];
char status[MAX_N];
int n, seq;

/* Insert requirement */
void insert_req(int above, int bellow) {
    node_t *new = (node_t *) malloc(sizeof (node_t));
    new->top = above;
    new->next = required[bellow];
    required[bellow] = new;
}

/* Free linked list */
void free_node(int i) {
    node_t *node = required[i];
    while (node != NULL) {
        node_t *delete = node;
        node = node->next;
        free(delete);
    }
}

/* Print all nodes respecting requirement, if possible */
int create_sequence(int i) {
    node_t *req = required[i];
    assert(status[i] == UNVISITED);
    status[i] = ENQUEUED;
    while (req != NULL) {
        int j = req->top;
        if (status[j] == ENQUEUED)
            return 0;
        else if (status[j] == UNVISITED)
            if (!create_sequence(j))
                return 0;
        req = req->next;
    }
    sequence[seq++] = i + 1;
    status[i] = FREE;
    return 1;
}

/* Main function */
int main() {
    int i, m, valid;
    while (scanf("%d %d", &n, &m) == 2 && n > 0) {
        for (i = 0; i < n; i++)
            required[i] = NULL, status[i] = UNVISITED;
        for (i = 0; i < m; i++) {
            int a, b;
            assert(scanf("%d %d", &a, &b) == 2);
            insert_req(--a, --b);
        }
        for (i = seq = 0, valid = 1; valid && i < n; i++)
            if (status[i] == UNVISITED)
                valid = create_sequence(i);
        if (valid) {
            assert(seq == n);
            for (i = 0; i < seq; i++)
                printf("%d\n", sequence[i]);
        }
        else
            puts("IMPOSSIBLE");
        for (i = 0; i < n; i++)
            if (required[i] != NULL)
                free_node(i);
    }
    return EXIT_SUCCESS;
}
