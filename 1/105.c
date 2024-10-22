/* 105
 * The Skyline Problem
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_BUILDS  5000

typedef struct {
    int left, height, right;
} build_t, *build_p;

typedef struct {
    int pos, height;
} point_t, *point_p;

build_t build[MAX_BUILDS];
point_t point[MAX_BUILDS * 2];
int num_builds, num_points;

#define MAX(x,y)    ((x) > (y) ? (x) : (y))

/* Insert new point */
void insert_point(int p) {
    int start = 0, end = num_points;
    while (start < end) {
        int middle = (start + end) / 2;
        if (point[middle].pos == p) {
            return;
        }
        else if (p < point[middle].pos) {
            end = middle;
        }
        else {
            start = middle + 1;
        }
    }
    for (end = num_points; end > start; end--) {
        point[end] = point[end - 1];
    }
    point[start].pos = p, point[start].height = 0;
    num_points++;
}

/* Set maximum height in each point, for each building */
void set_heights() {
    int i, k, j;
    for (i = 0, k = 0; i < num_builds; i++) {
        build_p b = &build[i];
        for (; point[k].pos < b->left; k++)
            ;
        for (j = k; j < num_points && point[j].pos < b->right; j++) {
            point[j].height = MAX(point[j].height, b->height);
        }
    }
}

/* Print the points where height is changed */
void print_points() {
    int last, i, first;
    for (last = 0, i = 0, first = 1; i < num_points; i++) {
        if (point[i].height != last) {
            printf("%s%d %d", first ? "" : " ", point[i].pos, point[i].height);
            last = point[i].height;
            first = 0;
        }
    }
    printf("\n");
}

/* Main function */
int main() {
    int eof = 0;
    num_builds = 0, num_points = 0;
    while (!eof) {
        build_p b = &build[num_builds];
        eof = scanf("%d %d %d", &b->left, &b->height, &b->right) == EOF;
        if (!eof) {
            insert_point(b->left);
            insert_point(b->right);
            num_builds++;
        }
    }
    set_heights();
    print_points();    
    return 0;
}
