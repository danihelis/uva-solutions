/* 755
 * 487--3279
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_PHONES  100000
#define MAX_STRING  1000

char alpha[] = "ABCDEFGHIJKLMNOPRSTUVWXY";
int phone[MAX_PHONES], num_phones;

/* Compare phone */
int compare(const void *a, const void *b) {
    return *((int *) a) - *((int *) b);
}

/* Convert string into phone number */
int convert(char *sequence) {
    int phone;
    for (phone = 0; *sequence != 0; sequence++) {
        if (isdigit(*sequence)) {
            phone = phone * 10 + *sequence - '0';
        }
        else if (isalpha(*sequence)) {
            char *p = strchr(alpha, *sequence);
            assert(p != NULL);
            phone = phone * 10 + (p - alpha) / 3 + 2;
        }
    }
    return phone;
}

/* Print repetitions */
#define LAST_DIGITS     10000
void print_repetitions() {
    int i, has_repetition;
    qsort(phone, num_phones, sizeof (int), compare);
    for (i = 0, has_repetition = 0; i < num_phones; ) {
        int current = phone[i], repeat;
        for (i += 1, repeat = 1; i < num_phones && phone[i] == current; repeat++, i++)
            ;
        if (repeat > 1) {
            printf("%03d-%04d %d\n", current / LAST_DIGITS, current % LAST_DIGITS, repeat);
            has_repetition = 1;
        }
    }
    if (!has_repetition) {
        printf("No duplicates.\n");
    }
}

/* Main function */
int main() {
    int i, num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        assert(scanf(" %d", &num_phones) != EOF);
        for (i = 0; i < num_phones; i++) {
            char input[MAX_STRING];
            assert(scanf(" %s", input) != EOF);
            phone[i] = convert(input);
        }
        print_repetitions();
        if (num_tests > 1) {
            printf("\n");
        }
    }
    return 0;
}
