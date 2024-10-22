/* 497
 * Strategic Defense Initiative
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_LENGTH 1000000
#define MAX_STRING 50

typedef struct value_s {
    struct value_s *prior;
    int value;
} value_t, *value_p;

value_t input[MAX_LENGTH];
value_p sequence[MAX_LENGTH];
int input_size, length;

/* Main function */
int main() {
    char line[MAX_STRING];
    int num_tests, solution[MAX_LENGTH];
    assert(fgets(line, MAX_STRING, stdin) != NULL);
    num_tests = atoi(line);
    assert(fgets(line, MAX_STRING, stdin) != NULL && *line == '\n');
    for (; num_tests > 0; num_tests--) {
        int i;
        value_p current;
        input_size = 0, length = 0;
        while (fgets(line, MAX_STRING, stdin) != NULL && *line != '\n') {
            int start = 0, end = length, middle;
            assert(input_size < MAX_LENGTH);
            input[input_size].value = atoi(line);
            while (start < end) {
                middle = (start + end) / 2;
                if (input[input_size].value > sequence[middle]->value) {
                    start = middle + 1;
                }
                else {
                    end = middle;
                }
            }
            input[input_size].prior = (start > 0 ? sequence[start - 1] : NULL);
            sequence[start] = &input[input_size];
            input_size++;
            length += (start == length ? 1 : 0);
        }
        for (i = length - 1, current = sequence[length - 1]; i >= 0 && current != NULL; 
                i--, current = current->prior) {
            solution[i] = current->value;
        }
        assert(i < 0 && current == NULL);
        printf("Max hits: %d\n", length);
        for (i = 0; i < length; i++) {
            printf("%d\n", solution[i]);
        }
        printf("%s", (num_tests > 1 ? "\n" : ""));
    }
    return 0;
}
