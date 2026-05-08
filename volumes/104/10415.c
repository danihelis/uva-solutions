/* 10415
 * Eb Alto Saxophone Player
 * By Johan Schreiber
 */
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_BUTTONS     14
#define NUM_FINGERS     10

#define MAX_STRING      202
#define READ(x)         (fgets(x, MAX_STRING, stdin) != NULL)

char buttons[NUM_BUTTONS + 2] = "cdefgabCDEFGAB";
char fingers[NUM_BUTTONS][NUM_FINGERS + 2] = {
    "0111001111", /* c */
    "0111001110", /* d */
    "0111001100", /* e */
    "0111001000", /* f */
    "0111000000", /* g */
    "0110000000", /* a */
    "0100000000", /* b */
    "0010000000", /* C */
    "1111001110", /* D */
    "1111001100", /* E */
    "1111001000", /* F */
    "1111000000", /* G */
    "1110000000", /* A */
    "1100000000", /* B */
};

/* Count and print the number of pressed buttons */
void count_and_print(char *sequence) {
    int count[NUM_BUTTONS];
    char pressed[NUM_FINGERS];
    char *s, *c;
    int i, j;

    memset(count, 0, sizeof (int) * NUM_BUTTONS);
    memset(pressed, 0, sizeof (char) * NUM_FINGERS);

    for (s = sequence; *s != '\n'; s++) {
        for (i = 0, c = buttons; *c != *s; i++, c++)
            ;
        for (j = 0, c = fingers[i]; *c != 0; j++, c++) {
            if (*c == '1') {
                count[j] += pressed[j] ? 0 : 1;
                pressed[j] = 1;
            } else {
                pressed[j] = 0;
            }
        }
    }

    for (i = 0; i < NUM_FINGERS; i++) {
        printf("%d%c", count[i], i == NUM_FINGERS - 1 ? '\n' : ' ');
    }
}

/* Main function */
int main() {
    int num_tests;
    char input[MAX_STRING];

    assert(READ(input));
    assert(sscanf(input, "%d", &num_tests) == 1);

    while (num_tests-- > 0) {
        assert(READ(input));
        count_and_print(input);
    }
    return EXIT_SUCCESS;
}
