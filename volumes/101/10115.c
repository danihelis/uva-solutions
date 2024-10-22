/* 10115
 * Automatic Editing
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  300
#define MAX_RULES   10

typedef char string_t[MAX_STRING];

typedef struct {
    string_t find, replace;
} rule_t, *rule_p;

rule_t rule[MAX_RULES];
int num_rules;

/* Find and replace */
void find_replace(char *s, char *t, rule_p r) {
    int size_f, size_r, length;
    size_f = strlen(r->find), size_r = strlen(r->replace), length = 0;
    while (*s != 0) {
        *t = *s;
        t++, s++, length++;
        if (length >= size_f) {
            *t = 0;
            if (strcmp(t - size_f, r->find) == 0) {
                strcpy(t - size_f, r->replace);
                t += size_r - size_f;
                length += size_r - size_f;
            }
        }
    }
    *t = 0;
}

/* Main function */
#define READ(x) (fgets(x, MAX_STRING, stdin) != NULL)
int main() {
    string_t line[2];
    while (READ(line[0]) && (num_rules = atoi(line[0])) > 0) {
        int k;
        char *p;
        for (k = 0; k < num_rules; k++) {
            assert(READ(rule[k].find) && READ(rule[k].replace));
            p = strchr(rule[k].find, '\n');
            *p = 0;
            p = strchr(rule[k].replace, '\n');
            *p = 0;
        }
        assert(READ(line[0]));
        for (k = 0; k < num_rules; k++) {
            find_replace(line[k % 2], line[(k + 1) % 2], &rule[k]);
        }
        printf("%s", line[num_rules % 2]);
    }
    return 0;
}
