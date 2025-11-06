/* 320
 * Border
 * By Johan Schreiber
 */
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE        32
#define MAX_STRING      (MAX_SIZE + 2)
#define MARK            'X'

char bitmap[MAX_SIZE][MAX_STRING];

/* Main function */
int main() {
    int test, num_tests;

    assert(scanf("%d", &num_tests) == 1);
    for (test = 1; test <= num_tests; test++) {
        int x, y, i;
        char symbol;
        assert(scanf("%d %d ", &x, &y) == 2);

        for (i = 0; i < MAX_SIZE; i++) {
            memset(bitmap[i], '.', MAX_SIZE);
            bitmap[i][MAX_SIZE] = 0;
        }

        while (scanf("%c", &symbol) == 1 && symbol != '.') {
            assert(x > 0 && y > 0 && x < MAX_SIZE && y < MAX_SIZE);
            switch (symbol) {
            case 'E':
                bitmap[y - 1][x] = MARK;
                x++;
                break;
            case 'N':
                bitmap[y][x] = MARK;
                y++;
                break;
            case 'W':
                bitmap[y][x - 1] = MARK;
                x--;
                break;
            case 'S':
                bitmap[y - 1][x - 1] = MARK;
                y--;
                break;
            }
        }

        printf("Bitmap #%d\n", test);
        for (y = MAX_SIZE - 1; y >= 0; y--) {
            printf("%s\n", bitmap[y]);
        }
        printf("\n");
    }

    return EXIT_SUCCESS;
}
