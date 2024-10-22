/* 400
 * Unix ls
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING      70
#define MAX_WIDTH       60
#define MAX_N           100

char file[MAX_N][MAX_STRING], *sorted[MAX_N];
int num_files;

/* Compare files */
int compare(const void *a, const void *b) {
    return strcmp(* (char **) a, * (char **) b);
}

/* Print in order */
void ls(int width) {
    char format[MAX_STRING];
    int columns = (MAX_WIDTH + 2) / (width + 2);
    int rows = (num_files + columns - 1) / columns;
    int i, r, c, index;
    for (i = 0; i < MAX_WIDTH; i++)
        printf("-");
    sprintf(format, "%%s%%-%ds", width);
    for (r = 0; r < rows; r++)
        for (c = 0; c < columns; c++) {
            index = r + c * rows;
            if (index < num_files)
                printf(format, c == 0 ? "\n" : "  ", sorted[index]);
        }
    printf("\n");
}

/* Main function */
int main() {
    while (scanf("%d", &num_files) != EOF) {
        int i, width, len;
        for (i = width = 0; i < num_files; i++) {
            assert(scanf(" %s", file[i]) != EOF);
            sorted[i] = file[i];
            len = strlen(file[i]);
            if (len > width)
                width = len;
        }
        qsort(sorted, num_files, sizeof (char *), compare);
        ls(width);
    }
    return EXIT_SUCCESS;
}
