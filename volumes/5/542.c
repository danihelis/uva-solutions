/* 542
 * France '98
 * By Johan Schreiber
 */
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME        20
#define MAX_STRING      200
#define NUM_COUNTRIES   16
#define NUM_MATCHES     4

typedef struct {
    double match[NUM_MATCHES + 1];
    double win[NUM_COUNTRIES];
    char name[MAX_NAME];
} country_t;

country_t countries[NUM_COUNTRIES];


/* Compute match probabilities for all countries */
void compute_probabilities() {
    int i, k, m;

    for (m = 0; m < NUM_MATCHES; m++) {
        int others = 1 << m;

        for (i = 0; i < NUM_COUNTRIES; i++) {
            country_t *ci = &countries[i];
            int prefix = i & (-1 << (m + 1));
            prefix |= (~(i >> m) & 1) << m;

            ci->match[m] = 0;

            for (k = 0; k < others; k++) {
                int j = prefix | k;
                country_t *cj = &countries[j];

                ci->match[m] += ci->win[j] * (m > 0 ? cj->match[m - 1] : 1);
            }
            if (m > 0) ci->match[m] *= ci->match[m - 1];
        }
    }
}

/* Main function */
int main() {
    int i, j;

    for (i = 0; i < NUM_COUNTRIES; i++) {
        country_t *c = &countries[i];
        assert(fgets(c->name, MAX_NAME, stdin) != NULL);
        c->name[strlen(c->name) - 1] = 0;
    }
    for (i = 0; i < NUM_COUNTRIES; i++) {
        country_t *c = &countries[i];
        char line[MAX_STRING], *s;

        assert(fgets(line, MAX_STRING, stdin) != NULL);
        for (j = 0, s = strtok(line, " "); j < NUM_COUNTRIES;
                j++, s = strtok(NULL, " ")) {
            assert(sscanf(s, "%lf", &c->win[j]) == 1);
            c->win[j] /= 100.0;
        }
    }

    compute_probabilities();

    for (i = 0; i < NUM_COUNTRIES; i++) {
        country_t *c = &countries[i];
        printf("%-10s p=%.2f%%\n", c->name, c->match[NUM_MATCHES - 1] * 100.0);
    }

    return EXIT_SUCCESS;
}
