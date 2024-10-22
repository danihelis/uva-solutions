/* 159
 * Word Crosses
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  20
#define NUM_PAIRS   2
#define NUM_SPACE   3

#define MAX(x,y)    ((x) > (y) ? (x) : (y))

typedef char string_t[MAX_STRING];

typedef struct {
    string_t word[2];
    int cross[2], size[2];
} cross_t, *cross_p;

cross_t pair[NUM_PAIRS];

/* Read two words and define crossing point */
int read_words(int which) {
    cross_p p = &pair[which];
    char *w1, *w2;
    assert(scanf(" %s %s", p->word[0], p->word[1]) != EOF);
    if (p->word[0][0] == '#') {
        return -1;
    }
    for (w1 = p->word[0], p->cross[0] = 0; *w1 != 0; w1++, p->cross[0]++) {
        for (w2 = p->word[1], p->cross[1] = 0; *w2 != 0; w2++, p->cross[1]++) {
            if (*w1 == *w2) {
                p->size[0] = strlen(p->word[0]), p->size[1] = strlen(p->word[1]);
                return 1;
            }
        }
    }
    return 0;
}

/* Print space */
void print_space(int n) {
    for (; n > 0; n--) {
        printf(" ");
    }
}

/* Main function */
int main() {
    int possible, first = 1;
    while ((possible = read_words(0)) != -1) {
        (first ? (void) (first = 0) : (void) printf("\n"));
        possible = read_words(1) * possible;
        if (!possible) {
            printf("Unable to make two crosses\n");
        }
        else {
            int t, k, space, end;
            for (t = -MAX(pair[0].cross[1], pair[1].cross[1]), end = 0; !end; t++) {
                if (t == 0) {
                    printf("%s   %s\n", pair[0].word[0], pair[1].word[0]);
                    continue;
                }
                for (k = 0, space = 0, end = 1; k < NUM_PAIRS; k++) {
                    cross_p p = &pair[k];
                    int idx = p->cross[1] + t;
                    if (idx >= 0 && idx < p->size[1]) {
                        print_space(space + p->cross[0]);
                        printf("%c", p->word[1][idx]);
                        space -= p->cross[0] + 1;
                        end = 0;
                    }
                    space += p->size[0] + NUM_SPACE;
                }
                if (!end) {
                    printf("\n");
                }
            }
        }
    }
    return 0;
}
