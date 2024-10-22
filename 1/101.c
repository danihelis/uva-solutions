/* 101
 * The Blocks Problem
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_BLOCKS  25
#define MAX_STRING  6

#define MOVE_HOME(x)     (x)->stack[0] = (x); (x)->top = 1; (x)->location = (x)

typedef struct block_s {
    struct block_s *stack[MAX_BLOCKS], *location;
    int top;
} block_t, *block_p;

block_t block[MAX_BLOCKS];
int num_blocks;

/* Deque all blocks that are over a given block b */
void deque(int b) {
    block_p stack = block[b].location;
    while (stack->top > 0 && stack->stack[stack->top - 1] != &block[b]) {
        block_p removed = stack->stack[stack->top - 1];
        MOVE_HOME(removed);
        stack->top--;        
    }
}

/* Move all blocks that are over a given block to another block */
void move(int from, int to) {
    block_p origin = block[from].location, destiny = block[to].location;
    int i, p;
    for (i = origin->top - 1; i >= 0 && origin->stack[i] != &block[from]; i--)
        ;
    for (p = i; i < origin->top; i++) {
        block_p moved = origin->stack[i];
        destiny->stack[destiny->top++] = moved;
        moved->location = destiny;
    }
    origin->top = p;
}

/* Main function */
int main() {
    char cmd_from[MAX_STRING], cmd_to[MAX_STRING];
    int i, j, from, to;
    assert(scanf("%d", &num_blocks) != EOF);
    for (i = 0; i < num_blocks; i++) {
        MOVE_HOME(&block[i]);
    }
    while (scanf(" %s %d %s %d", cmd_from, &from, cmd_to, &to) == 4) {
        if (block[from].location == block[to].location) {
            continue;
        }
        if (cmd_from[0] == 'm') {
            deque(from);
        }
        if (cmd_to[1] == 'n') {
            deque(to);
        }
        move(from, to);
    }
    for (i = 0; i < num_blocks; i++) {
        block_p b = &block[i];
        printf("%d:", i);
        for (j = 0; j < b->top; j++) {
            printf(" %ld", b->stack[j] - block);
        }
        printf("\n");
    }
    return 0;
}
