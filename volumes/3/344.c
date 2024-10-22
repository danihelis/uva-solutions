/* 344
 * Roman Digititis
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define NUM_CHARACTERS  5
#define NUM_BASIC_CHAR  3
#define INDEX_HIGH      2
#define NUM_DIGITS      10
#define MAX_NUMBERS     101

typedef int roman_t[NUM_CHARACTERS];

int needed[NUM_DIGITS][NUM_BASIC_CHAR] = {
    {0, 0, 0},
    {1, 0, 0},
    {2, 0, 0},
    {3, 0, 0},
    {1, 1, 0},
    {0, 1, 0},
    {1, 1, 0},
    {2, 1, 0},
    {3, 1, 0},
    {1, 0, 1},
};
char letter[] = "ivxlc";
roman_t used[MAX_NUMBERS];
int last_defined;

/* Main function */
int main() {
    int i, n;
    last_defined = 1;
    memset(used[0], 0, NUM_CHARACTERS * sizeof (int));
    while (scanf("%d", &n) != EOF && n > 0) {
        for (; last_defined <= n; last_defined++) {
            int e = 0, k = last_defined;
            memcpy(used[last_defined], used[last_defined - 1], NUM_CHARACTERS * sizeof (int));
            while (k > 0) {
                int d = k % 10;
                for (i = 0; i < NUM_BASIC_CHAR && e + i < NUM_CHARACTERS; i++) {
                    used[last_defined][e + i] += needed[d][i];
                }
                e += 2;
                k /= 10;
            }            
        }
        printf("%d:", n);
        for (i = 0; i < NUM_CHARACTERS; i++) {
            printf(" %d %c%c", used[n][i], letter[i], (i < NUM_CHARACTERS - 1 ? ',' : '\n'));
        }
    }
    return 0;
}
