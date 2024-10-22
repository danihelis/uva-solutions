/* 10701
 * Pre, in and post
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  55

/* Print post order visit of represented tree */
void post_order_visit(char *in, char *pre, int size) {
    int left = strchr(pre, *in) - pre;
    int right = size - left - 1;
    if (left > 0)
        post_order_visit(in + 1, pre, left);
    if (right > 0)
        post_order_visit(in + left + 1, pre + left + 1, right);
    printf("%c", *in);
}

/* Main function */
int main() {
    char inorder[MAX_STRING], preorder[MAX_STRING];
    int n;
    assert(scanf("%*d") != EOF);
    while (scanf("%d %s %s", &n, inorder, preorder) == 3) {
        post_order_visit(inorder, preorder, n);
        puts("");
    }
    return EXIT_SUCCESS;
}
