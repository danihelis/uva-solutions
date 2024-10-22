/* 119
 * Greedy Gift Givers
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_NAME    15
#define MAX_GROUP   20
#define MAX_STRING  300
#define READ(x)     (fgets(x, MAX_STRING, stdin) != NULL)
#define SPACE       " \t\n"
#define NEXT()      strtok(NULL, SPACE)

typedef struct {
    char name[MAX_NAME];
    int profit;
} person_t, *person_p;

person_t person[MAX_GROUP];
person_p index[MAX_GROUP], order[MAX_GROUP];
int num_people;

/* Find a person or insert a new person in the group */
person_p find(char *name) {
    int start = 0, end = num_people;
    while (start < end) {
        int middle = (start + end) / 2;
        int cmp = strcmp(index[middle]->name, name);
        if (cmp == 0) {
            return index[middle];
        }
        else if (cmp < 0) {
            start = middle + 1;
        }
        else {
            end = middle;
        }
    }
    for (end = num_people; end > start; end--) {
        index[end] = index[end - 1];
    }
    strcpy(person[num_people].name, name);
    person[num_people].profit = 0;
    index[start] = &person[num_people];
    num_people++;
    return index[start];
}

/* Main function */
int main() {
    int first = 1;
    char line[MAX_STRING], *p;
    while (READ(line)) {
        int i, n, total, value;
        person_p key;
        assert(sscanf(line, "%d", &n) == 1 && READ(line));
        for (num_people = 0, p = strtok(line, SPACE); p != NULL; p = NEXT()) {
            i = num_people;
            order[i] = find(p);
        }
        assert(n == num_people);
        for (i = 0; i < num_people; i++) {
            assert(READ(line));
            p = strtok(line, SPACE);
            key = find(p);
            assert((p = NEXT()) != NULL);
            total = atoi(p);
            assert((p = NEXT()) != NULL);
            n = atoi(p);
            value = (n > 0 ? total / n : 0);
            key->profit -= value * n;
            for (p = NEXT(); p != NULL; p = NEXT()) {
                person_p whom = find(p);
                whom->profit += value;
            }
        }
        (first ? (first = 0) : printf("\n"));
        for (i = 0; i < num_people; i++) {
            printf("%s %d\n", order[i]->name, order[i]->profit);
        }
    }
    return 0;
}
