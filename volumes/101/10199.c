/* 10199
 * Tourist Guide
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N           100
#define MAX_STRING      34

typedef struct node_s {
    char name[MAX_STRING];
    struct node_s *edge[MAX_N], *parent;
    int num_edges, low, visited, is_art;
} node_t;

node_t node[MAX_N], *dict[MAX_N];
int num_nodes;

/* Find or insert new node */
node_t * find_or_insert(char *name) {
    int start = 0, end = num_nodes;
    node_t *new;
    while (start < end) {
        int middle = (start + end) / 2;
        int cmp = strcmp(name, dict[middle]->name);
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
    strcpy(new->name, name);
    new->num_edges = 0;
    return new;
}

/* Set low scores on graph to determine articulation points */
void set_low(node_t * cur, int *count) {
    int i, children, can_be_art;

    cur->low = cur->visited = ++(*count);
    for (i = children = can_be_art = 0; i < cur->num_edges; i++) {
        node_t *next = cur->edge[i];
        if (!next->visited) {
            next->parent = cur;
            children++;
            set_low(next, count);
            can_be_art |= next->low >= cur->visited;
            if (next->low < cur->low)
                cur->low = next->low;
        }
        else if (next != cur->parent && next->visited < cur->low)
            cur->low = next->visited;
    }
    cur->is_art = (cur->parent != NULL && can_be_art) || (!cur->parent && children > 1);
}

/* Get articulation points for graph */
int get_articulation_points() {
    int i, count, total;
    for (i = 0; i < num_nodes; i++)
        node[i].visited = node[i].is_art = 0, node[i].parent = NULL;
    for (i = count = total = 0; i < num_nodes; i++) {
        if (!node[i].visited)
            set_low(&node[i], &count);
        if (node[i].is_art)
            total++;
    }
    return total;
}

/* Main function */
int main() {
    int n, test = 0;
    while (scanf("%d", &n) == 1 && n > 0) {
        for (num_nodes = 0; n > 0; n--) {
            char name[MAX_STRING];
            assert(scanf(" %s", name) == 1);
            find_or_insert(name);
        }
        assert(scanf("%d", &n) == 1);
        for (; n > 0; n--) {
            char k1[MAX_STRING], k2[MAX_STRING];
            node_t *n1, *n2;
            assert(scanf(" %s %s", k1, k2) == 2);
            n1 = find_or_insert(k1), n2 = find_or_insert(k2);
            n1->edge[n1->num_edges++] = n2;
            n2->edge[n2->num_edges++] = n1;
        }
        n = get_articulation_points();
        if (test > 0)
            puts("");
        printf("City map #%d: %d camera(s) found\n", ++test, n);
        for (n = 0; n < num_nodes; n++)
            if (dict[n]->is_art)
                printf("%s\n", dict[n]->name);
    }
    return EXIT_SUCCESS;
}
