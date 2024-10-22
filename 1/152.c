/*
 * 152
 * Tree's a Crowd
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define NUM_BINS 10
#define MAX_TREES 5000
#define NUM_DIMENSIONS 3
typedef struct {
    short value[NUM_DIMENSIONS];
} tree_t;
tree_t tree[MAX_TREES];
int num_trees;
int bin[NUM_BINS];


/* Calculate distance of two trees */
double distance(tree_t *a, tree_t *b) {
    double sum = 0;
    int i;
    for (i = 0; i < NUM_DIMENSIONS; i++) {
        sum += (a->value[i] - b->value[i]) * (a->value[i] - b->value[i]);
    }
    return sqrt(sum);
}


/* Create histogram by finding closest neighbour and increment bin */
#define INFINITY 1E10
void create_histogram() {
    int i, j;
    memset(bin, 0, NUM_BINS * sizeof (int));
    for (i = 0; i < num_trees; i++) {
        double closest = INFINITY;
        int int_value;
        for (j = 0; j < num_trees; j++) {
            if (i != j) {
                double dist = distance(&tree[i], &tree[j]);
                if (dist < closest) {
                    closest = dist;
                }
            }
        }
        int_value = (int) closest;
        if (closest < NUM_BINS) {
            bin[int_value]++;
        }
    }
}


/* Main function */
int main() {
    int b;
    num_trees = 0;
    while (scanf("%hd %hd %hd", &tree[num_trees].value[0], &tree[num_trees].value[1], 
                &tree[num_trees].value[2]) != EOF) {
        if (tree[num_trees].value[0] == 0 && tree[num_trees].value[1] == 0 
                && tree[num_trees].value[2] == 0) {
            break;
        }
        num_trees++;
    }
    create_histogram();
    for (b = 0; b < NUM_BINS; b++) {
        printf("%4d", bin[b]);
    }
    printf("\n");
    return 0;
}
