/* 437
 * The Tower of Babylon
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_BLOCKS  (3 * 30)
#define MIN(x,y)    ((x) < (y) ? (x) : (y))
#define MAX(x,y)    ((x) > (y) ? (x) : (y))

typedef struct {
    int b1, b2, height, tower;
} block_t;

block_t block[MAX_BLOCKS];
int num_blocks;

/* Add a block */
void add_block(int x, int y, int z) {
    block[num_blocks].b1 = MIN(x, y);
    block[num_blocks].b2 = MAX(x, y);
    block[num_blocks].height = z;
    block[num_blocks++].tower = 0;
}

/* Read a block and insert their variations */
void read_block() {
    int x, y, z;
    assert(scanf("%d %d %d", &x, &y, &z) == 3);
    add_block(x, y, z);
    if (y != z)
        add_block(x, z, y);
    if (x != z && x != y)
        add_block(z, y, x);
}

/* Compare two blocks */
int compare(const void *a, const void *b) {
    block_t *x = (block_t *) a, *y = (block_t *) b;
    if (x->b1 == y->b1)
        return x->b2 - y->b2;
    return x->b1 - y->b1;
}

/* Compute largest height */
int largest_height() {
    int i, j, max_height;
    qsort(block, num_blocks, sizeof (block_t), compare);
    for (i = num_blocks - 1, max_height = 0; i >= 0; i--) {
        block_t *b = &block[i];
        b->tower = b->height;
        for (j = i + 1; j < num_blocks; j++) {
            block_t *n = &block[j];
            if (b->b1 < n->b1 && b->b2 < n->b2 &&
                    b->height + n->tower > b->tower)
                b->tower = b->height + n->tower;
        }
        if (b->tower > max_height)
            max_height = b->tower;
    }
    return max_height;
}

/* Main function */
int main() {
    int k, test = 0;
    while (scanf("%d", &k) == 1 && k > 0) {
        for (num_blocks = 0; k > 0; k--)
            read_block();
        printf("Case %d: maximum height = %d\n", ++test, largest_height());
    }
    return EXIT_SUCCESS;
}
