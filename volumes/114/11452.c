/* 11452
 * Dancing the Cheeky-Cheeky
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  2005
#define NUM_SEQ     8

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        char dance[MAX_STRING], *s1, *s2, *s3, *p1, *p2, *p3;
        int size, match, i;
        assert(scanf(" %s", dance) != EOF);
        s1 = s2 = s3 = p1 = p2 = p3 = NULL;
        for (size = strlen(dance) / 2, match = 0; 
                !match && size > 0; size--) {
            s1 = dance, s2 = dance + size, s3 = dance + 2 * size;
            for (i = 0, p1 = s1, p2 = s2, p3 = s3, match = 1; 
                    match && i < size; p1++, p2++, i++) {
                match = *p1 == *p2;
                if (*p3 != 0) {
                    match &= *p1 == *p3;
                    p3++;
                }
            }
        }
        for (i = 0, p1 = s1 + (p3 - s3); i < NUM_SEQ; i++, p1++) {
            if (p1 >= s2)
                p1 = s1;
            printf("%c", *p1);
        }
        printf("...\n");
    }
    return EXIT_SUCCESS;
}
