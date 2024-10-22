/* 12097
 * Pie
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       10000
#define ZERO(a,b)   (fabs(a - b) < 1e-4)

double PI;

double pie[MAX_N];
int num_pies;

/* Compare two doubles */
int compare(const void *a, const void *b) {
    return *((double *) a) < *((double *) b) ? 1 : -1;
}

/* Number of pieces using a given size */
int get_pieces(double area) {
    int i, pieces;
    for (i = 0, pieces = 0; i < num_pies; i++) {
        pieces += (int) floor(pie[i] / area);
    }
    return pieces;
}

/* Find biggest area that serves all friends */
double biggest_area(int friends) {
    double start = pie[0] / friends;
    double end = pie[0] / ((friends + num_pies - 1) / num_pies);
    while (!ZERO(start, end)) {
        double middle = (start + end) / 2;
        int pieces = get_pieces(middle);
        if (pieces < friends) end = middle;
        else start = middle;
    }
    return start;
}

/* Main function */
int main() {
    int num_tests;
    PI = atan(1) * 4;
    assert(scanf("%d", &num_tests) != EOF);
    while (num_tests-- > 0) {
        int i, radius, friends;
        assert(scanf("%d %d", &num_pies, &friends) != EOF);
        for (i = 0; i < num_pies; i++) {
            assert(scanf("%d", &radius) != EOF);
            pie[i] = radius * radius * PI;
        }
        qsort(pie, num_pies, sizeof (double), compare);
        printf("%.4f\n", biggest_area(friends + 1));
    }
    return EXIT_SUCCESS;
}
