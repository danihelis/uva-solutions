/* 154
 * Recycling
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING      1000
#define MAX_CITIES      100
#define MAX_BINS        5   
#define MAX_MATERIALS   5
#define BINS            "roygb"
#define MATERIALS       "PGSAN"

char bins[] = BINS, materials[] = MATERIALS;
int amount[MAX_BINS][MAX_MATERIALS];
int city[MAX_CITIES][MAX_BINS];

/* Main function */
int main() {
    char line[MAX_STRING];
    while (fgets(line, MAX_STRING, stdin) != NULL && line[0] != '#') {
        int i, best_index, best_diff, num_cities = 0;
        memset(amount, 0, MAX_BINS * MAX_MATERIALS * sizeof (int));
        do {
            char *start = line, *point;
            int bin, material;
            while (*start != 0) {
                point = strchr(bins, *start);
                assert(point != NULL);
                bin = (point - bins);
                start += 2;
                point = strchr(materials, *start);
                assert(point != NULL);
                material = (point - materials);
                amount[bin][material]++;
                city[num_cities][bin] = material;
                start += 2;
            }
            num_cities++;
            assert(fgets(line, MAX_STRING, stdin) != NULL);
        } while (line[0] != 'e');

        for (i = 0, best_index = -1, best_diff = 0; i < num_cities; i++) {
            int diff, j;
            for (j = 0, diff = 0; j < MAX_BINS; j++) {
                diff += num_cities - amount[j][city[i][j]];
            }
            if (best_index == -1 || diff < best_diff) {
                best_index = i;
                best_diff = diff;
            }
        }
        printf("%d\n", best_index + 1);
    }
    return 0;
}
