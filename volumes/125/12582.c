/* 12582
 * Wedding of Sultan
 * By Johan Schreiber
 */
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N           26
#define MAX_STRING      (2 + MAX_N * 2)
#define ORD(x)          ((x) - 'A')

/* Main function */
int main() {
    int test, num_tests;
    assert(scanf("%d", &num_tests) == 1);
    for (test = 1; test <= num_tests; test++) {
        char input[MAX_STRING], stack[MAX_STRING], visited[MAX_N], *c;
        int count[MAX_N], top, i;
        assert(scanf(" %s", input) == 1);
        memset(count, 0, sizeof (int) * MAX_N);
        memset(visited, 0, sizeof (char) * MAX_N);
        for (c = input, top = 0; *c != 0; c++) {
            if (visited[ORD(*c)]) {
                assert(top > 0 && *c == stack[top - 1]);
                top--;
            } else {
                if (top > 0) {
                    count[ORD(stack[top - 1])]++;
                    count[ORD(*c)]++;
                }
                stack[top++] = *c;
                visited[ORD(*c)] = 1;
            }
        }
        printf("Case %d\n", test);
        for (i = 0; i < MAX_N; i++) {
            if (count[i]) printf("%c = %d\n", i + 'A', count[i]);
        }
    }
    return EXIT_SUCCESS;
}
