/* 10895
 * Matrix Transpose
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIM     1000

typedef struct {
    int row, column, value;
} entry_t;

entry_t entry[MAX_DIM];
int size;

/* Compare two entries */
int compare(const void *a, const void *b) {
    entry_t *x = (entry_t *) a, *y = (entry_t *) b;
    if (x->row != y->row)
        return x->row - y->row;
    return x->column - y->column;
}

/* Main function */
int main() {
    int m, n;
    while (scanf("%d %d", &m, &n) != EOF) {
        int i, j, row;
        for (i = 0, size = 0; i < m; i++) {
            int num_cols, column[MAX_DIM];
            assert(scanf("%d", &num_cols) != EOF);
            for (j = 0; j < num_cols; j++) {
                assert(scanf("%d", &column[j]) != EOF);
            }
            for (j = 0; j < num_cols; j++) {
                entry_t e;
                assert(scanf("%d", &e.value) != EOF);
                e.row = column[j] - 1, e.column = i + 1;
                entry[size++] = e;
            }
        }
        qsort(entry, size, sizeof (entry_t), compare);
        printf("%d %d\n", n, m);
        for (row = 0, i = 0; row < n; row++) {
            for (j = i; j < size && entry[j].row == row; j++)
                ;
            printf("%d", j - i);
            for (j = i; j < size && entry[j].row == row; j++)
                printf(" %d", entry[j].column);
            printf("\n");
            for (j = i; i < size && entry[i].row == row; i++)
                printf("%s%d", i == j ? "" : " ", entry[i].value);
            printf("\n");
        }
    }
    return 0;
}
