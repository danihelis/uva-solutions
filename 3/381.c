/* 381
 * Making the Grade
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STUDENTS    30
#define MAX_TESTS       10
#define ROUND(x)        ((int) (0.5 + ((double) x)))
#define ROUND10(x)      ((int) (10.0 * ((double) x) + 0.5))

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) == 1);
    printf("MAKING THE GRADE OUTPUT\n");
    for (; num_tests > 0; num_tests--) {
        int test[MAX_STUDENTS], bonus[MAX_STUDENTS], fault[MAX_STUDENTS];
        int i, n, t, avg, sd, grade;
        assert(scanf("%d %d", &n, &t) == 2);
        for (i = avg = 0; i < n; i++) {
            int j, sum, min, val;
            for (j = sum = 0, min = 100; j < t; j++) {
                assert(scanf("%d", &val) == 1);
                sum += val;
                min = val < min ? val : min;
            }
            test[i] = t > 2 ? ROUND10((sum - min) / (t - 1)) : 
                              ROUND10(sum / t);
            avg += test[i];
            assert(scanf("%d %d", &bonus[i], &fault[i]) == 2);
        }
        avg = ROUND(avg / n);
        for (i = sd = 0; i < n; i++)
            sd += (test[i] - avg) * (test[i] - avg);
        sd = ROUND(sqrt((double) sd / n));
        for (i = grade = 0; i < n; i++) {
            int res = test[i] + 30 * (bonus[i] / 2);
            int g = res >= avg + sd ? 4 :
                    res >= avg ? 3 :
                    res >= avg - sd ? 2 : 1;
            if (fault[i] == 0)
                g = g < 4 ? g + 1 : 4;
            else {
                g -= fault[i] / 4;
                g = g < 0 ? 0 : g;
            }
            grade += g;
        }
        grade = ROUND10(grade / n);
        printf("%d.%d\n", grade / 10, grade % 10);
    }
    printf("END OF OUTPUT\n");
    return EXIT_SUCCESS;
}
