/* 11045
 * My T-shirt suits me
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define NUM_TYPES       6
#define MAX_N           30
#define NUM_CHOICES     2
#define MAX_STRING      10

int choice[MAX_N][NUM_CHOICES];
int available[NUM_TYPES];
int num_people;

/* Return type code */
int get_type(char *type) {
    switch (type[0]) {
        case 'S': return 0;
        case 'M': return 1;
        case 'L': return 2;
        default:
            switch (type[1]) {
                case 'S': return 3;
                case 'L': return 4;
            }
            return 5;
    }
}

/* Whether there is a type available for all or not */
int fit_all(int i) {
    int k;
    if (i == num_people)
        return 1;
    for (k = 0; k < 2; k++) {
        int opt = choice[i][k];
        if (available[opt] > 0) {
            available[opt]--;
            if (fit_all(i + 1))
                return 1;
            available[opt]++;
        }
    }
    return 0;
}

/* Main function */
int main() {
    int num_shirts;
    assert(scanf("%*d") != EOF);
    while (scanf("%d %d", &num_shirts, &num_people) == 2) {
        int i, k;
        for (i = 0, num_shirts /= NUM_TYPES; i < NUM_TYPES; i++)
            available[i] = num_shirts;
        for (i = 0; i < num_people; i++)
            for (k = 0; k < 2; k++) {
                char code[MAX_STRING];
                assert(scanf(" %s", code) == 1);
                choice[i][k] = get_type(code);
            }
        puts(fit_all(0) ? "YES" : "NO");
    }
    return EXIT_SUCCESS;
}
