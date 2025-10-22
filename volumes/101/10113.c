/* 10113
 * Exchange Rates
 * By Johan Schreiber
 */
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING      22
#define MAX_ENTRIES     60
#define PRINT_ENTRY(value, name, ending) do { \
        if (value == 0) printf("?"); \
        else printf("%ld", value); \
        printf(" %s%s", name, ending); \
    } while (0);

struct entry_s;

typedef struct {
    long given, taken;
} exchange_t;

typedef struct {
    struct entry_s *entry;
    exchange_t exchange;
} edge_t;

typedef struct entry_s {
    char name[MAX_STRING];
    edge_t edges[MAX_ENTRIES];
    int num_edges;
    char visited;
} entry_t;

const exchange_t ONE = {1, 1}, ZERO = {0, 0};

entry_t entries[MAX_ENTRIES];
entry_t *dictionary[MAX_ENTRIES];
int num_entries;


/* Simplify exchange values by their g.c.d. */
exchange_t simplify(exchange_t e) {
    long a = e.given, b = e.taken;
    if (a == 0 || b == 0) return e;
    while (b > 0) {
        long r = a % b;
        a = b;
        b = r;
    }
    e.given /= a, e.taken /= a;
    return e;
}


/* Get or add entry by name */
entry_t * get_or_add(char *name, char may_add) {
    int start = 0, end = num_entries;
    while (start < end) {
        int middle = (start + end) / 2;
        int cmp = strcmp(dictionary[middle]->name, name);
        if (cmp == 0) return dictionary[middle];
        else if (cmp < 0) start = middle + 1;
        else end = middle;
    }
    if (!may_add) return NULL;

    for (end = num_entries; end > start; end--) {
        dictionary[end] = dictionary[end - 1];
    }
    dictionary[start] = &entries[num_entries++];
    strcpy(dictionary[start]->name, name);
    dictionary[start]->num_edges = 0;
    return dictionary[start];
}


/* Find path from given to taken, and return correct exchange */
exchange_t find_exchange_path(entry_t *given, entry_t *taken) {
    int e;

    given->visited = 1;
    if (given == taken) return ONE;

    for (e = 0; e < given->num_edges; e++) {
        edge_t *edge = &given->edges[e];
        exchange_t x;
        if (edge->entry->visited) continue;
        x = find_exchange_path(edge->entry, taken);
        if (x.given && x.taken) {
            x.given *= edge->exchange.given;
            x.taken *= edge->exchange.taken;
            return simplify(x);
        }
    }
    return ZERO;
}


/* Get exchange from given to taken, calling method before */
exchange_t get_exchange(char *given_name, char *taken_name) {
    entry_t *given = get_or_add(given_name, 0);
    entry_t *taken = get_or_add(taken_name, 0);
    int i;
    if (!given || !taken) return ZERO;

    for (i = 0; i < num_entries; i++) {
        entries[i].visited = 0;
    }
    return find_exchange_path(given, taken);
}


/* Add exchange between two entries */
void add_exchange(char *given_name, char *taken_name, exchange_t exchange) {
    entry_t *given = get_or_add(given_name, 1);
    entry_t *taken = get_or_add(taken_name, 1);
    exchange_t x = simplify(exchange);
    edge_t *edge;

    edge = &given->edges[given->num_edges++];
    edge->entry = taken;
    edge->exchange = x;

    edge = &taken->edges[taken->num_edges++];
    edge->entry = given;
    edge->exchange.given = x.taken;
    edge->exchange.taken = x.given;
}


/* Main function */
int main() {
    char op;
    char given_name[MAX_STRING], taken_name[MAX_STRING];
    exchange_t exchange;

    num_entries = 0;
    while (scanf(" %c", &op) == 1 && op != '.') {
        if (op == '!') {
            assert(scanf("%ld %s = %ld %s", &exchange.given, given_name,
                &exchange.taken, taken_name) == 4);
            add_exchange(given_name, taken_name, exchange);
        } else {
            assert(op == '?');
            assert(scanf("%s = %s", given_name, taken_name) == 2);
            exchange = get_exchange(given_name, taken_name);
            PRINT_ENTRY(exchange.given, given_name, " = ");
            PRINT_ENTRY(exchange.taken, taken_name, "\n");
        }
    }
    return EXIT_SUCCESS;
}
