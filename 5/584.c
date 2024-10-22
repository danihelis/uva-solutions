/* 584
 * Bowling
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_FRAMES  10
#define MAX_STRING  (2 * 3 * MAX_FRAMES)

#define BPOINT(p)   (*(p) == 'X' ? 10 : *(p) - '0')
#define POINT(p)    (*(p) == '/' ? 10 - BPOINT(p - 2) : BPOINT(p))

/* Main function */
int main() {
    char input[MAX_STRING];
    while (fgets(input, MAX_STRING, stdin) != NULL && input[0] != 'G') {
        int points, frame;
        char *score;
        for (score = input, points = 0, frame = 0; frame < MAX_FRAMES; frame++) {
            if (isdigit(*score)) {
                if (*(score + 2) == '/') {
                    score += 4;
                    points += 10 + POINT(score);
                }
                else {
                    points += POINT(score) + POINT(score + 2);
                    score += 4;
                }
            }
            else {
                points += 10 + POINT(score + 2) + POINT(score + 4);
                score += 2;
            }
        }
        printf("%d\n", points);
    }
    return 0;
}
