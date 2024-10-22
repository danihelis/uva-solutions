/* 10420
 * List of Conquests
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_COUNTRIES 2010
#define MAX_NAME 80

typedef struct {
    char name[MAX_NAME];
    int count;
} country_t, *country_p;

country_t country[MAX_COUNTRIES];
int num_countries;

/* Return the country, if present, or insert a new country in the sorted vector */
country_p binary_search(char *name) {
    int start = 0, end = num_countries, middle;
    while (start < end) {
        int compare;
        middle = (start + end) / 2;
        compare = strcmp(country[middle].name, name);
        if (compare < 0) {
            start = middle + 1;
        }
        else if (compare > 0) {
            end = middle;
        }
        else {
            return &country[middle];
        }
    }
    for (end = num_countries; end > start; end--) {
        country[end] = country[end - 1];
    }
    strcpy(country[start].name, name);
    country[start].count = 0;
    num_countries++;
    return &country[start];
}

/* Main function */
int main() {
    int inputs, i;
    num_countries = 0;
    assert(scanf("%d", &inputs) != EOF);
    for (; inputs > 0; inputs--) {
        char name[MAX_NAME];
        country_p where;
        assert(scanf(" %s %*[^\n]", name) != EOF);
        where = binary_search(name);
        where->count++;
    }
    for (i = 0; i < num_countries; i++) {
        printf("%s %d\n", country[i].name, country[i].count);
    }
    return 0;
}
