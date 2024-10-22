/* 11242
 * Tour de France
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_GEARS   10
#define MAX_DRIVES  (MAX_GEARS * MAX_GEARS)

typedef struct {
    int first, second;
} ratio_t, *ratio_p;

int front[MAX_GEARS];
ratio_t drive[MAX_DRIVES];
int num_fronts, num_backs, num_drives;

/* Compare two drive ratios in order to sort them */
int compare_ratio(const void *a, const void *b) {
    ratio_p x = (ratio_p) a, y = (ratio_p) b;
    return (x->first * y->second) - (x->second * y->first);
}

/* Main function */
int main() {
    while (scanf("%d", &num_fronts) != EOF && num_fronts > 0) {
        int i, j, back;
        double maximum = 0;
        assert(scanf("%d", &num_backs) != EOF);
        for (i = 0; i < num_fronts; i++) {
            assert(scanf("%d", &front[i]) != EOF);
        }
        for (j = 0, num_drives = 0; j < num_backs; j++) {
            assert(scanf("%d", &back) != EOF);
            for (i = 0; i < num_fronts; i++, num_drives++) {
                drive[num_drives].first = front[i];
                drive[num_drives].second = back;
            }
        }
        qsort(drive, num_drives, sizeof (ratio_t), compare_ratio);
        for (i = 1; i < num_drives; i++) {
            double spread = (drive[i].first * drive[i - 1].second) / 
                (double) (drive[i].second * drive[i - 1].first);
            if (spread > maximum) {
                maximum = spread;
            }
        }
        printf("%.2f\n", maximum);
    }
    return 0;
}
