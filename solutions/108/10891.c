/* 10891
 * Game of Sum
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_NUMBERS 100

typedef struct {
    int first, second;
} play_t, *play_p;

int number[MAX_NUMBERS];
int num_numbers;

/* Compute the maximum score difference from an optimum game play */
int optimum_play_difference() {
    play_t table[MAX_NUMBERS][MAX_NUMBERS];
    int i, j, k;
    for (i = 0; i < num_numbers; i++) {
        table[i][i].first = number[i];
        table[i][i].second = 0;
    }
    for (i = 1; i < num_numbers; i++) {
        for (j = i; j < num_numbers; j++) {
            int best_difference, sum, shift = j - i;
            play_p cell = &table[shift][j];
            for (k = 0, sum = 0; k < i; k++) {
                play_t result;
                sum += number[shift + k];
                result.first = sum + table[shift + k + 1][j].second;
                result.second = table[shift + k + 1][j].first;
                if (k == 0 || result.first - result.second > best_difference) {
                    *cell = result;
                    best_difference = result.first - result.second;
                }
            }
            sum += number[shift + k];
            if (sum > best_difference) {
                cell->first = sum;
                cell->second = 0;
                best_difference = sum;
            }
            for (k = i, sum = 0; k > 0; k--) {
                play_t result;
                sum += number[shift + k];
                result.first = sum + table[shift][shift + k - 1].second;
                result.second = table[shift][shift + k - 1].first;
                if (result.first - result.second > best_difference) {
                    *cell = result;
                    best_difference = result.first - result.second;
                }
            }
        }
    }
    return table[0][num_numbers - 1].first - table[0][num_numbers - 1].second;
}

/* Main function */
int main() {
    while (scanf("%d", &num_numbers) != EOF && num_numbers > 0) {
        int i;
        for (i = 0; i < num_numbers; i++) {
            assert(scanf("%d", &number[i]) != EOF);
        }
        printf("%d\n", optimum_play_difference());
    }
    return 0;
}
