/* 11369
 * Shopaholic
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_ITEMS       20000

/* Compare two integers */
int compare(const void *a, const void *b) {
    return *((int *) b) - *((int *) a);
}

/* Main function */
int main() {
    int item[MAX_ITEMS];
    int num_tests, num_items, i, total;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        assert(scanf("%d", &num_items) != EOF);
        for (i = 0; i < num_items; i++) {
            assert(scanf("%d", &item[i]) != EOF);
        }
        qsort(item, num_items, sizeof (int), compare);
        for (total = 0, i = 2; i < num_items; i += 3) {
            total += item[i];
        }
        printf("%d\n", total);
    }
    return 0;
}
