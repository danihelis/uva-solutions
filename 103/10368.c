/* 10368
 * Euclid's Game
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MIN(a,b)    ((a) < (b) ? (a) : (b))
#define MAX(a,b)    ((a) > (b) ? (a) : (b))

/* Get the winner. If the player has a choice, he is the winner. 
 * Otherwise, he must play a forced move and just hope for a win. */
int get_winner(long a, long b, int player) {
    if (a == b || a >= 2 * b) return player;
    return get_winner(b, a % b, 1 - player);
}

/* Main function */
int main() {
    long a, b;
    while (scanf("%ld %ld", &a, &b) == 2 && a > 0) {
        int p = get_winner(MAX(a, b), MIN(a, b), 0);
        printf("%s wins\n", p == 0 ? "Stan" : "Ollie");
    }
    return EXIT_SUCCESS;
}
