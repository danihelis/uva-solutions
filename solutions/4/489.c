/* 489
 * Hangman Judge
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_LETTERS     26
#define MAX_WRONG       7
#define ORD(x)          ((x) - 'a')

/* Main function */
int main() {
    int round;
    while (scanf(" %d ", &round) != EOF && round != -1) {
        char letter, solution[MAX_LETTERS], guessed[MAX_LETTERS];
        int total = 0, correct = 0, wrong = 0, win = 0;
        memset(solution, 0, MAX_LETTERS);
        memset(guessed, 0, MAX_LETTERS);
        while (scanf("%c", &letter) != EOF && letter != '\n') {
            if (islower(letter)) {
                total += solution[ORD(letter)] ? 0 : 1;
                solution[ORD(letter)] = 1;
            }
        }
        while (scanf("%c", &letter) != EOF && letter != '\n') {
            if (islower(letter) && !guessed[ORD(letter)]) {
                (solution[ORD(letter)] ? correct++ : wrong++);
                guessed[ORD(letter)] = 1;
                if (win == 0) {
                    win = wrong >= MAX_WRONG ? -1 : correct >= total ? 1 : 0;
                }
            }
        }
        printf("Round %d\nYou %s.\n", round, win > 0 ? "win" : win < 0 ? "lose" : "chickened out");
    }
    return 0;
}
