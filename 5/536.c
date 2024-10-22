/* 536
 * Tree Recovery
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING      30

typedef char string_t[MAX_STRING];
string_t postorder;
int index;

/* Reconstruct tree */
void visit_node(char *pre, char *in, int len) {
    char node = pre[0];
    char *nodepos = strchr(in, node);
    int left, right;
    assert(nodepos != NULL);
    left = nodepos - in;
    if (left > 0)
        visit_node(pre + 1, in, left);
    right = len - left - 1;
    if (right > 0)
        visit_node(pre + left + 1, nodepos + 1, right);
    postorder[index++] = node;
}

/* Main function */
int main() {
    string_t preorder, inorder;
    while (scanf(" %s %s", preorder, inorder) != EOF) {
        index = 0;
        visit_node(preorder, inorder, strlen(preorder));
        postorder[index] = 0;
        printf("%s\n", postorder);
    }
    return EXIT_SUCCESS;
}
