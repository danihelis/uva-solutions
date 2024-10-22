/* 514
 * Rails
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_SIZE 10000

int stack[MAX_SIZE];
int top;

/* Main function */
int main() {
    int vector[MAX_SIZE];
    int size, i, coach, possible;
    while (scanf("%d", &size) != EOF) {
        if (size == 0) {
            break;
        }
        while (scanf("%d", &vector[0]) != EOF) {
            if (vector[0] == 0) {
                printf("\n");
                break;
            }
            for (i = 1; i < size; i++) {
                assert(scanf("%d", &vector[i]) != EOF);
            }
            for (i = 0, top = 0, possible = 1, coach = 1; possible && i < size; i++) {
                while (top == 0 || stack[top - 1] < vector[i]) {
                    stack[top++] = coach++;
                }
                if (stack[top - 1] != vector[i]) {
                    possible = 0;
                }
                top--;
            }
            printf("%s\n", possible ? "Yes" : "No");
        }
    }
    return 0;
}
