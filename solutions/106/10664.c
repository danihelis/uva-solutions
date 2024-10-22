/* 10664
 * Luggage
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       20
#define MAX_STRING  (MAX_N * 10)

int weight[MAX_N], n;

/* Find summed weight */
int find(int index, int parcial, int goal) {
    if (index >= n || parcial > goal)
        return 0;
    if (weight[index] + parcial == goal)
        return 1;
    return find(index + 1, parcial + weight[index], goal) ||
        find(index + 1, parcial, goal);
}

/* Main function */
#define READ(x)     (fgets(x, MAX_STRING, stdin) != NULL)
int main() {
    int sum, num_tests;
    char input[MAX_STRING], *value;
    assert(READ(input));
    for (num_tests = atoi(input); num_tests > 0; num_tests--) {
        assert(READ(input));
        for (n = sum = 0, value = strtok(input, " \n"); value != NULL;
                n++, value = strtok(NULL, " \n")) {
            weight[n] = atoi(value);
            sum += weight[n];
        }
        printf("%s\n", sum % 2 == 0 && find(0, 0, sum / 2) ? "YES" : "NO");
    }
    return EXIT_SUCCESS;
}
