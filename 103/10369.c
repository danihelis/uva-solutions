/* 10369
 * Arctic Network
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_POSTS 500

typedef struct post_s {
    struct post_s *set;
    int x, y;
} post_t, *post_p;

post_t post[MAX_POSTS];
int num_posts;

typedef struct {
    post_p pair[2];
    int distance;
} link_t, *link_p;

link_t link[MAX_POSTS * MAX_POSTS];
link_p link_index[MAX_POSTS * MAX_POSTS];
int num_links;

/* Find post set */
post_p find_set(post_p post) {
    if (post != post->set) {
        post->set = find_set(post->set);
    }
    return post->set;
}

/* Compare two links in order to sort them */
int compare_link(const void *a, const void *b) {
    return (*((link_p *) a))->distance - (*((link_p *) b))->distance;
}

/* Find n-th longest link */
#define SQUARE(x) ((x) * (x))
link_p find_maximal(int order) {
    int i, j;
    for (i = 0, num_links = 0; i < num_posts - 1; i++) {
        for (j = i + 1; j < num_posts; j++) {
            link[num_links].pair[0] = &post[i], link[num_links].pair[1] = &post[j];
            link[num_links].distance = SQUARE(post[i].x - post[j].x) + 
                SQUARE(post[i].y - post[j].y);
            link_index[num_links] = &link[num_links];
            num_links++;
        }
    }
    qsort(link_index, num_links, sizeof (link_p), compare_link);
    for (i = 0, j = 0; j < order && i < num_links; i++) {
        post_p set_a = find_set(link_index[i]->pair[0]), set_b = find_set(link_index[i]->pair[1]);
        if (set_a != set_b) {
            set_a->set = set_b; /* join sets */
            j++;
        }
    }
    assert(j == order);
    return link_index[--i];
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        int i, num_satelites;
        link_p longest;
        assert(scanf("%d %d", &num_satelites, &num_posts) != EOF);
        for (i = 0; i < num_posts; i++) {
            assert(scanf("%d %d", &post[i].x, &post[i].y) != EOF);
            post[i].set = &post[i];
        }
        longest = find_maximal(num_posts - num_satelites);
        printf("%.2f\n", sqrt((double) longest->distance));
    }
    return 0;
}
