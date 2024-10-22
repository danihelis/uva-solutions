/* 11413
 * Fill the Containers
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       1000
#define MAX(x,y)    ((x) > (y) ? (x) : (y))

int vessel[MAX_N];
int optimal[MAX_N][MAX_N];
char defined[MAX_N][MAX_N];
int num_vessels, num_containers;

/* Compute optimal distribution */
int optimal_distribution(int index, int how_many) {
    int i, sum, current, best;
    assert(index < num_vessels && how_many > 0);
    if (defined[index][how_many - 1])
        return optimal[index][how_many - 1];
    else if (how_many == 1)
        for (i = index, best = 0; i < num_vessels; i++)
            best += vessel[i];
    else {
        for (i = index, sum = 0, best = -1; 
                i <= num_vessels - how_many; i++) {
            sum += vessel[i];
            current = optimal_distribution(i + 1, how_many - 1);
            current = MAX(sum, current);
            if (best == -1 || current < best)
                best = current;
        }
    }
    defined[index][how_many - 1] = 1;
    optimal[index][how_many - 1] = best;
    return best;
}

/* Main function */
int main() {
    while (scanf("%d %d", &num_vessels, &num_containers) != EOF) {
        int i;
        if (num_containers > num_vessels)
            num_containers = num_vessels;
        for (i = 0; i < num_vessels; i++) {
            assert(scanf("%d", &vessel[i]) != EOF);
            memset(defined[i], 0, num_containers);
        }
        printf("%d\n", optimal_distribution(0, num_containers));
    }
    return EXIT_SUCCESS;
}
