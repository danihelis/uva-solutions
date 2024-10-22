/* 10528
 * Major Scales
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define SCALE_SIZE 12
#define TONE_SIZE 4
#define EXCLUDED_TONE_SIZE 5
#define MAX_LINE 1100

char tone[SCALE_SIZE][TONE_SIZE] = {
    "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
int skip[EXCLUDED_TONE_SIZE] = {1, 2, 3, 2, 2};
int major[SCALE_SIZE][EXCLUDED_TONE_SIZE];
int set[SCALE_SIZE];
int set_size;

/* Create table of notes not included in the major scales */
void create_major_scales() {
    int i, j;
    for (i = 0; i < SCALE_SIZE; i++) {
        int index = i;
        for (j = 0; j < EXCLUDED_TONE_SIZE; j++) {
            index = (index + skip[j]) % SCALE_SIZE;
            major[i][j] = index;
        }
    }
}

/* Create set containing all tones */
void create_tone_set() {
    int i;
    for (i = 0; i < SCALE_SIZE; i++) {
        set[i] = i;
    }
    set_size = SCALE_SIZE;
}

/* Exclude all major scales that contain the given tone symbol */
void exclude_majors(char symbol, int sharp) {
    int i = 0;
    while (i < set_size) {
        int j, code, remove = 0;
        switch (symbol) {
            case 'C': code = 0; break;
            case 'D': code = 2; break;
            case 'E': code = 4; break;
            case 'F': code = 5; break;
            case 'G': code = 7; break;
            case 'A': code = 9; break;
            case 'B': code = 11; break;
            default: code = SCALE_SIZE;
        }
        code += (sharp ? 1 : 0);
        for (j = 0; !remove && j < EXCLUDED_TONE_SIZE; j++) {
            remove = (major[set[i]][j] == code);
        }
        if (remove) {
            set[i] = set[set_size - 1];
            set_size--;
        }
        else {
            i++;
        }
    }
}

/* Compare two integres in order to sort them */
int compare_int(const void *a, const void *b) {
    return *((int *) a) - *((int *) b);
}

/* Main function */
int main() {
    char line[MAX_LINE];
    create_major_scales();
    while (fgets(line, MAX_LINE, stdin) != NULL) {
        char *symbol;
        int i, sharp;
        if (strncmp(line, "END", 3) == 0) {
            break;
        }
        create_tone_set();
        symbol = line;
        while (*symbol != 0) {
            assert(isgraph(*symbol));
            sharp = (symbol[1] == '#');
            exclude_majors(*symbol, sharp);
            symbol += 1 + (sharp ? 1 : 0);
            while (isspace(*symbol)) {
                symbol++;
            }
        }
        qsort(set, set_size, sizeof (int), compare_int);
        for (i = 0; i < set_size; i++) {
            printf("%s%s", (i > 0 ? " " : ""), tone[set[i]]);
        }
        printf("\n");
    }
    return 0;
}
