/* 10050
 * Hartals
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_HARTALS     100

typedef struct {
    int day, interval;
} hartal_t;

hartal_t hartal[MAX_HARTALS];
int num_hartals;

#define SWAP(i, j)      do { \
        hartal_t swap = hartal[i]; \
        hartal[i] = hartal[j]; \
        hartal[j] = swap; \
    } while (0)

/* Ascend lowest heap element */
void heap_up() {
    int i = num_hartals - 1;
    int parent = (i - 1) / 2;
    while (i > 0 && hartal[i].day < hartal[parent].day) {
        SWAP(i, parent);
        i = parent;
        parent = (i - 1) / 2;
    }
}

/* Descend top heap element */
void heap_down() {
    int i = 0, child = 1;
    while ((child < num_hartals && hartal[i].day > hartal[child].day) ||
                (child + 1 < num_hartals && hartal[i].day > hartal[child + 1].day)) {
        if (child + 1 < num_hartals && hartal[child].day > hartal[child + 1].day) {
            child++;
        }
        SWAP(i, child);
        i = child;
        child = 2 * i + 1;
    }
}

#if 0
void print_heap() {
    int i;
    fprintf(stderr, "\nHEAP\n");
    for (i = 0; i < num_hartals; i++) {
        fprintf(stderr, "%d: D=%d  I=%d\n", i, hartal[i].day, hartal[i].interval);
    }
}
#endif


/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        int n, days, total;
        assert(scanf("%d %d", &days, &n) != EOF);
        for (num_hartals = 0; num_hartals < n; ) {
            assert(scanf("%d", &hartal[num_hartals].interval) != EOF);
            hartal[num_hartals].day = hartal[num_hartals].interval;
            num_hartals++;
            heap_up();
        }
        total = 0;
        while (hartal[0].day <= days) {
            int today = hartal[0].day;
            total += (today % 7 != 0 && (today + 1) % 7 != 0 ? 1 : 0);
            while (hartal[0].day == today) {
                hartal[0].day += hartal[0].interval;
                heap_down();
            }
        }
        printf("%d\n", total);
    }
    return 0;
}
