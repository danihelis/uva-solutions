/* 544
 * Heavy Cargo
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       200
#define MAX_STRING  35
#define MAX_EDGES   20000

typedef struct {
    char name[MAX_STRING];
    int code;
} city_t;

typedef struct {
    int a, b, weight;
} edge_t;

typedef void *set_t;

city_t city[MAX_N], *dict[MAX_N];
edge_t edge[MAX_EDGES];
int num_cities, num_edges;

/* Compare edges */
int compare(const void *a, const void *b) {
    return ((edge_t *) b)->weight - ((edge_t *) a)->weight;
}

/* Get set */
set_t get_set(set_t *s) {
    if (*s != s)
        *s = get_set(*s);
    return *s;
}

/* Join sets */
void join_sets(set_t *a, set_t *b) {
    set_t *head = get_set(a);
    *head = get_set(b);
}

/* Find or insert city */
int find_or_insert(char *name) {
    int start = 0, end = num_cities;
    while (start < end) {
        int middle = (start + end) / 2;
        int cmp = strcmp(name, dict[middle]->name);
        if (cmp == 0)
            return dict[middle]->code;
        else if (cmp < 0)
            end = middle;
        else
            start = middle + 1;
    }
    strcpy(city[num_cities].name, name);
    city[num_cities].code = num_cities;
    for (end = num_cities; end > start; end--)
        dict[end] = dict[end - 1];
    dict[start] = &city[num_cities++];
    return num_cities - 1;
}

/* Find largest weight using MST */
int find_largest_weight(int source, int destiny) {
    set_t set[MAX_N];
    int i;
    qsort(edge, num_edges, sizeof (edge_t), compare);
    for (i = 0; i < num_cities; i++)
        set[i] = &set[i];
    for (i = 0; i < num_edges; i++) {
        edge_t *e = &edge[i];
        join_sets(&set[e->a], &set[e->b]);
        if (get_set(&set[source]) == get_set(&set[destiny]))
            return e->weight;
    }
    return 0;
}

/* Main function */
int main() {
    int testcase = 0;
    while (scanf("%*d %d", &num_edges) == 1 && num_edges > 0) {
        char name[MAX_STRING];
        int i, j;
        num_cities = 0;
        for (i = 0; i < num_edges; i++) {
            edge_t *e = &edge[i];
            assert(scanf(" %s", name) == 1);
            e->a = find_or_insert(name);
            assert(scanf(" %s %d", name, &e->weight) == 2);
            e->b = find_or_insert(name);            
        }
        assert(scanf(" %s", name) == 1);
        i = find_or_insert(name);
        assert(scanf(" %s", name) == 1);
        j = find_or_insert(name);
        printf("Scenario #%d\n%d tons\n\n", ++testcase,
                find_largest_weight(i, j));
    }
    return EXIT_SUCCESS;
}
