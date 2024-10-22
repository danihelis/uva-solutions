/* 12347
 * Binary Search Tree
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAXINT (1 << 30)

/* Traverse tree */
int traverse(int node, int parent) {
    int next;
    if (scanf("%d", &next) != 1)
        next = -1;
    else {
        if (next < node)
            next = traverse(next, node); /* left */
        if (next != -1 && next < parent)
            next = traverse(next, parent); /* right */
    }
    printf("%d\n", node);
    return next;
}

/* Main function */
int main() {
    int root;
    assert(scanf("%d", &root) == 1);
    assert(traverse(root, MAXINT) == -1);
    return EXIT_SUCCESS;
}
