/* 11991
 * Easy Problem from Rujia Liu?
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_ELEMS   100001

typedef struct {
    int pos, value;
} elem_t;

elem_t elem[MAX_ELEMS], list[MAX_ELEMS];
int size, list_size;

/* Compare two elems */
int compare_elem(const void *a, const void *b) {
    elem_t *x = (elem_t *) a, *y = (elem_t *) b;
    if (x->value != y->value)
        return x->value - y->value;
    return x->pos - y->pos;
}

/* Compare two elem's values, ignoring pos */
int compare_value(const void *a, const void *b) {
    elem_t *x = (elem_t *) a, *y = (elem_t *) b;
    return x->value - y->value;
}


/* Main function */
int main() {
    int queries;
    while (scanf("%d %d", &size, &queries) != EOF) {
        int i;
        for (i = 0; i < size; i++) {
            assert(scanf("%d", &elem[i].value) != EOF);
            elem[i].pos = i + 1;
        }
        qsort(elem, size, sizeof (elem_t), compare_elem);
        list[0].value = elem[0].value, list[0].pos = 0;
        for (i = 1, list_size = 1; i < size; i++) {
            if (elem[i].value != list[list_size - 1].value) {
                list[list_size].value = elem[i].value;
                list[list_size].pos = i;
                list_size++;
            }
        }
        for (; queries > 0; queries--) {
            int k;
            elem_t key, *head;
            assert(scanf("%d %d", &k, &key.value) != EOF);
            head = bsearch(&key, list, list_size, sizeof (elem_t), 
                    compare_value);
            if (head == NULL)
                printf("0\n");
            else {
                k += head->pos - 1;
                printf("%d\n", k >= size || elem[k].value != key.value ? 0 :
                        elem[k].pos);
            }
        }
    }
    return 0;
}
