/* 1220
 * Party at Hali-Bula
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       200
#define MAX_STR     102
#define MAX(x,y)    ((x) > (y) ? (x) : (y))

typedef struct node_s {
    struct node_s *child[MAX_N];
    char name[MAX_STR];
    int num_children, included, excluded, inc_multi, exc_multi;
} node_t;

node_t node[MAX_N], *dict[MAX_N];
int size;

/* Find or insert */
node_t* find_insert(char *name) {
    int start = 0, end = size;
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
    strcpy(node[size].name, name);
    node[size].num_children = 0;
    for (end = size; end > start; end--)
        dict[end] = dict[end - 1];
    dict[start] = &node[size++];
    return dict[start];
}

/* Compute maximum number of invitees */
void compute_max(node_t *n) {
    n->included = 1, n->excluded = 0, n->inc_multi = n->exc_multi = 0;
    if (n->num_children != 0) {
        int i;
        for (i = 0; i < n->num_children; i++) {
            node_t *c = n->child[i];
            compute_max(c);
            n->included += c->excluded, n->inc_multi |= c->exc_multi;
            if (c->excluded > c->included)
                n->excluded += c->excluded, n->exc_multi |= c->exc_multi;
            else if (c->included > c->excluded)
                n->excluded += c->included, n->exc_multi |= c->inc_multi;
            else
                n->excluded += c->included, n->exc_multi = 1;
        }
    }
}

/* Main function */
int main() {
    int n, max, multi;
    while (scanf("%d", &n) == 1 && n > 0) {
        char name[2][MAX_STR];
        node_t *head;
        size = 0;
        assert(scanf(" %s", name[0]) == 1);
        head = find_insert(name[0]);
        for (n--; n > 0; n--) {
            node_t *child, *parent;
            assert(scanf(" %s %s", name[0], name[1]) == 2);
            child = find_insert(name[0]), parent = find_insert(name[1]);
            parent->child[parent->num_children++] = child;
        }
        compute_max(head);
        max = MAX(head->included, head->excluded);
        multi = head->included == head->excluded ? 1 :
                max == head->included ? head->inc_multi : head->exc_multi;
        printf("%d %s\n", max, multi ? "No" : "Yes");
    }
    return EXIT_SUCCESS;
}
