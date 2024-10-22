/* 11777
 * Automate the Grades
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define NUM_MARKS       7
#define NUM_TESTS       3
#define FIRST_TEST      (NUM_MARKS - NUM_TESTS)

/* Main function */
int main() {
    int num_tests, test;
    assert(scanf("%d", &num_tests) != EOF);
    for (test = 1; test <= num_tests; test++) {
        int mark[NUM_TESTS], least, i, grade, score;
        for (i = 0, score = 0, least = -1; i < NUM_MARKS; i++) {
            assert(scanf("%d", &grade) != EOF);
            if (i < FIRST_TEST) {
                score += grade;
            }
            else {
                mark[i - FIRST_TEST] = grade;
                least = (least == -1 || least > grade) ? grade : least;
            }
        }
        for (i = 0, least = -least; i < NUM_TESTS; i++) {
            least += mark[i];
        }
        score += least / (NUM_TESTS - 1);
        score = 9 - score / 10;
        score = (score < 0 ? 0 : score > 3 ? 5 : score);
        printf("Case %d: %c\n", test, 'A' + score);
    }
    return 0;
}
