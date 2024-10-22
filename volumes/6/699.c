/* 699
 * The Falling Leaves
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define POS(x)      (2 * abs(x) + ((x) >= 0 ? 0 : -1))
#define MAX_SIZE    80

int pile[MAX_SIZE], leftest, rightest;

/* Process tree */
void process_tree(int index) {
    int size;
    assert(scanf("%d", &size) == 1);
    if (size != -1) {
        int pos = POS(index);
        pile[pos] += size;
        if (index < 0 && pos > leftest)
            leftest = pos;
        if (index >= 0 && pos > rightest)
            rightest = pos;
        process_tree(index - 1);
        process_tree(index + 1);
    }
}

/* Main function */
int main() {
    int test = 0, i;
    while (1) {
        memset(pile, 0, sizeof (pile));
        leftest = rightest = -1;
        process_tree(0);
        if (rightest < 0)
            break;
        printf("Case %d:\n", ++test);
        for (i = leftest; i > 0; i -= 2)
            printf("%d ", pile[i]);
        for (i = 0; i <= rightest; i += 2)
            printf("%d%c", pile[i], i == rightest ? '\n' : ' ');
        puts("");
    }
    return EXIT_SUCCESS;
}
