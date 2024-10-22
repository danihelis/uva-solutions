/* 941
 * Permutations
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING 25
#define MAX_FACTORIALS 20

long factorial[MAX_FACTORIALS];

/* Create a table of factorial numbers */
void create_factorial_table() {
    int i;
    factorial[0] = 1;
    for (i = 1; i < MAX_FACTORIALS; i++) {
        factorial[i] = factorial[i - 1] * i;
    }
}

/* Compare two characters in order to sort them */
int compare_char(const void *a, const void *b) {
    return *((char *) a) - *((char *) b);
}

/* Print permutation for a given set of characters */
void print_permutation(char *set, int max_set, long value) {
    long index, remain;
    if (max_set == 1) {
        printf("%c\n", set[0]);
        return;
    }
    qsort(set, max_set, sizeof (char), compare_char);
    max_set--;
    index = value / factorial[max_set];
    remain = value % factorial[max_set];
    assert(index <= max_set);
    printf("%c", set[index]);
    set[index] = set[max_set];
    print_permutation(set, max_set, remain);
}

/* Main function */
int main() {
    int tests;
    create_factorial_table();
    assert(scanf("%d", &tests) != EOF);
    for (; tests > 0; tests--) {
        char set[MAX_STRING];
        long index;
        assert(scanf(" %s %ld", set, &index) != EOF);
        print_permutation(set, strlen(set), index);
    }
    return 0;
}
