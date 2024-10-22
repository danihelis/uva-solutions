/**
 * 115
 * Climbing Trees
 * by Daniel Donadon
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAMES    300
#define LONGEST_NAME 35

#define NO_RELATION  -1
#define NON_EXISTENT -1

typedef struct {
    int ancestor[MAX_NAMES];
    int num_ancestors;
    int children[MAX_NAMES];
    int num_children;
} person_t;

typedef struct {
    char name[LONGEST_NAME];
    int index;
} name_t;

person_t person[MAX_NAMES];
name_t list[MAX_NAMES];
int num_people;


/* Compare two names */
int compare_name(const void *a, const void *b) {
    return strcmp(((name_t *) a)->name, ((name_t *) b)->name);
}


/* Insert new name on list */
int get_or_insert_name(char *name, int insert) {
    int max, min, pos;
    max = num_people - 1;
    min = 0;
    while (max >= min) {
        int cmp;
        pos = (max + min) / 2;
        cmp = strcmp(name, list[pos].name);
        if (cmp == 0) {
            return pos;
        }
        else if (strcmp(name, list[pos].name) < 0) {
            max = pos - 1;
        }
        else {
            min = pos + 1;
        }
    }

    if (!insert) {
        return NON_EXISTENT;
    }

    /* (max + 1) is the place for insertion */
    for (pos = num_people - 1; pos > max; pos--) {
        list[pos + 1] = list[pos];
    }
    strcpy(list[max + 1].name, name);
    list[max + 1].index = num_people++;
    return max + 1;
}


/* Obtain a person, if existent, or insert it */
int obtain_person(char *name) {
    int num_peolpe_before = num_people;
    int name_pos = get_or_insert_name(name, 1);
    if (num_people > num_peolpe_before) {
        person[num_people - 1].num_ancestors = 0;
        person[num_people - 1].num_children = 0;
    }
    return list[name_pos].index;
}


/* Get a person */
int get_person(char *name) {
    int name_pos = get_or_insert_name(name, 0);
    return (name_pos != NON_EXISTENT ? list[name_pos].index : NON_EXISTENT);
}


/* Insert a new relation child-parent */
void insert_relation(char *child, char *parent) {
    int i, child_idx, parent_idx;
    int queue[MAX_NAMES], q, queue_size;
    child_idx = obtain_person(child);
    parent_idx = obtain_person(parent);

    /* Set new child */
    person[parent_idx].children[person[parent_idx].num_children++] = child_idx;

    /* Set new parent and its ascendency */
    person[child_idx].ancestor[0] = parent_idx;
    for (i = 0; i < person[parent_idx].num_ancestors; i++) {
        person[child_idx].ancestor[i + 1] = person[parent_idx].ancestor[i];
    }
    person[child_idx].num_ancestors = person[parent_idx].num_ancestors + 1;

    /* Update the ancestor information for all child's descendency */
    for (i = 0; i < person[child_idx].num_children; i++) {
        queue[i] = person[child_idx].children[i];
    }
    queue_size = person[child_idx].num_children;
    for (q = 0; q < queue_size; q++) {
        /* Update ancestor information */
        person_t *descendent = &person[queue[q]];
        for (i = 0; i < person[child_idx].num_ancestors; i++) {
            descendent->ancestor[descendent->num_ancestors++] = person[child_idx].ancestor[i];
        }
        /* Put all children of the descendent into the queue */
        for (i = 0; i < descendent->num_children; i++) {
            queue[queue_size++] = descendent->children[i];
        }
    }
}


/* Return the ascestor generation of a person in relation to another */
int get_ancestor_generation(int fellow, int ancestor) {
    int i;
    for (i = 0; i < person[fellow].num_ancestors; i++) {
        if (person[fellow].ancestor[i] == ancestor) {
            return i;
        }
    }
    return NO_RELATION;
}


/* Get closest cousin relation, returning the common ancestor */
int get_cousin_relation(int a, int b, int *a_dist, int *b_dist) {
    int i;
    for (i = 0; i < person[a].num_ancestors; i++) {
        int gen = get_ancestor_generation(b, person[a].ancestor[i]);
        if (gen != NO_RELATION) {
            *a_dist = i;
            *b_dist = gen;
            return person[a].ancestor[i];
        }
    }
    return NON_EXISTENT;
}


/* Print relation between two people */
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define ABS(x, y) ((x) > (y) ? (x) - (y) : (y) - (x))
void print_relation(char *a_name, char *b_name) {
    int a, b, i, m, n;
    int is_there_relation = 0;
    a = get_person(a_name);
    b = get_person(b_name);
    if (a != NON_EXISTENT || b != NON_EXISTENT) {
        /* Is child or parent? */
        m = get_ancestor_generation(a, b);
        n = get_ancestor_generation(b, a);
        if (m != NO_RELATION || n != NO_RELATION) {
            is_there_relation = 1;
            for (i = 1; i < MAX(m, n); i++) {
                printf("great ");
            }
            if (MAX(m, n) > 0) {
                printf("grand ");
            }
            printf(m != NO_RELATION ? "child" : "parent");
        }
        /* Is cousin in any degree? */
        else {
            i = get_cousin_relation(a, b, &m, &n);
            if (i != NON_EXISTENT) {
                is_there_relation = 1;
                if (m == 0 && n == 0) {
                    printf("sibling");
                }
                else {
                    char cousin[100];
                    char removed[50];
                    sprintf(removed, " removed %d", ABS(m, n));
                    sprintf(cousin, "%d cousin%s", MIN(m, n), (ABS(m, n) == 0 ? "" : removed));
                    printf(cousin);
                }
            }
        }
    }
    if (!is_there_relation) {
        printf("no relation");
    }
    printf("\n");
    return;
}


/* Main */
int main() {
    char first[LONGEST_NAME], second[LONGEST_NAME];
    int no_more_relations = 0;

    /* Read relations */
    num_people = 0;
    while (!no_more_relations) {
        scanf("%s %s", first, second);
        if (strcmp(first, "no.child") == 0) {
            no_more_relations = 1;
        }
        else {
            insert_relation(first, second);
        }
    }

    /* Read queries */
    while (scanf("%s %s", first, second) == 2) {
        print_relation(first, second);
    }
    return 0;
}

