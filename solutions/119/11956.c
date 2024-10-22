/* 11956
 * Brainfuck
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   100


/* Main function */
int main() {
    int test, num_tests;
    assert(scanf("%d ", &num_tests) == 1);
    for (test = 1; test <= num_tests; test++) {
        int memory[MAX_N], pointer;
        char command;
        memset(memory, 0, sizeof (memory));
        pointer = 0;
        while ((command = getchar()) != '\n') {
            switch (command) {
                case '+': memory[pointer] = (0x100 + memory[pointer] + 1) % 0x100; break;
                case '-': memory[pointer] = (0x100 + memory[pointer] - 1) % 0x100; break;
                case '>': pointer = (MAX_N + pointer + 1) % MAX_N; break;
                case '<': pointer = (MAX_N + pointer - 1) % MAX_N; break;
            }
        }
        printf("Case %d:", test);
        for (pointer = 0; pointer < MAX_N; pointer++)
            printf(" %02X", memory[pointer]);
        puts("");
    }
    return EXIT_SUCCESS;
}
