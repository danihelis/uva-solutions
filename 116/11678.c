/* 11678
 * Cards' Exchange
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   10000

/* Main function */
int main() {
    int alice[MAX_N], betty[MAX_N];
    int num_a, num_b, diff_a, diff_b;
    while (scanf("%d %d", &num_a, &num_b) != EOF && num_a > 0) {
        int a, b;
        for (a = 0; a < num_a; a++) {
            assert(scanf("%d", &alice[a]) != EOF);
        }
        for (b = 0; b < num_b; b++) {
            assert(scanf("%d", &betty[b]) != EOF);
        }
        a = b = diff_a = diff_b = 0; 
        while (a < num_a || b < num_b) {
            if (a < num_a && (b == num_b || alice[a] < betty[b])) {
                diff_a++;
                for (a++; a < num_a && alice[a] == alice[a - 1]; a++) 
                    ;
            } else if (b < num_b && (a == num_a || betty[b] < alice[a])) {
                diff_b++;
                for (b++; b < num_b && betty[b] == betty[b - 1]; b++) 
                    ;
            } else {
                for (a++; a < num_a && alice[a] == alice[a - 1]; a++) 
                    ;
                for (b++; b < num_b && betty[b] == betty[b - 1]; b++) 
                    ;
            }
        }
        printf("%d\n", diff_a < diff_b ? diff_a : diff_b);
    }
    return EXIT_SUCCESS;
}
