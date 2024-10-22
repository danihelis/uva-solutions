/* 11362
 * Phone List
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       10000
#define MAX_STRING  12
#define MIN(x, y)   ((x) < (y) ? (x) : (y))

typedef struct {
    char value[MAX_STRING];
    int len;
} number_t;

number_t number[MAX_N], *list[MAX_N];
int size;

/* Insert in the list, if is different */
int insert_different(char *value) {
    int start = 0, end = size, len = strlen(value);
    while (start < end) {
        int middle = (start + end) / 2;
        int comp = strncmp(value, list[middle]->value, 
                MIN(len, list[middle]->len));
        if (comp == 0)
            return 0;
        else if (comp < 0)
            end = middle;
        else
            start = middle + 1;
    }
    strcpy(number[size].value, value);
    number[size].len = len;
    for (end = size; end > start; end--)
        list[end] = list[end - 1];
    list[start] = &number[size++];
    return 1;
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) == 1);
    for (; num_tests > 0; num_tests--) {
        int n, consistent;
        assert(scanf("%d", &n) == 1);
        for (consistent = 1, size = 0; n > 0; n--) {
            char number[MAX_STRING];
            assert(scanf(" %s", number) == 1);
            if (consistent)
                consistent = insert_different(number);
        }
        printf("%s\n", consistent ? "YES" : "NO");
    }
    return EXIT_SUCCESS;
}
