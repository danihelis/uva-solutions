/* 739
 * Soundex Indexing
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_NAME 25
#define PADDING "         "
#define NUM_CODES 6

/* Main function */
int main() {
    char code[NUM_CODES][MAX_NAME] = {"BPFV", "CSKGJQXZ", "DT", "L", "MN", "R"};
    char name[MAX_NAME];
    char *letter;
    int i, last_code, num_digits;

    printf("%s%-25s%s\n", PADDING, "NAME", "SOUNDEX CODE");
    while (scanf("%s", name) != EOF) {
        printf("%s%-25s%c", PADDING, name, name[0]);
        num_digits = 0;
        last_code = -1;
        for (letter = name; *letter != 0 && num_digits < 3; letter++) {
            for (i = 0; strchr(code[i], *letter) == NULL && i < NUM_CODES; i++)
                ;
            if (i == NUM_CODES) {
                last_code = 0;
                continue;
            }
            else if (last_code == -1) {
                last_code = i + 1;
            }
            else if (i + 1 != last_code) {
                printf("%d", i + 1);
                last_code = i + 1;
                num_digits++;
            }
        }
        for (; num_digits < 3; num_digits++) {
            printf("0");
        }
        printf("\n");
    }
    printf("%s%s END OF OUTPUT\n", PADDING, PADDING);
    return 0;
}
