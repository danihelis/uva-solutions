/* 1610
 * Party Games
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  32
#define MAX_N       1000

char name[MAX_N][MAX_STRING], *dict[MAX_N];
int num_names;

/* Compare two string pointers */
int compare(const void *a, const void *b) {
    char *pa = *((char **) a), *pb = *((char **) b);
    return strcmp(pa, pb);
}

/* Main function */
int main() {
    while (scanf("%d", &num_names) != EOF && num_names > 0) {
        int i;
        char *a, *b;
        for (i = 0; i < num_names; i++) {
            assert(scanf(" %s", name[i]) != EOF);
            dict[i] = name[i];
        }
        qsort(dict, num_names, sizeof (char *), compare);
        a = dict[num_names / 2 - 1];
        b = dict[num_names / 2];
        for (; *a != 0 && *b != 0 && *a == *b; a++, b++) {
            printf("%c", *a);
        }
        if (*a != 0) {
            if (*(a + 1) == 0) printf("%c", *a);
            else if (*a + 1 == *b) {
                if (*(b + 1) != 0) printf("%c", *b);
                else {
                    printf("%c", *a);
                    for (a++; *a == 'Z'; a++) {
                        printf("Z");
                    }
                    if (*a != 0) printf("%c", *(a + 1) == 0 ? *a : *a + 1);
                }
            } else printf("%c", *a + 1);
        }
        printf("\n");
    }
    return EXIT_SUCCESS;
}
