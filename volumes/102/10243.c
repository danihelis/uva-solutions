/* 10243
 * Fire! Fire!! Fire!!!
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_GALLERIES   1000
#define MIN(x,y)        ((x) < (y) ? (x) : (y))

typedef struct gallery_s {
    struct gallery_s *link[MAX_GALLERIES];
    int num_links;
    int with_exit, without_exit;
    char visited;
} gallery_t, *gallery_p;

gallery_t gallery[MAX_GALLERIES];
int num_galleries;

/* Calculate the minimum number of fire exits */
int get_minimum_exits(gallery_p root) {
    int i;
    assert(!root->visited);
    root->visited = 1;
    root->with_exit = 1;
    root->without_exit = 0;
    for (i = 0; i < root->num_links; i++) {
        gallery_p child = root->link[i];
        if (!child->visited) {
            get_minimum_exits(child);
            root->with_exit += child->without_exit;
            root->without_exit += child->with_exit;
        }
    }
    if (root->with_exit < root->without_exit) {
        root->without_exit = root->with_exit;
    }
    return MIN(root->with_exit, root->without_exit);
}

/* Main function */
int main() {
    while (scanf("%d", &num_galleries) != EOF && num_galleries > 0) {
        int i, j;
        for (i = 0; i < num_galleries; i++) {
            assert(scanf("%d", &gallery[i].num_links) != EOF);
            for (j = 0; j < gallery[i].num_links; j++) {
                int index;
                assert(scanf("%d", &index) != EOF);
                gallery[i].link[j] = &gallery[--index];
            }
            gallery[i].visited = 0;
        }
        if (num_galleries == 1) {
            printf("1\n");
        }
        else {
            printf("%d\n", get_minimum_exits(&gallery[0]));
        }
    }
    return 0;
}
