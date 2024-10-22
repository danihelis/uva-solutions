/* 10706
 * Number Sequence
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_TABLE   31268

unsigned int start[MAX_TABLE];
unsigned int position[MAX_TABLE];

/* Create starting points */
void create_starts() {
    unsigned int i, len = 0, inc = 0, inv = 1;
    start[0] = position[0] = 1;
    for (i = 1; i < MAX_TABLE; i++) {
        if (i == inv)
            inc++, inv *= 10;
        len += inc;
        position[i] = position[i - 1] + inc;
        start[i] = start[i - 1] + len;
    }
}

/* Find sequence */
int find_sequence(unsigned int table[], unsigned int pos) {
    int start = 0, end = MAX_TABLE;
    while (start < end) {
        int middle = (start + end) / 2;
        if (table[middle] == pos)
            return middle + 1;
        else if (table[middle] < pos)
            start = middle + 1;
        else
            end = middle;
    }
    return start;
}

/* Find pos-th digit in sequence */
char decode(unsigned int pos) {
    char string[20];
    int seq, index, value, sk;
    seq = find_sequence(start, pos);
    index = pos - start[seq - 1] + 1;
    value = find_sequence(position, index);
    sk = index - position[value - 1];
    sprintf(string, "%d", value);
    return string[sk];
}

/* Main function */
int main() {
    int num_tests;
    create_starts();
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        unsigned int pos;
        assert(scanf("%u", &pos) == 1);
        printf("%c\n", decode(pos));
    }
    return EXIT_SUCCESS;
}
