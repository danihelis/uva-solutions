/* 628
 * Passwords
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_NAMES   100
#define MAX_RULES   1000
#define MAX_STRING  260
#define MAX_DIGITS  10

typedef char string_t[MAX_STRING];

string_t name[MAX_NAMES], rule;
int num_names;

/* Print a password following the general rule and the given placehold name */
void print_password(int position, int name_index) {
    int capture_position = 0, digit;
    for (; !capture_position && rule[position] != 0; position++) {
        if (rule[position] == '0') {
            capture_position = 1;
            for (digit = 0; digit < MAX_DIGITS; digit++) {
                rule[position] = '0' + digit;
                print_password(position + 1, name_index);
            }
            rule[position] = '0';
        }
    }
    if (!capture_position) {
        char *c;
        for (c = rule; *c != 0; c++) {
            if (*c == '#') {
                printf("%s", name[name_index]);
            }
            else {
                printf("%c", *c);
            }
        }
        printf("\n");
    }
}

/* Main function */
int main() {
    int i, num_rules;
    while (scanf("%d", &num_names) != EOF) {
        for (i = 0; i < num_names; i++) {
            assert(scanf(" %s", name[i]) != EOF);
        }
        assert(scanf("%d", &num_rules) != EOF);
        printf("--\n");
        for (; num_rules > 0; num_rules--) {
            assert(scanf(" %s", rule) != EOF);
            for (i = 0; i < num_names; i++) {
                print_password(0, i);
            }
        }
    }
    return 0;
}
