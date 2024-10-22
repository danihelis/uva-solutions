/*
 * 168
 * Theseus and the Minotaur
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_NODES 26
typedef struct {
    int path[MAX_NODES];
    int number_paths;
    char lighted;
} cave_t;
cave_t cave[MAX_NODES];
int theseus, minotaur, k;


/* Utilities */
#define TO_NODE(c) ((c) - 'A')
#define TO_CHAR(i) ('A' + (i))
#define CONSUME_SPACE(s) \
    do { \
        assert(*(s++) == ' '); \
    } while(*s == ' ')


/* Iterate Theseus and Minotaur in the maze until the Minotaur is trapped */
void iterate() {
    int iteration = 0;
    for (;;) {
        /* Find a path for Minotaur */
        int next, p;
        for (next = -1, p = 0; next == -1 && p < cave[minotaur].number_paths; p++) {
            int way = cave[minotaur].path[p];
            if (way != theseus && !cave[way].lighted) {
                next = way;
            }
        }
        if (next == -1) {
            printf("/%c\n", TO_CHAR(minotaur));
            break;
        }

        /* Theseus follows him */
        theseus = minotaur;
        minotaur = next;
        iteration++;
        if (iteration % k == 0) {
            cave[theseus].lighted = 1;
            printf("%c ", TO_CHAR(theseus));
        }
    }
}


/* Read labyrinth */
void read_labyrinth(char *line) {
    char *p = line, end = 0;
    memset(cave, 0, MAX_NODES * sizeof(cave_t));
    while (!end) {
        int local = TO_NODE(*(p++));
        assert(*(p++) == ':');
        while (*p != ';' && *p != '.') {
            cave[local].path[cave[local].number_paths++] = TO_NODE(*(p++));
        }
        end = (*(p++) == '.');   
    }
    CONSUME_SPACE(p);
    minotaur = TO_NODE(*(p++));
    CONSUME_SPACE(p);
    theseus = TO_NODE(*(p++));
    CONSUME_SPACE(p);
    k = atoi(p);
}


/* Main function */
#define MAX_INPUT 1024
int main() {
    char input[1024];
    while (fgets(input, MAX_INPUT, stdin) != NULL) {
        if (input[0] == '#') {
            break;
        }
        read_labyrinth(input);
        iterate();
    }
    return 0;
}

