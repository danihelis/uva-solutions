/* 10646
 * What is the Card?
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  4
#define NUM_CARDS   52
#define NUM_HAND    25
#define INIT_PILE   (NUM_CARDS - NUM_HAND)
#define NUM_REPEAT  3

typedef struct {
    char stack[NUM_CARDS][MAX_STRING];
    int top;
} stack_t;

/* Main function */
int main() {
    stack_t hand, pile;
    int i, k, value, count, test, num_tests;
    char *card;
    assert(scanf("%d ", &num_tests));
    for (test = 1; test <= num_tests; test++) {
        for (i = 0, pile.top = 0, hand.top = 0; i < NUM_CARDS; i++) {
            stack_t *s = i < INIT_PILE ? &pile : &hand;
            assert(scanf("%s ", s->stack[s->top++]) != EOF);
        }
        for (k = 0, count = -1; k < NUM_REPEAT; k++) {
            card = pile.stack[--pile.top];
            value = isdigit(*card) ? *card - '0' : 10;
            count += value;
            pile.top += value - 10;
        }
        card = count < pile.top ? pile.stack[count] : hand.stack[count - pile.top];
        printf("Case %d: %s\n", test, card);
    }
    return 0;
}
