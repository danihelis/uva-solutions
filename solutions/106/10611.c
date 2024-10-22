/* 10611
 * The Playboy Chimp
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_CHIMPS  50000

typedef struct {
    int height, index;
} chimp_t, *chimp_p;

chimp_t chimp[MAX_CHIMPS];
int num_chimps;

/* Search a chimp by height */
chimp_p find_chimp(int height) {
    int start = 0, end = num_chimps;
    while (start < end) {
        int middle = (start + end) / 2;
        int comparison = (chimp[middle].height == height ? chimp[middle].index : 
                chimp[middle].height - height);
        if (comparison == 0) {
            return &chimp[middle];
        }
        else if (comparison > 0) {
            end = middle;
        }
        else {
            start = middle + 1;
        }
    }
    return (start < num_chimps ? &chimp[start] : NULL);
    
}

/* Main function */
int main() {
    int i, num_queries, height;
    assert(scanf("%d", &num_chimps) != EOF);
    for (i = 0; i < num_chimps; i++) {
        assert(scanf("%d", &chimp[i].height) != EOF);
        chimp[i].index = (i == 0 || chimp[i - 1].height < chimp[i].height ? 0 : 
                chimp[i - 1].index + 1);
    }
    assert(scanf("%d", &num_queries) != EOF);
    for (i = 0; i < num_queries; i++) {
        chimp_p who;
        assert(scanf("%d", &height) != EOF);
        who = find_chimp(height);
        if (who == NULL) {
            printf("%d X\n", chimp[num_chimps - 1].height);
        }
        else {
            (who == chimp ? printf("X ") : printf("%d ", (who - 1)->height));
            who = (who->height > height ? who : find_chimp(height + 1));
            (who == NULL ? printf("X\n") : printf("%d\n", who->height));
        }
    }
    
    return 0;
}
