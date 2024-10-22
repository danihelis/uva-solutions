/* 383
 * Shipping Routes
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       30
#define MAX_CODE    3

typedef struct node_s {
    char code[MAX_CODE];
    struct node_s *edge[MAX_N];
    int num_edges, distance;
    char visited;
} node_t;

node_t node[MAX_N], *dict[MAX_N];
int num_nodes;

/* Find or insert node */
node_t * find_or_insert(char *code) {
    int start = 0, end = num_nodes;
    node_t *new;
    while (start < end) {
        int middle = (start + end) / 2;
        int cmp = strcmp(code, dict[middle]->code);
        if (cmp == 0)
            return dict[middle];
        else if (cmp < 0)
            end = middle;
        else 
            start = middle + 1;
    }
    for (end = num_nodes; end > start; end--)
        dict[end] = dict[end - 1];
    new = dict[start] = &node[num_nodes++];
    strcpy(new->code, code);
    new->num_edges = 0;
    return new;
}

/* Find shortest distance */
int find_shortest_distance(node_t *start, node_t * end) {
    node_t *queue[MAX_N];
    int i, front, rear;
    for (i = 0; i < num_nodes; i++)
        node[i].distance = node[i].visited = 0;
    queue[0] = start, front = 0, rear = 1;
    start->visited = 1;
    while (front < rear) {
        node_t *cur = queue[front++];
        if (cur == end)
            return cur->distance;
        for (i = 0; i < cur->num_edges; i++) {
            node_t *next = cur->edge[i];
            if (!next->visited) {
                next->visited = 1;
                next->distance = cur->distance + 1;
                queue[rear++] = next;
            }
        }
    }
    return -1;
}

/* Main function */
int main() {
    int test, num_tests;
    assert(scanf("%d", &num_tests) == 1);
    puts("SHIPPING ROUTES OUTPUT");
    for (test = 1; test <= num_tests; test++) {
        int m, n, p;
        assert(scanf("%d %d %d", &m, &n, &p) == 3);
        for (num_nodes = 0; m > 0; m--) {
            char code[MAX_CODE];
            assert(scanf(" %s", code) == 1);
            find_or_insert(code);
        }
        for (; n > 0; n--) {
            char c1[MAX_CODE], c2[MAX_CODE];
            node_t *n1, *n2;
            assert(scanf(" %s %s", c1, c2) == 2);
            n1 = find_or_insert(c1), n2 = find_or_insert(c2);
            n1->edge[n1->num_edges++] = n2;
            n2->edge[n2->num_edges++] = n1;
        }
        printf("\nDATA SET  %d\n\n", test);
        for (; p > 0; p--) {
            char c1[MAX_CODE], c2[MAX_CODE];
            int cargo, dist;
            node_t *n1, *n2;
            assert(scanf("%d %s %s", &cargo, c1, c2) == 3);
            n1 = find_or_insert(c1), n2 = find_or_insert(c2);
            dist = find_shortest_distance(n1, n2);
            if (dist < 0)
                puts("NO SHIPMENT POSSIBLE");
            else
                printf("$%d\n", cargo * dist * 100);
        }
    }
    puts("\nEND OF OUTPUT");
    return EXIT_SUCCESS;
}
