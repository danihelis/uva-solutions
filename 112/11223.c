/* 11223
 * O: dah dah dah!
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_INPUT 2010
#define NUM_SYMBOLS 53
#define MAX_CODE 10

char symbol[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,?'!/()&:;=+-_\"@";
char morse[NUM_SYMBOLS][MAX_CODE] = {
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",
    ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.",
    "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", "-----",
    ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.",
    ".-.-.-", "--..--", "..--..", ".----.", "-.-.--", "-..-.", "-.--.", "-.--.-", ".-...",
    "---...", "-.-.-.", "-...-", ".-.-.", "-....-", "..--.-", ".-..-.", ".--.-."
};

/* Main function */
int main() {
    int message, tests;
    char line[MAX_INPUT];
    assert(scanf("%d", &tests) != EOF);
    for (message = 1; message <= tests; message++) {
        int index;
        char code[MAX_CODE], *entry;
        printf("%sMessage #%d\n", (message > 1 ? "\n" : ""), message);
        assert(scanf(" %[^\n]", line) != EOF);
        index = 0;
        for (entry = line; *entry != 0; entry++) {
            if (*entry == '.' || *entry == '-') {
                code[index++] = *entry;
            }
            else {
                assert(*entry == ' ');
                if (index == 0) {
                    printf(" ");
                }
                else {
                    code[index] = 0;
                    for (index = 0; strcmp(code, morse[index]) && index < NUM_SYMBOLS; index++)
                        ;
                    assert(index != NUM_SYMBOLS);
                    printf("%c", symbol[index]);
                    index = 0;
                }
            }
        }
        if (index > 0) {
            code[index] = 0;
            for (index = 0; strcmp(code, morse[index]) && index < NUM_SYMBOLS; index++)
                ;
            assert(index != NUM_SYMBOLS);
            printf("%c", symbol[index]);
            index = 0;
        }
        printf("\n");
    }
    return 0;
}
