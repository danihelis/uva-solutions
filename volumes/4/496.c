/* 496
 * Simply Subsets
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_SIZE    100000

/* Read a set */
int read_set(int set[], int *size) {
    char symbol;
    *size = 0;
    symbol = getchar();
    while (!feof(stdin) && symbol != '\n') {
        int value = 0;
        while (symbol == ' ')
            symbol = getchar();
        if (isdigit(symbol)) {
            while (isdigit(symbol)) {
                value = value * 10 + symbol - '0';
                symbol = getchar();
            }
            set[(*size)++] = value;
        }
    }
    return *size > 0;
}

/* Compare elements */
int compare(const void *a, const void *b) {
    return * (int *) a - * (int *) b;
}

/* Main function */
int main() {
    int set_a[MAX_SIZE], set_b[MAX_SIZE];
    int size_a, size_b;
    while (read_set(set_a, &size_a)) {
        int *small, *big, s_size, b_size;
        int i, common;
        read_set(set_b, &size_b);
        if (size_a < size_b)
            small = set_a, big = set_b, s_size = size_a, b_size = size_b;
        else
            small = set_b, big = set_a, s_size = size_b, b_size = size_a;
        qsort(small, s_size, sizeof (int), compare);
        for (i = common = 0; i < b_size; i++)
            if (bsearch(&big[i], small, s_size, sizeof (int), compare) 
                    != NULL)
                common++;
        if (common == 0)
            puts("A and B are disjoint");
        else if (common == s_size) {
            if (s_size < b_size)
                printf("%c is a proper subset of %c\n", 
                        size_a < size_b ? 'A' : 'B', 
                        size_a < size_b ? 'B' : 'A');
            else
                puts("A equals B");
        }
        else
            puts("I'm confused!");
    }
    return EXIT_SUCCESS;
}
