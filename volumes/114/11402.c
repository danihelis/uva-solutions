/* 11402
 * Ahoy, Pirates!
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_PIRATES     2000000
#define MAX_BLOCK_SIZE  60
#define MAX_BLOCKS      200
#define NUM_BRANCHES    2

#define MIN(x, y)       ((x) < (y) ? (x) : (y))
#define MAX(x, y)       ((x) > (y) ? (x) : (y))

struct node_s;
typedef char block_t[MAX_BLOCK_SIZE];

typedef struct node_s {
    struct node_s *next[NUM_BRANCHES];
    block_t *block;
    int start, middle, end, count;
    char inverted, filled;
} node_t, *node_p;

typedef enum {
    NONE,
    FILL_ZERO,
    FILL_ONE,
    INVERT
} operation_t;

node_t memory[MAX_PIRATES];
node_p memory_ptr;
block_t block[MAX_BLOCKS];
block_t *block_ptr;

/* Join two nodes to compose one new */
node_p join_two(node_p a, node_p b) {
    node_p new = memory_ptr++;
    new->start = a->start;
    new->middle = b->start;
    new->end = b->end;
    assert(new->start <= new->middle && new->middle <= new->end);
    new->next[0] = a, new->next[1] = b;
    new->count = a->count + b->count;
    new->inverted = 0;
    new->block = NULL;
    new->filled = (new->count == 0 || new->count == new->end - new->start);
    return new;
}

/* Create tree of segments bottom up */
node_p create_tree() {
    node_p start_point, end_point, left_out, node;
    start_point = memory, left_out = NULL;
    while (start_point < memory_ptr) {
        if (memory_ptr - start_point == 1) {
            if (left_out != NULL) {
                start_point = join_two(start_point, left_out);
            }
            break;
        }
        for (end_point = memory_ptr, node = start_point; 
                node < end_point - 1; node += 2) {
            join_two(node, node + 1);
        }
        if (node < end_point) {
            if (left_out == NULL) {
                left_out = node;
            }
            else {
                join_two(node, left_out);
                left_out = NULL;
            }
        }
        start_point = end_point;
    }
    return start_point;
}

/* Transform a block node into a tree node */
#define TRANSFORM_TREE(n) do { \
        if ((n)->block != NULL) { \
            create_tree_from_block((n), 0, 0, NULL, NONE); \
        } \
    } while (0)

/* Create tree of segments from a starting block */
node_p create_tree_from_block(node_p existent, int start, int end, char *data, 
        operation_t op) {
    node_p node;
    if (existent != NULL) {
        node = existent;
        start = node->start, end = node->end;
        data = *node->block;
        op = (node->filled ? (node->count > 0 ? FILL_ONE : FILL_ZERO) : NONE);
    }
    else {
        node = memory_ptr++;
        node->start = start, node->end = end;
        node->inverted = 0;
    }
    node->middle = (start + end) / 2;
    node->block = NULL;
    if (end - start == 1) {
        node->count = (op == NONE ? (*data == '0' ? 0 : 1) : op == FILL_ZERO ? 0 : 1);
    }
    else {
        int k;
        for (k = 0, node->count = 0; k < NUM_BRANCHES; k++) {
            node_p half = create_tree_from_block(NULL,
                    (k == 0 ? start : node->middle), 
                    (k == 0 ? node->middle : end),
                    (k == 0 ? data : data + (node->middle - node->start)), 
                    op);
            node->next[k] = half;
            node->count += half->count;
        }
    }
    node->filled = (node->count == 0 || node->count == end - start);
    return node;
}

/* Update inverted status */
#define UPDATE_INVERTED(n) do { \
        if ((n)->inverted) { \
            int k; \
            (n)->inverted = 0; \
            (n)->count = (n)->end - (n)->start - (n)->count; \
            for (k = 0; k < NUM_BRANCHES; k++) \
                (n)->next[k]->inverted = !(n)->next[k]->inverted; \
        } \
    } while (0)

/* Query segment to get numbers of ones */
#define QUERY_NODE(n)       (query_segment((n), (n)->start, (n)->end))
int query_segment(node_p node, int start, int end) {
    int total = 0;
    assert(start >= node->start && end <= node->end && start < end);
    if (node->start == start && node->end == end) {
        return (node->inverted ? end - start - node->count : node->count);
    }
    if (node->filled) {
        return (node->count > 0 ? (node->inverted ? 0 : end - start) : 
                (node->inverted ? end - start : 0));
    }
    TRANSFORM_TREE(node);
    UPDATE_INVERTED(node);
    if (start < node->middle) {
        total += query_segment(node->next[0], start, MIN(end, node->middle));
    }
    if (end > node->middle) {
        total += query_segment(node->next[1], MAX(start, node->middle), end);
    }
    return total;
}


/* Fill segment with either 0 or 1 or invertion and return the new count */
#define FILL_NODE(n,o)      (fill_segment((n), (n)->start, (n)->end, (o)))
void fill_segment(node_p node, int start, int end, operation_t op) {
    assert(start >= node->start && end <= node->end && start < end);
    if (node->start == start && node->end == end) {
        if (op == INVERT) {
            node->inverted = !node->inverted;
        }
        else {
            node->count = (op == FILL_ZERO ? 0 : end - start);
            node->filled = 1, node->inverted = 0;
        }
        return;
    }
    if (node->filled) {
        switch (op) {
            case FILL_ZERO: 
                if ((node->count == 0 && !node->inverted) ||
                        (node->count > 0 && node->inverted)) 
                    return;
                break;
            case FILL_ONE:
                if ((node->count > 0 && !node->inverted) ||
                        (node->count == 0 && node->inverted)) 
                    return;
                break;
            default:
                (void) NULL;
        }
    }
    TRANSFORM_TREE(node);
    UPDATE_INVERTED(node);    
    if (node->filled) {
        int k;
        for (k = 0; k < NUM_BRANCHES; k++) {
            FILL_NODE(node->next[k], (node->count == 0 ? FILL_ZERO : FILL_ONE));
        }
    }
    if (start < node->middle) {
        fill_segment(node->next[0], start, MIN(end, node->middle), op);
    }
    if (end > node->middle) {
        fill_segment(node->next[1], MAX(start, node->middle), end, op);
    }
    node->count = QUERY_NODE(node->next[0]) + QUERY_NODE(node->next[1]);
    node->filled = (node->count == 0 || node->count == node->end - node->start);
}

/* Create base */
void create_base() {
    int num_blocks, start;
    assert(scanf("%d", &num_blocks) != EOF);
    for (memory_ptr = memory, block_ptr = block, start = 0; 
            num_blocks > 0; num_blocks--, block_ptr++) {
        int block_size, count, num_times;
        char *p;
        assert(scanf(" %d %[01]", &num_times, *block_ptr) != EOF);
        for (p = *block_ptr, block_size = 0, count = 0; *p != 0; p++, block_size++) {
            count += (*p == '0' ? 0 : 1);                    
        }
        for (; num_times > 0; num_times--, start += block_size) {
            node_p node = memory_ptr++;
            node->start = start, node->end = start + block_size;
            node->block = block_ptr;
            node->count = count;
            node->inverted = 0;
            node->filled = (count == 0 || count == block_size);
        }
    }
}

/* Main function */
int main() {
    int test, num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (test = 1; test <= num_tests; test++) {
        int num_queries, query;
        node_p tree;
        create_base();
        tree = create_tree();
        printf("Case %d:\n", test);
        assert(scanf("%d", &num_queries) != EOF);
        for (query = 0; num_queries > 0; num_queries--) {
            char op;
            int start, end;
            assert(scanf(" %c %d %d", &op, &start, &end) != EOF);
            end++;
            if (op == 'S') {
                int value = query_segment(tree, start, end);
                printf("Q%d: %d\n", ++query, value);
            }
            else {
                fill_segment(tree, start, end, (op == 'F' ? FILL_ONE : 
                            op == 'E' ? FILL_ZERO : INVERT));
            }
        }
    }
    return 0;
}
