/* 10474
 * Where is the Marble?
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_MARBLES 10000

/* Compare two integers */
int compare_int(const void *a, const void *b) {
    return *((int *) a) - *((int *) b);
}

/* Main function */
int main() {
    int marble[MAX_MARBLES];
    int i, test = 0, num_marbles, num_queries;
    while (scanf("%d %d", &num_marbles, &num_queries) != EOF && (num_marbles || num_queries)) {
        for (i = 0; i < num_marbles; i++) {
            assert(scanf("%d", &marble[i]) != EOF);
        }
        qsort(marble, num_marbles, sizeof (int), compare_int);
        printf("CASE# %d:\n", ++test);
        for (i = 0; i < num_queries; i++) {
            int query, *pos;
            assert(scanf("%d", &query) != EOF);
            pos = bsearch(&query, marble, num_marbles, sizeof (int), compare_int);
            if (pos == NULL) {
                printf("%d not found\n", query);
            }
            else {
                while (pos > marble && *pos == *(pos - 1)) {
                    pos--;
                }
                printf("%d found at %d\n", query, (int) (pos - marble) + 1);
            }
        }
    }
    return 0;
}
