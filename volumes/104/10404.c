/* 10404
 * Bachet's Game
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N           1000000
#define MAX_CHOICES     10

char win[MAX_N + 1];
int choice[MAX_CHOICES], num_choices;

/* Compare integers */
int compare(const void *a, const void *b) {
    return * (int *) a - * (int *) b;
}

/* Fill table with win possibilities */
char fill_table(int n) {
    int i, k;
    char can_lose;
    win[0] = 0;
    for (i = 1; i <= n; i++) {
        can_lose = 1;
        for (k = 0; can_lose && k < num_choices && choice[k] <= i; k++)
            can_lose &= win[i - choice[k]] == 1;
        win[i] = !can_lose;
    }
    return win[n];
}

/* Main function */
int main() {
    int i, n;
    while (scanf("%d %d", &n, &num_choices) != EOF) {
        for (i = 0; i < num_choices; i++)
            assert(scanf("%d", &choice[i]) == 1);
        qsort(choice, num_choices, sizeof (int), compare);
        printf("%s wins\n", fill_table(n) ? "Stan" : "Ollie");
    }
    return EXIT_SUCCESS;
}
