/**
 * 124
 * Following Orders
 * by Daniel Donadon
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define MAX_CHARS 26
#define MAX_LINE 1024
#define UNDEFINED -1

#define INDEX(c) ((c) - 'a')

typedef struct {
    char value;
    int precede[MAX_CHARS];
    int number_precedes;
} variable_t;

variable_t variable[MAX_CHARS];
int number_vars;
char used_variable[MAX_CHARS];
char solution[MAX_CHARS + 1];


/* Compare two characters */
int compare(const void *a, const void *b) {
    return ((variable_t *) a)->value - ((variable_t *) b)->value;
}


/* Print sequence of variables recursively */
void print_sequence(int i) {
    int k;

    /* Stop recursion when combination is complete */
    if (i >= number_vars) {
        printf("%s\n", solution);
        return;
    }

    /* Tries to use all variables */
    for (k = 0; k < number_vars; k++) {
        int p, index = INDEX(variable[k].value);
        int may_use = !used_variable[index];
        for (p = 0; may_use && p < variable[k].number_precedes; p++) {
            may_use = used_variable[variable[k].precede[p]];
        }
        if (may_use) {
            solution[i] = variable[k].value;
            used_variable[index] = 1;
            print_sequence(i + 1);
            used_variable[index] = 0;
        }
    }
}


/* Main */
#define READ_UNTIL_NEXT(c) while (*c != '\0' && !isalpha((int) *c)) c++
#define SKIP_AND_READ_NEXT(c) c++; READ_UNTIL_NEXT(c)

int main() {
    char line[MAX_LINE], *l_ptr;
    int first_input = 1;

    while (fgets(line, MAX_LINE, stdin) != NULL) {
        if (first_input) {
            first_input = 0;
        }
        else {
            printf("\n");
        }

        /* Initialization */
        memset(used_variable, 0, MAX_CHARS);
        number_vars = 0;

        /* Read variables */
        l_ptr = line;
        READ_UNTIL_NEXT(l_ptr);
        while (*l_ptr != '\0') {
            variable[number_vars].value = *l_ptr;
            variable[number_vars].number_precedes = 0;
            number_vars++;
            SKIP_AND_READ_NEXT(l_ptr);
        }
        qsort(variable, number_vars, sizeof (variable_t), compare);

        /* Read restrictions */
        l_ptr = fgets(line, MAX_LINE, stdin);
        READ_UNTIL_NEXT(l_ptr);
        while (*l_ptr != '\0') {
            variable_t *var, key;
            char precede = *l_ptr;
            SKIP_AND_READ_NEXT(l_ptr);
            key.value = *l_ptr;
            var = bsearch(&key, variable, number_vars, sizeof (variable_t), compare);
            assert(var != NULL);
            var->precede[var->number_precedes++] = INDEX(precede);
            SKIP_AND_READ_NEXT(l_ptr);
        }

        /* Print soluctions */
        solution[number_vars] = '\0';
        print_sequence(0);
    }
    return 0;
}

