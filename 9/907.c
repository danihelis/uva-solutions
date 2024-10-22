/* 907
 * Winterim Backpacking Trip
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_LENGTH  601
#define MAX_STOPS   300
#define INFINITY    (1 << 30)
#define MIN(x,y)    ((x) < (y) ? (x) : (y))
#define MAX(x,y)    ((x) > (y) ? (x) : (y))

int distance[MAX_LENGTH];
int sum[MAX_LENGTH][MAX_LENGTH];
int table[MAX_STOPS][MAX_LENGTH];
int num_stops, length;

/* Pre-compute dynamic tables with default values */
void pre_compute_tables() {
    int start, end;
    for (start = 0; start < length; start++) {
        sum[start][start] = distance[start];
        for (end = start + 1; end < length; end++) 
            sum[start][end] = sum[start][end - 1] + distance[end];
        for (end = 0; end < num_stops; end++) {
            table[end][start] = -1;
        }
    }
}

/* Use DPS with memoization to find mininal trip with N stops */
int minimal_trip(int stops, int start) {
    int i, minimal, day, remain;
    if (stops == 0) 
        return sum[start][length - 1];
    if (table[stops - 1][start] != -1)
        return table[stops - 1][start];
    for (i = start, minimal = INFINITY; i < length - stops; i++) {
        day = sum[start][i];
        if (day >= minimal)
            break;
        remain = minimal_trip(stops - 1, i + 1);
        minimal = MIN(minimal, MAX(day, remain));
    }
    table[stops - 1][start] = minimal;
    return minimal;
}

/* Main function */
int main() {
    while (scanf("%d %d", &length, &num_stops) != EOF) {
        int i;
        for (i = 0, length++; i < length; i++) 
            assert(scanf("%d", &distance[i]) != EOF);
        pre_compute_tables();
        printf("%d\n", minimal_trip(num_stops, 0));
    }
    return EXIT_SUCCESS;
}
