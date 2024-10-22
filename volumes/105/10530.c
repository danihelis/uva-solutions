/* 10530
 * Guessing Game
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING      20
#define MAX_NUMBERS     10

enum {
    ANY,
    HIGH,
    LOW,
    FALSE
} info, guess[MAX_NUMBERS];

/* Main function */
int main() {
    int n, i, honest;
    char answer[MAX_STRING];
    while (scanf("%d %[^\n]", &n, answer) != EOF && n > 0) {
        memset(guess, ANY, MAX_NUMBERS * sizeof(guess[0]));
        while (answer[0] != 'r') {
            n--, info = (answer[4] == 'h' ? HIGH : LOW);
            guess[n] = (guess[n] == ANY || guess[n] == info ? info : FALSE);
            assert(scanf("%d %[^\n]", &n, answer) != EOF);
        }
        for (honest = 1, i = 0; honest && i < MAX_NUMBERS; i++) {
            honest = guess[i] == ANY || (guess[i] == LOW && i < (n - 1)) || 
                (guess[i] == HIGH && i >= n);
        }
        printf("Stan %shonest\n", honest ? "may be " : "is dis");
    }
    return 0;
}
