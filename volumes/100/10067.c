/* 10067
 * Playing with Wheels
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       10000
#define NUM_COMBS   8

char forbidden[MAX_N];
int neighbor[MAX_N][NUM_COMBS];

/* Generate next numbers from a sequence */
void generate_neighbors(int value) {
    int i, k;
    char root[5], back;
    sprintf(root, "%04d", value);
    for (k = 0; k < NUM_COMBS; k++) {
        i = k / 2;
        back = root[i];
        root[i] = '0' + (root[i] - '0' + (k % 2 == 0 ? 9 : 1)) % 10;
        neighbor[value][k] = atoi(root);
        root[i] = back;
    }
}

/* Generate all combinations */
void generate_all_neighbors() {
    int i;
    for (i = 0; i < MAX_N; i++)
        generate_neighbors(i);
}

/* Find minimum steps to achieve final state */
int find_final_state(int start, int end) {
    struct {
        int value, steps;
    } queue[MAX_N], current, next;
    int i, front, rear, *comb;
    queue[0].value = start, queue[0].steps = 0;
    forbidden[start] = 1;
    front = 0, rear = 1;
    while (front < rear) {
        current = queue[front++];
        if (current.value == end)
            return current.steps;
        next.steps = current.steps + 1;
        comb = neighbor[current.value];
        for (i = 0; i < NUM_COMBS; i++)
            if (comb[i] == end)
                return next.steps;
            else if (!forbidden[comb[i]]) {
                next.value = comb[i];
                queue[rear++] = next;
                forbidden[comb[i]] = 1;
            }
    }
    return -1;
}

/* Read entry */
int read_entry() {
    int a, b, c, d;
    assert(scanf("%d %d %d %d", &a, &b, &c, &d) == 4);
    return a * 1000 + b * 100 + c * 10 + d;
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) == 1);
    generate_all_neighbors();
    for (; num_tests > 0; num_tests--) {
        int start = read_entry(), 
            goal = read_entry();
        int n;
        memset(forbidden, 0, sizeof (forbidden));
        assert(scanf("%d", &n) == 1);
        for (; n > 0; n--) {
            int state = read_entry();
            forbidden[state] = 1;
        }
        printf("%d\n", find_final_state(start, goal));
    }
    return EXIT_SUCCESS;
}
