/**
 * 134
 * Loglan - A Logical Language
 * by Daniel Donadon
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#define MAX_WORD 50
#define MAX_STATE 14
#define MAX_ARCH 5
#define NULL_STATE -1

typedef enum {
    A,
    MOD,
    BA,
    DA,
    LA,
    NAM,
    PREDA,
    END,
    INVALID_WORD
} rule_t;

typedef struct {
    rule_t rule;
    int state;
} arch_t;

typedef struct {
    arch_t arch[MAX_ARCH];
    int num_arch;
} state_t;

state_t state[MAX_STATE];
int cur_state;
int invalid_flow;


/* Build a state with the given parameters */
void build_state(int s, int amount, ...) {
    int i;
    va_list list;
    va_start(list, amount);
    for (i = 0; i < amount / 2; i++) {
        state[s].arch[i].rule = va_arg(list, rule_t);
        state[s].arch[i].state = va_arg(list, int);
    }
    state[s].num_arch = i;
}


/* Build all states (statically) */
void build_states() {
    build_state(0, 6, LA, 1, NAM, 8, DA, 9);
    build_state(1, 2, PREDA, 2);
    build_state(2, 6, PREDA, 2, MOD, 3, BA, 9);
    build_state(3, 2, PREDA, 4);
    build_state(4, 8, PREDA, 4, LA, 5, NAM, 7, END, NULL_STATE);
    build_state(5, 2, PREDA, 6);
    build_state(6, 4, PREDA, 6, END, NULL_STATE);
    build_state(7, 2, END, NULL_STATE);
    build_state(8, 4, MOD, 3, BA, 9);
    build_state(9, 2, PREDA, 10);
    build_state(10, 6, PREDA, 10, A, 9, END, NULL_STATE);
}


/* Determine rule */
#define IS_VOWEL(x) ((x) == 'a' || (x) == 'e' || (x) == 'i' || (x) == 'o' || (x) == 'u')
rule_t get_rule(char *str) {
    int i, size;
    if (str == NULL || str[0] == '\0') {
        return END;
    }
    size = strlen(str);
    for (i = 0; i < size; i++) {
        str[i] = tolower((int) str[i]);
    }
    if (!IS_VOWEL(str[size - 1])) {
        return NAM;
    }
    if (size == 1) {
        return A;
    }
    else if (size == 2) {
        switch (str[0]) {
            case 'g': return MOD;
            case 'b': return BA;
            case 'd': return DA;
            case 'l': return LA;
        }
        return INVALID_WORD;
    }
    else if (size == 5) {
        int i, k = 0;
        for (i = 0; i < 4; i++) {
            k += (IS_VOWEL(str[i]) ? 0 : 1);
        }
        if (k == 3 && (IS_VOWEL(str[2]) || IS_VOWEL(str[1]))) {
            return PREDA;
        }
    }
    return INVALID_WORD;
}


/* Determine next state, if the state flow is still valid */
void next_state(char *word) {
    rule_t rule;
    int i;

    if (invalid_flow) {
        return;
    }
    rule = get_rule(word);

    invalid_flow = 1;
    for (i = 0; invalid_flow && i < state[cur_state].num_arch; i++) {
        if (state[cur_state].arch[i].rule == rule) {
            cur_state = state[cur_state].arch[i].state;
            invalid_flow = 0;
        }
    }
}


/* Main */
int main() {
    char word[MAX_WORD];
    int end_of_sentence;

    build_states();
    while (scanf("%s", word) == 1) {
        if (word[0] == '#') {
            break;
        }
        invalid_flow = 0;
        cur_state = 0;
        end_of_sentence = 0;
        do {
            if (word[strlen(word) - 1] == '.') {
                word[strlen(word) - 1] = '\0';
                end_of_sentence = 1;
                if (word[0] == '\0') {
                    continue; /* it must only be presented non-null strings */
                }
            }
            next_state(word);
            if (!end_of_sentence) {
                scanf("%s", word);
            }
        }
        while (!end_of_sentence);
        next_state(NULL);
        if (!invalid_flow && cur_state == NULL_STATE) {
            printf("Good\n");
        }
        else {
            printf("Bad!\n");
        }
    }
    return 0;
}
