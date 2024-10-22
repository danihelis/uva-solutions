/* 11878
 * Homework Checker
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

/* Main function */
int main() {
    int n1, n2, corrects = 0;
    char op, result[10];
    while (scanf("%d%c%d=%s", &n1, &op, &n2, result) != EOF)
        if (result[0] != '?') {
            int ans = atoi(result);
            corrects += op == '+' && n1 + n2 == ans ? 1 :
                        op == '-' && n1 - n2 == ans ? 1 : 0;
        }
    printf("%d\n", corrects);
    return EXIT_SUCCESS;
}
