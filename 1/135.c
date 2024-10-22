/**
 * 135
 * No Rectangles
 * by Daniel Donadon
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_K 32
#define MAX_N (MAX_K * MAX_K)

int row[MAX_N][MAX_K];
int k, n;

/* Determine points of intersection and print */
void print_intersection_points() {
    int i, j, z;

    /* First lines */
    z = 1;
    for (i = 0; i < k; i++) {
        row[i][0] = 0;
        for (j = 1; j < k; j++) {
            row[i][j] = z++;
        }
    }
    /* Next lines */
    for (i = 1; i < k; i++) {
        for (j = 0; j < k - 1; j++) {
            row[(i - 1) * (k - 1) + k + j][0] = i;
            for (z = 1; z < k; z++) {
                int tilt = (j + (i - 1) * (z - 1)) % (k - 1) + 1;
                row[(i - 1) * (k - 1) + k + j][z] = row[z][tilt];
            }
        }
    }
    /* Print results */
    for (i = 0; i < n; i++) {
        for (j = 0; j < k; j++) {
            if (j > 0) {
                printf(" ");
            }
            printf("%d", row[i][j] + 1);
        }
        printf("\n");
    }

}

/* Main */
int main() {
    int first_go = 1;

    while (scanf("%d", &k) == 1) {
        n = (k * k) - k + 1;
        if (first_go) {
            first_go = 0;
        } 
        else {
            printf("\n");
        }
        print_intersection_points();

    }
    return 0;
}
