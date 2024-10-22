/* 183
 * Bit Maps
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIM     200
#define MAX_INPUT   (MAX_DIM * MAX_DIM + 2)
#define WIDTH       50

int screen_width = 0;
char bitmap[MAX_INPUT];
int rows, cols;

typedef enum {
    NONE = 0,
    ZERO = 1,
    ONE = 2,
    MIXED = 3
} type_t;

typedef struct node_s {
    type_t type;
    struct node_s *child[4];
    int size;
} node_t;


/* Build compat notation recursivelly from bitmap */
#define ADD(a, b, c, d)   (node->child[node->size++] = build(a, b, c, d))
node_t * build(int r0, int r1, int c0, int c1) {
    node_t *node = (node_t *) malloc(sizeof (node_t));
    node->size = 0;
    if (r1 - r0 == 1 && c1 - c0 == 1)
        node->type = bitmap[r0 * cols + c0] == '0' ? ZERO : ONE;
    else {
        int i, rm = (r0 + r1 + 1) / 2, cm = (c0 + c1 + 1) / 2;
        ADD(r0, rm, c0, cm);
        (cm < c1 ? ADD(r0, rm, cm, c1) : 0);
        (rm < r1 ? ADD(rm, r1, c0, cm) : 0);
        (rm < r1 && cm < c1 ? ADD(rm, r1, cm, c1) : 0);
        for (i = 0, node->type = NONE; i < node->size; i++)
            node->type |= node->child[i]->type;
        if (node->type != MIXED) {
            for (i = 0; i < node->size; i++)
                free(node->child[i]);
            node->size = 0;
        }
    }
    return node;
}

/* Print notation and also delete node */
void print_notation(node_t *node) {
    if (screen_width >= WIDTH) {
        printf("\n");
        screen_width = 0;
    }
    screen_width++;
    if (node->type == MIXED) {
        int i;
        printf("D");
        for (i = 0; i < node->size; i++)
            print_notation(node->child[i]);
    }
    else
        printf("%c", node->type == ZERO ? '0' : '1');
    free(node);
}

/* Reconstruct bitmap from compact notation */
void reconstruct(int r0, int r1, int c0, int c1) {
    char type;
    assert(scanf(" %c", &type) != EOF);
    if (type == '0' || type == '1') {
        int r, c;
        for (r = r0; r < r1; r++)
            for (c = c0; c < c1; c++)
                bitmap[r * cols + c] = type;
    }
    else {
        int rm = (r0 + r1 + 1) / 2, cm = (c0 + c1 + 1) / 2;
        reconstruct(r0, rm, c0, cm);
        (cm < c1 ? reconstruct(r0, rm, cm, c1) : (void) 0);
        (rm < r1 ? reconstruct(rm, r1, c0, cm) : (void) 0);
        (rm < r1 && cm < c1 ? reconstruct(rm, r1, cm, c1) : (void) 0);
    }
}

/* Print bitmap on screen */
void print_bitmap() {
    int i, len = rows * cols;
    for (i = 0; i < len; i++, screen_width++) {
        if (screen_width >= WIDTH) {
            printf("\n");
            screen_width = 0;
        }
        printf("%c", bitmap[i]);
    }
}

/* Main function */
int main() {
    char type;
    while (scanf(" %c", &type) != EOF && type != '#') {
        assert(scanf("%d %d", &rows, &cols) != EOF);
        printf("%c%4d%4d\n", type == 'B' ? 'D' : 'B', rows, cols);
        screen_width = 0;
        if (type == 'B') {
            node_t *node;
            char *p = bitmap;
            int total_len = 0, max_len = rows * cols, len;
            while (total_len < max_len) {
                assert(scanf(" %s", p) != EOF);
                len = strlen(p);
                total_len += len;
                p = p + len;
            }
            node = build(0, rows, 0, cols);
            print_notation(node);
        }
        else {
            reconstruct(0, rows, 0, cols);
            print_bitmap();
        }
        printf("\n");
    }
    return EXIT_SUCCESS;
}
