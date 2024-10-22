/* 10131
 * Is Bigger Smarter?
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_ENTRIES     1000

typedef struct {
    int index, weight, smart, order;
} entry_t, *entry_p;

/* Compare two entries */
int compare(const void *a, const void *b) {
    entry_p x = (entry_p) a, y = (entry_p) b;
    return x->weight == y->weight ? x->smart - y->smart : x->weight - y->weight;
}

/* Main function */
int main() {
    entry_t entry[MAX_ENTRIES];
    int i, a, b, n, m, length[MAX_ENTRIES];
    for (n = 0; scanf("%d %d", &a, &b) != EOF; n++) {
        entry_p e = &entry[n];
        e->weight = a, e->smart = b, e->index = n + 1;
    }
    qsort(entry, n, sizeof (entry_t), compare);
    for (i = n - 1, m = 0; i >= 0; i--) {
        entry_p e = &entry[i];
        for (a = 0; a < m && e->smart > length[a]; a++)
            ;
        e->order = a;
        length[a] = e->smart;
        m = (a >= m ? a + 1 : m);
    }
    printf("%d\n", m);
    for (i = 0; i < n; i++) {
        entry_p e = &entry[i];
        if (e->order == m - 1) {
            printf("%d\n", e->index);
            m--;
        }
    }
    return 0;
}
