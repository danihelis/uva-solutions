/* 10226
 * Hardwood Species
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING 50
#define MAX_SPECIES 10000

typedef char string_t[MAX_STRING];

typedef struct {
    string_t name;
    int count;
} specie_t, *specie_p;

specie_t specie[MAX_SPECIES];
specie_p index[MAX_SPECIES];
int num_species;

/* Find a specie by name, and insert it if not found */
specie_p find(string_t *name) {
    int start, end;
    start = 0, end = num_species;
    while (start < end) {
        int middle, comp;
        middle = (start + end) / 2;
        comp = strcmp(index[middle]->name, *name);
        if (comp == 0) {
            return index[middle];
        }
        else if (comp < 0) {
            start = middle + 1;
        }
        else {
            end = middle;
        }
    }
    for (end = num_species; end > start; end--) {
        index[end] = index[end - 1];
    }
    strcpy(specie[num_species].name, *name);
    specie[num_species].count = 0;
    index[start] = &specie[num_species];
    num_species++;
    return index[start];
}

/* Main function */
int main() {
    int tests;
    string_t line;
    assert(fgets(line, MAX_STRING, stdin) != NULL);
    tests = atoi(line);
    assert(fgets(line, MAX_STRING, stdin) != NULL && *line == '\n');
    for (; tests > 0; tests--) {
        int i, count = 0;
        num_species = 0;
        while (fgets(line, MAX_STRING, stdin) != NULL && *line != '\n') {
            char *end = strchr(line, '\n');
            specie_p current;
            assert(end != NULL);
            *end = 0;
            current = find(&line);
            current->count++;
            count++;
        }
        for (i = 0; i < num_species; i++) {
            double ratio = index[i]->count / (double) count * 100.0;
            printf("%s %.4f\n", index[i]->name, ratio);
        }
        printf("%s", tests > 1 ? "\n" : "");
    }
    return 0;
}
