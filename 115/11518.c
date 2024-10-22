/* 11518
 * Dominos 2
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   10000

typedef struct {
    int x, y;
} pair_t;

pair_t pair[MAX_N];
int num_dominoes, num_pairs, dropped[MAX_N], start[MAX_N];

/* Compare pair */
int compare(const void *a, const void *b) {
    return ((pair_t *) a)->x - ((pair_t *) b)->x;
}

/* Drop all dominoes in sequence and return amount dropped */
int drop_all(int x) {
    int queue[MAX_N], front, rear, total, i;
    if (dropped[x])
        return 0;
    queue[0] = x, front = 0, rear = 1;
    dropped[x] = 1, total = 1;
    while (front < rear) {
        x = queue[front++];
        for (i = start[x]; i < num_pairs && pair[i].x == x; i++)
            if (!dropped[pair[i].y])
                queue[rear++] = pair[i].y, dropped[pair[i].y] = 1, total++;
    }
    return total;
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) == 1);
    for (; num_tests > 0; num_tests--) {
        int i, j, total, num_manual;
        assert(scanf("%d %d %d", &num_dominoes, &num_pairs, 
                    &num_manual) == 3);
        for (i = 0; i < num_pairs; i++) {
            assert(scanf("%d %d", &pair[i].x, &pair[i].y) == 2);
            pair[i].x--, pair[i].y--;
        }
        qsort(pair, num_pairs, sizeof (pair_t), compare);
        for (i = j = 0; i < num_dominoes; i++) {
            dropped[i] = 0;
            start[i] = j;
            for (; j < num_pairs && pair[j].x <= i; j++)
                ;
        }
        for (total = 0; num_manual > 0; num_manual--) {
            assert(scanf("%d", &i) == 1);
            total += drop_all(i - 1);
        }
        printf("%d\n", total);
    }
    return EXIT_SUCCESS;
}
