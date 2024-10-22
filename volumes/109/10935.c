/* 10935
 * Throwing cards away I
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_QUEUE   200

/* Main function */
int main() {
    int front, rear, n, queue[MAX_QUEUE];
    while (scanf("%d", &n) != EOF && n > 0) {
        for (front = 0, rear = 0; rear < n; rear++)
            queue[rear] = rear + 1;
        printf("Discarded cards:");
        while (front < rear - 1) {
            int card = queue[front++];
            printf("%s%d", card == 1 ? " " : ", ", card);
            queue[rear++] = queue[front++];
        }
        printf("\nRemaining card: %d\n", queue[front]);
    }
    return EXIT_SUCCESS;
}
