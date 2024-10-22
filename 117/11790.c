/* 11790
 * Murcia's Skyline
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_TOWERS 100000

typedef struct {
    int height, length;
} tower_t, *tower_p;

tower_t tower[MAX_TOWERS];
int height[MAX_TOWERS];
int num_towers;

#define MAX(x, y) ((x) > (y) ? (x) : (y))

/* Compare two integers in order to sort 'em */
int compare_int(const void *a, const void *b) {
    return *((int *) a) - *((int *) b);
}

/* Calculate longest length in a given direction */
int longest_length(int increasing) {
    int i, j;
    int length[MAX_TOWERS], lengthest = 0;
    memset(length, 0, num_towers * sizeof (int));
    for (i = 0; i < num_towers; i++) {
        int *height_index, index, best;
        height_index = (int *) bsearch(&tower[i].height, height, num_towers, sizeof (int),
                compare_int);
        assert(height_index != NULL);
        index = (int) (height_index - height);
        assert(height[index] == tower[i].height);
        assert(index >= 0 && index < num_towers);
        for (j = (increasing ? 0 : num_towers - 1), best = 0; height[j] != height[index];
                j += (increasing ? 1 : -1)) {
            if (length[j] > best) {
                best = length[j];
            }
        }
        length[index] = MAX(best + tower[i].length, length[index]);
        if (length[index] > lengthest) {
            lengthest = length[index];
        }
    }
    return lengthest;
}

/* Main function */
int main() {
    int test, num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (test = 1; test <= num_tests; test++) {
        int i, inc_length, dec_length;
        assert(scanf("%d", &num_towers) != EOF);
        for (i = 0; i < num_towers; i++) {
            assert(scanf("%d", &tower[i].height) != EOF);
            height[i] = tower[i].height;
        }
        for (i = 0; i < num_towers; i++) {
            assert(scanf("%d", &tower[i].length) != EOF);
        }
        qsort(height, num_towers, sizeof (int), compare_int);
        inc_length = longest_length(1), dec_length = longest_length(0);
        printf("Case %d. ", test);
        if (inc_length >= dec_length) {
            printf("Increasing (%d). Decreasing (%d).\n", inc_length, dec_length);
        }
        else {
            printf("Decreasing (%d). Increasing (%d).\n", dec_length, inc_length);
        }
    }
    return 0;
}
