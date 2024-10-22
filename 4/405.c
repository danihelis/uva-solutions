/* 405
 * Message Routing
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_TABLES      10
#define MAX_ENTRIES     10
#define MAX_STRING      15
#define NUM_FIELDS      4

typedef struct {
    char name[MAX_STRING], field[NUM_FIELDS][MAX_STRING];
} entry_t;

typedef struct {
    char name[MAX_STRING];
    entry_t entry[MAX_ENTRIES];
    int num_entries, visited;
} table_t;

table_t table[MAX_TABLES];
int num_tables;

/* Perform routing */
void deliver(entry_t *message) {
    int i, k, acc;
    table_t *t, *n;
    for (i = 0, t = NULL; i < num_tables; i++) {
        table[i].visited = 0;
        if (strcmp(message->name, table[i].name) == 0)
            t = &table[i];
    }
    while (t != NULL) {
        if (t->visited) {
            printf("circular routing detected by %s\n", t->name);
            break;
        }
        t->visited = 1;
        for (i = 0, n = NULL; n == NULL && i < t->num_entries; i++) {
            entry_t *e = &t->entry[i];
            for (k = 0, acc = 1; acc && k < NUM_FIELDS; k++)
                acc = e->field[k][0] == '*' || 
                        strcmp(e->field[k], message->field[k]) == 0;
            if (acc)
                for (k = 0; k < num_tables; k++)
                    if (strcmp(table[k].name, e->name) == 0)
                        n = &table[k];
        }
        if (n == NULL)
            printf("unable to route at %s\n", t->name);
        else if (n == t) {
            printf("delivered to %s\n", t->name);
            break;
        }
        t = n;
    }
}

/* Main function */
int main() {
    int test = 0;
    while (scanf("%d", &num_tables) != EOF) {
        int i, j, k, queries;
        printf("Scenario # %d\n", ++test);
        for (i = 0; i < num_tables; i++) {
            table_t *t = &table[i];
            assert(scanf(" %s %d", t->name, &t->num_entries) == 2);
            for (j = 0; j < t->num_entries; j++) {
                entry_t *e = &t->entry[j];
                assert(scanf(" %s", e->name) == 1);
                for (k = 0; k < NUM_FIELDS; k++)
                    assert(scanf(" %s", e->field[k]) == 1);
            }
        }
        assert(scanf("%d", &queries) == 1);
        for (i = 1; i <= queries; i++) {
            entry_t m;
            assert(scanf(" %s", m.name) == 1);
            for (k = 0; k < NUM_FIELDS; k++)
                assert(scanf(" %s", m.field[k]) == 1);
            printf("%d -- ", i);
            deliver(&m);
        }
        printf("\n");
    }
    return EXIT_SUCCESS;
}
