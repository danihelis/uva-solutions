/* 10098
 * Generating Fast
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_ELEMENTS    10
#define MAX_STRING      (MAX_ELEMENTS + 2)

typedef struct {
    char content;
    int count;
} symbol_t;

symbol_t symbol[MAX_ELEMENTS];
char permutation[MAX_STRING];
int length, num_symbols;

/* Compare two characters */
int compare(const void *a, const void *b) {
    return * (char *) a - * (char *) b;
}

/* Generate permutations */
void generate_all(int index) {
    if (index == length) 
        printf("%s\n", permutation);
    else {
        int i;
        for (i = 0; i < num_symbols; i++)
            if (symbol[i].count > 0) {
                symbol[i].count--;
                permutation[index] = symbol[i].content;
                generate_all(index + 1);
                symbol[i].count++;
            }
    }
}

/* Main function */
int main() {
    int num_tests, i;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        char input[MAX_STRING];
        assert(scanf(" %s", input) != EOF);
        length = strlen(input);
        qsort(input, length, sizeof (char), compare);
        for (i = 0, num_symbols = 0; i < length; i++) {
            if (num_symbols == 0 || 
                    input[i] != symbol[num_symbols - 1].content) {
                symbol[num_symbols].content = input[i];
                symbol[num_symbols].count = 0;
                num_symbols++;
            }
            symbol[num_symbols - 1].count++;
        }
        permutation[length] = 0;
        generate_all(0);
        printf("\n");
    }
    return EXIT_SUCCESS;
}
