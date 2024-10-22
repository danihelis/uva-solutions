/* 10567
 * Helping Fill Bates
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_CHARS       52
#define MAX_N           1000000
#define MAX_STRING      110
#define INDEX(c)        (islower(c) ? (c) - 'a' : 26 + (c) - 'A')

int pos[MAX_CHARS][MAX_N], count[MAX_CHARS], idx[MAX_CHARS];

/* Main function */
int main() {
    int i, n;
    char symbol;
    memset(count, 0, MAX_CHARS * sizeof (int));
    for (i = 0; scanf("%c", &symbol) != EOF && isalpha(symbol); i++) {
        int index = INDEX(symbol);
        pos[index][count[index]++] = i;
    }
    assert(scanf("%d", &n) != EOF);
    for (; n > 0; n--) {
        int start, place;
        char string[MAX_STRING], *c;
        assert(scanf(" %s", string) != EOF);
        memset(idx, 0, MAX_CHARS * sizeof (int));
        for (c = string, place = start = -1; *c != 0; c++) {
            int index = INDEX(*c);
            while (idx[index] < count[index] && 
                    pos[index][idx[index]] <= place)
                idx[index]++;
            if (idx[index] >= count[index])
                break;
            place = pos[index][idx[index]];
            if (start == -1)
                start = place;
        }
        if (*c != 0)
            printf("Not matched\n");
        else
            printf("Matched %d %d\n", start, place);
    }
    return EXIT_SUCCESS;
}
