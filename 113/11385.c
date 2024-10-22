/* 11385
 * Da Vinci Code
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_LENGTH  1000
#define MAX_STRING  (MAX_LENGTH + 2)
#define MAX_FIBO    100
#define LIMIT_FIBO  (1L << 31)

typedef char string_t[MAX_STRING];

long fibonacci[MAX_FIBO];
int num_fibonacci;

/* Compute all Fibonacci numbers under limit */
void compute_fibonacci() {
    fibonacci[0] = 1, fibonacci[1] = 2;
    for (num_fibonacci = 2; fibonacci[num_fibonacci - 1] < LIMIT_FIBO; num_fibonacci++) {
        fibonacci[num_fibonacci] = fibonacci[num_fibonacci - 1] + fibonacci[num_fibonacci - 2];
    }
}

/* Compare two long integers */
int compare_long(const void *a, const void *b) {
    return *((long *) a) - *((long *) b);
}

/* Decode message */
void decode_message(char *num_string, char *char_string) {
    string_t output;
    int index, last;
    long value;
    memset(output, 0x20, MAX_LENGTH);
    for (last = 0, value = 0; *num_string != 0; num_string++) {
        if (isdigit(*num_string)) {
            value = value * 10 + *num_string - '0';
        }
        else if (value != 0) {
            long *pos = bsearch(&value, fibonacci, num_fibonacci, sizeof (long), compare_long);
            assert(pos != NULL);
            index = pos - fibonacci;
            for (; !isupper(*char_string); char_string++)
                ;
            output[index] = *char_string;
            char_string++;
            if (index > last) {
                last = index;
            }
            value = 0;
        }
    }
    output[last + 1] = 0;
    printf("%s\n", output);
}

/* Main function */
#define READ(x)     (fgets(x, MAX_STRING, stdin) != NULL)
int main() {
    string_t num_string, char_string;
    int num_tests;
    compute_fibonacci();
    assert(READ(num_string));
    for (num_tests = atoi(num_string); num_tests > 0; num_tests--) {
        assert(READ(num_string) && READ(num_string) && READ(char_string));
        decode_message(num_string, char_string);
    }
    return 0;
}
