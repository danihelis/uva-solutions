/* 11056
 * Formula 1
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       100
#define MAX_NAME    25

typedef struct {
    char name[MAX_N], key[MAX_N];
    int min, sec, ms;
} pilot_t;

pilot_t pilot[MAX_N], *sorted[MAX_N];
int size;

/* Convert string to lowercase */
void string_to_lower(char *output, char *input) {
    for (; *input != 0; input++, output++)
        *output = tolower(*input);
}

/* Compare two pilots */
int compare(const void *a, const void *b) {
    pilot_t *x = * (pilot_t **) a, *y = * (pilot_t **) b;
    if (x->min != y->min)
        return x->min - y->min;
    if (x->sec != y->sec)
        return x->sec - y->sec;
    if (x->ms - y->ms)
        return x->ms - y->ms;
    return strcmp(x->key, y->key);
}

/* Main function */
int main() {
    while (scanf("%d", &size) != EOF) {
        int i;
        for (i = 0; i < size; i++) {
            pilot_t *p = &pilot[i];
            assert(scanf(" %s : %d min %d sec %d ms", p->name, &p->min,
                        &p->sec, &p->ms) != EOF);
            string_to_lower(p->key, p->name);
            sorted[i] = p;
        }
        qsort(sorted, size, sizeof (pilot_t *), compare);
        for (i = 0; i < size; i += 2) {
            printf("Row %d\n%s\n", (i / 2) + 1, sorted[i]->name);
            if (i + 1 < size)
                printf("%s\n", sorted[i + 1]->name);
        }
        printf("\n");
    }
    return EXIT_SUCCESS;
}
