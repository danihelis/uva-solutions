/* 410
 * Station Balance
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_CHAMBERS    5
#define MAX_UNITS       2
#define MAX_BODIES      (MAX_UNITS * MAX_CHAMBERS)
#define INFINITY        1e10

#define ABSDIFF(x, y)   ((x) > (y) ? (x) - (y) : (y) - (x))

typedef struct {
    int body[MAX_UNITS];
    int num_bodies;
} chamber_t, *chamber_p;

int weight[MAX_BODIES];
chamber_t best[MAX_CHAMBERS], draft[MAX_CHAMBERS];
double best_imbalance, average;
int num_bodies, num_chambers;

/* Compare two integers */
int compare_int(const void *a, const void *b) {
    return *((int *) a) - *((int *) b);
}

/* Choose the best chamber configuration */
void best_configuration(int i, int n, int k, double imbalance) {
    if (k == 0) {
        if (imbalance < best_imbalance) {
            memcpy(best, draft, MAX_CHAMBERS * sizeof (chamber_t));
            best_imbalance = imbalance;
        }
    }
    else if (i >= n) {
        draft[k - 1].num_bodies = 0;
        best_configuration(i, n, k - 1, imbalance + average);
    }
    else {
        if (n - i < 2 * k) {
            draft[k - 1].num_bodies = 1;
            draft[k - 1].body[0] = weight[n - 1];
            best_configuration(i, n - 1, k - 1, imbalance + ABSDIFF(weight[n - 1], average));
        }
        if (n - i > k) {
            draft[k - 1].num_bodies = 2;
            draft[k - 1].body[0] = weight[n - 1];
            draft[k - 1].body[1] = weight[i];
            best_configuration(i + 1, n - 1, k - 1, 
                    imbalance + ABSDIFF(weight[n - 1] + weight[i], average));
        }
    }
}

/* Main function */
int main() {
    int set = 0;
    while (scanf("%d %d", &num_chambers, &num_bodies) != EOF) {
        int i, j;
        for (i = 0, average = 0; i < num_bodies; i++) {
            assert(scanf("%d", &weight[i]) != EOF);
            average += weight[i];
        }
        average /= num_chambers;
        qsort(weight, num_bodies, sizeof (int), compare_int);
        best_imbalance = INFINITY;
        best_configuration(0, num_bodies, num_chambers, 0);
        assert(best_imbalance < INFINITY);

        printf("Set #%d\n", ++set);
        for (i = 0; i < num_chambers; i++) {
            printf(" %d:", i);
            for (j = 0; j < best[i].num_bodies; j++) {
                printf(" %d", best[i].body[j]);
            }
            printf("\n");
        }
        printf("IMBALANCE = %.5f\n\n", best_imbalance);
    }
    return 0;
}
