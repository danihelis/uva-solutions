/* 331
 * Mapping the Swaps
 * By Johan Schreiber
 */
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE        5
#define MAX_ENTRIES     1000
#define UNDEFINED       -1
#define INVALID         (1 << 30)

typedef struct entry_s {
    char value[MAX_SIZE + 2];
    struct entry_s *next[MAX_SIZE];
    int size, distance, paths;
} entry_t;

entry_t entries[MAX_ENTRIES];
entry_t *entries_dict[MAX_ENTRIES];
int num_entries;


/* Get or insert entry */
int get_or_insert(char *value, entry_t **ref) {
    int start = 0, end = num_entries;
    while (start < end) {
        int middle = (start + end) / 2;
        int cmp = strcmp(value, entries_dict[middle]->value);
        if (cmp == 0) {
            *ref = entries_dict[middle];
            return 1;
        } else if (cmp < 0) end = middle;
        else start = middle + 1;
    }

    *ref = &entries[num_entries++];
    strcpy((*ref)->value, value);
    (*ref)->distance = (*ref)->paths = UNDEFINED;
    (*ref)->size = strlen(value);

    for (end = num_entries; end > start; end--) {
        entries_dict[end] = entries_dict[end - 1];
    }
    entries_dict[start] = *ref;
    return 0;
}


/* Create all entries recursively after an initial seed */
entry_t * create_entries(char *value) {
    entry_t *e;

    if (get_or_insert(value, &e) == 0) {
        char *c, *n;
        int i;

        for (i = 0, c = value, n = value + 1; *n != 0; c++, n++, i++) {
            char bc = *c, bn = *n;
            *c = bn, *n = bc;
            e->next[i] = create_entries(value);
            *c = bc, *n = bn;
        }
    }
    return e;
}


/* Compute the distance between all nodes */
void compute_distances(entry_t *start) {
    entry_t *queue[MAX_ENTRIES];
    int i, j, front, rear;

    queue[0] = start, front = 0, rear = 1;
    start->distance = 0;

    while (front < rear) {
        entry_t *e = queue[front++];
        for (i = 0; i < e->size - 1; i++) {
            entry_t *n = e->next[i];
            if (n->distance == UNDEFINED) {
                n->distance = e->distance + 1;
                queue[rear++] = n;
            }
        }
    }

    start->paths = 1;
    for (i = 1; i < rear; i++) {
        entry_t *e = queue[i];
        e->paths = 0;
        for (j = 0; j < e->size - 1; j++) {
            entry_t *n = e->next[j];
            if (n->distance == e->distance - 1) e->paths += n->paths;
        }
    }
    start->paths = 0;
}


/* Create all entries */
void create_all_entries() {
    char value[MAX_SIZE + 2] = "1";
    int i;
    entry_t *start;

    num_entries = 0;
    for (i = 0; i < MAX_SIZE; i++) {
        value[i] = '1' + i;
        value[i + 1] = 0;

        start = create_entries(value);
        compute_distances(start);
    }
}


/* Compare integers */
int compare(const void *a, const void *b) {
    return  *((int *) a) - *((int *) b);
}


/* Convert vector into string position code */
void convert_positions(int vector[], int n, char *value) {
    int sorted[MAX_SIZE];
    int i, pos;

    for (i = 0; i < n; i++) {
        sorted[i] = vector[i];
    }
    qsort(sorted, n, sizeof (int), compare);

    for (i = 0; i < n; i++) {
        for (pos = 0; sorted[pos] != vector[i]; pos++)
            ;
        value[i] = '1' + pos;
        sorted[pos] = INVALID;
    }
    value[n] = 0;
}


/* Main function */
int main() {
    int test;
    int i, n, vector[MAX_SIZE];
    char value[MAX_SIZE + 2];
    entry_t *entry;

    create_all_entries();
    test = 0;

    while (scanf("%d", &n) == 1 && n > 0) {
        for (i = 0; i < n; i++) {
            assert(scanf("%d", &vector[i]) == 1);
        }
        convert_positions(vector, n, value);

        assert(get_or_insert(value, &entry) == 1);
        printf("There are %d swap maps for input data set %d.\n",
                entry->paths, ++test);
    }
    return EXIT_SUCCESS;
}
