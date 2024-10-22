/* 825
 * Walking on the Safe Side
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       10000
#define MAX_STRING  (MAX_N * 4)

char blocked[MAX_N][MAX_N];
int rows, cols;

/* Find all different paths to exit with minimum distance */
int find_all_paths() {
    int paths[MAX_N + 1], last[MAX_N + 1];
    int i, j;
    paths[cols] = 1;
    for (j = cols - 1; j >= 0; j--)
        paths[j] = blocked[rows - 1][j] ? 0 : paths[j + 1];
    paths[cols] = 0;
    for (i = rows - 2; i >= 0; i--) {
        memcpy(last, paths, sizeof (paths));
        for (j = cols - 1; j >= 0; j--)
            paths[j] = blocked[i][j] ? 0 : paths[j + 1] + last[j];
    }
    return paths[0];
}

/* Main function */
#define READ(x) (fgets(x, MAX_STRING, stdin) != NULL)
int main() {
    int num_tests;
    char input[MAX_STRING];
    assert(READ(input));
    num_tests = atoi(input);
    assert(READ(input) && input[0] == '\n');
    for (; num_tests > 0; num_tests--) {
        int i, j;
        char *s;

        assert(READ(input));
        assert(sscanf(input, "%d %d", &rows, &cols) == 2);
        for (i = 0; i < rows; i++)
            for (j = 0; j < cols; j++)
                blocked[i][j] = 0;
        while (READ(input) && input[0] != '\n') {
            s = strtok(input, " \n");
            i = atoi(s) - 1;
            for (s = strtok(NULL, " \n"); s != NULL; 
                    s = strtok(NULL, " \n")) {
                j = atoi(s) - 1;
                blocked[i][j] = 1;
            }
        }
        printf("%d\n%s", find_all_paths(), num_tests > 1 ? "\n" : "");
    }
    return EXIT_SUCCESS;
}
