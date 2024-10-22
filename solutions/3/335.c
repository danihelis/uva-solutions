/* 335
 * Processing MX Records
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING      40
#define MAX_ENTRIES     1000000
#define MAX_MACHINES    1000000
#define BLOCK           100

typedef struct {
    char name[MAX_STRING];
    int up;
} machine_t;

typedef struct {
    char domain[MAX_STRING];
    machine_t **machine;
    int *priority, allocated, num_machines;
} entry_t;

machine_t machine[MAX_MACHINES], *s_machine[MAX_MACHINES];
entry_t entry[MAX_ENTRIES], *s_entry[MAX_ENTRIES];
int num_machines, num_entries;

/* Find or insert machine */
machine_t * find_insert_machine(char *name, char insert) {
    int start = 0, end = num_machines;
    while (start < end) {
        int mid = (start + end) / 2;
        int comp = strcmp(s_machine[mid]->name, name);
        if (comp == 0)
            return s_machine[mid];
        else if (comp < 0)
            start = mid + 1;
        else
            end = mid;
    }
    if (!insert)
        return NULL;
    assert(num_machines < MAX_MACHINES);
    strcpy(machine[num_machines].name, name);
    machine[num_machines].up = 1;
    for (end = num_machines; end > start; end--)
        s_machine[end] = s_machine[end - 1];
    s_machine[start] = &machine[num_machines++];
    return s_machine[start];
}

/* Find or insert entry */
entry_t * find_insert_entry(char *name, char insert) {
    int start = 0, end = num_entries;
    while (start < end) {
        int mid = (start + end) / 2;
        int comp = strcmp(s_entry[mid]->domain, name);
        if (comp == 0)
            return s_entry[mid];
        else if (comp < 0)
            start = mid + 1;
        else
            end = mid;
    }
    if (!insert)
        return NULL;
    assert(num_entries < MAX_ENTRIES);
    strcpy(entry[num_entries].domain, name);
    entry[num_entries].num_machines = 0;
    entry[num_entries].machine = (machine_t **) 
            malloc(BLOCK * sizeof (machine_t *));
    entry[num_entries].priority = (int *) 
            malloc(BLOCK * sizeof (int));
    entry[num_entries].allocated = BLOCK;
    entry[num_entries].num_machines = 0;
    for (end = num_entries; end > start; end--)
        s_entry[end] = s_entry[end - 1];
    s_entry[start] = &entry[num_entries++];
    return s_entry[start];
}

/* Main function */
int main() {
    int i, k;
    char field[MAX_STRING], op;
    entry_t *last_entry;

    assert(scanf("%d", &k) == 1);
    for (num_machines = num_entries = 0, last_entry = NULL; k > 0; k--) {
        int is_number, p;
        char *c;
        machine_t *m;
        entry_t *e;
        assert(scanf(" %s", field) == 1);
        for (c = field, is_number = 1; is_number && *c != 0; c++)
            is_number = isdigit(*c);
        if (is_number)
            e = last_entry;
        else {
            p = field[0] == '*' ? 1 : 0;
            e = find_insert_entry(field + p, 1);
            assert(scanf(" %s", field) == 1);
        }
        p = atoi(field);
        assert(scanf(" %s", field) == 1);
        m = find_insert_machine(field, 1);
        if (e->allocated == e->num_machines) {
            e->allocated += BLOCK;
            e->machine = (machine_t **) realloc(e->machine, 
                    e->allocated * sizeof (machine_t *));
            e->priority = (int *) realloc(e->priority,
                    e->allocated * sizeof (int));
        }
        e->machine[e->num_machines] = m, e->priority[e->num_machines] = p;
        e->num_machines++;
        last_entry = e;
    }

    while (scanf(" %c %s", &op, field) == 2 && op != 'X') {
        if (op == 'A') {
            int priority = 1 << 30;
            machine_t *best = NULL;
            char *domain = field;
            while (domain != NULL) {
                entry_t *e = find_insert_entry(domain, 0);
                if (e != NULL)
                    for (i = 0; i < e->num_machines; i++)
                        if (e->priority[i] < priority &&
                                e->machine[i]->up)
                            best = e->machine[i], priority = e->priority[i];
                domain = strchr(domain + 1, '.');
            }
            printf("%s =>", field);
            (best != NULL ? printf(" %s\n", best->name) : printf("\n"));
        }
        else {
            machine_t *m = find_insert_machine(field, 0);
            if (m != NULL)
                m->up = op == 'U' ? 1 : 0;
        }
    }
    return EXIT_SUCCESS;
}
