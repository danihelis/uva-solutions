/* 10800
 * Not That Kind of Graph
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_LINES   50
#define MAX_STRING  (MAX_LINES + 2)

#define MIN(x,y)    ((x) < (y) ? (x) : (y))
#define MAX(x,y)    ((x) > (y) ? (x) : (y))

/* Main function */
int main() {
    int test, num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (test = 0; test < num_tests; test++) {
        char data[MAX_STRING], graph[MAX_LINES][MAX_STRING];
        int i, used, lowest, highest, line, top, column, height, width;
        char *p;
        assert(scanf(" %s", data) != EOF);
        lowest = 1, highest = -1;
        for (p = data, line = top = 0; *p != 0; p++) {
            if (*p == 'R') {
                if (!top) 
                    top = 1;
                else
                    line++;
            }
            else if (*p == 'C') {
                if (top) 
                    line++, top = 0;
            }
            else {
                if (top)
                    top = 0;
                else 
                    line--;
            }
            highest = MAX(line, highest);
            lowest = MIN(line, lowest);
        }
        width = p - data;
        height = highest - lowest + 1;
        for (i = 0; i < height; i++)
            memset(graph[i], 0, (width + 1) * sizeof (char));
        for (p = data, line = 0 - lowest, column = top = 0; 
                *p != 0; p++, column++) {
            if (*p == 'R') {
                if (!top) 
                    top = 1;
                else
                    line++;
                graph[line][column] = '/';
            }
            else if (*p == 'C') {
                if (top)
                    line++, top = 0;
                graph[line][column] = '_';
            }
            else {
                if (top)
                    top = 0;
                else 
                    line--;
                graph[line][column] = '\\';
            }
        }
        for (i = 0; i < height; i++) {
            for (p = graph[i] + width - 1, used = 0; p >= graph[i]; p--) {
                used |= *p != 0;
                if (*p == 0 && used)
                    *p = ' ';
            }
        }
        printf("Case #%d:\n", test + 1);
        for (i = height - 1; i >= 0; i--)
            printf("| %s\n", graph[i]);
        printf("+");
        for (i = 0; i < width + 2; i++)
            printf("-");
        printf("\n\n");
    }

    return EXIT_SUCCESS;
}
