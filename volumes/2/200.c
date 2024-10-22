/* 200
 * Rare Order
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_LETTERS 27
#define MAX_STRING  1000
#define ORD(x)      ((x) - 'A')

typedef struct {
    char value, used;
    int preceed[MAX_LETTERS], num_precedences, order;
} letter_t, *letter_p;

letter_t letter[MAX_LETTERS], *letter_ptr[MAX_LETTERS];

/* Compare letters */
int compare_letters(const void *a, const void *b) {
    letter_p x = *((letter_p *) a), y = *((letter_p *) b);
    if (!x->used || !y->used) {
        return y->used - x->used;
    }
    return x->order - y->order;
}

/* Compute precedence order (Bellman-Ford) */
void compute_precedence(char first_letter) {
    int i, j, k, num_used;
    letter_p cur, pre;

    for (i = 0, num_used = 0; i < MAX_LETTERS; i++) {
        num_used += letter[i].used ? 1 : 0;
    }
    letter[ORD(first_letter)].order = 0;

    for (k = 0; k < num_used - 1; k++) {
        for (i = 0; i < MAX_LETTERS; i++) {
            cur = &letter[i];
            if (cur->used) {
                for (j = 0; j < cur->num_precedences; j++) {
                    pre = &letter[cur->preceed[j]];
                    if (cur->order <= pre->order) {
                        cur->order = pre->order + 1;
                    }
                }
            }
        }
    }
    qsort(letter_ptr, MAX_LETTERS, sizeof (letter_p), compare_letters);
}

/* Main function */
int main() {
    int i;
    char word[MAX_STRING], last[MAX_STRING], first_letter;

    for (i = 0; i < MAX_LETTERS; i++) {
        letter_p l = &letter[i];
        l->value = i + 'A', l->num_precedences = 0, l->order = 0, l->used = 0;
        letter_ptr[i] = l;
    }

    last[0] = 0, first_letter = 0;
    while (scanf(" %s", word) != EOF && word[0] != '#') {
        char *p, *l, exists;
        if (!first_letter) {
            first_letter = word[0];
        }
        for (p = word; *p != 0; p++) {
            letter[ORD(*p)].used = 1;
        }
        for (p = word, l = last; *p == *l && *p != 0; p++, l++)
            ;
        if (*p != 0 && *l != 0) {
            letter_p cur = &letter[ORD(*p)];
            int value = ORD(*l);
            for (i = 0, exists = 0; !exists && i < cur->num_precedences; i++) {
                exists = cur->preceed[i] == value;
            }
            if (!exists) {
                cur->preceed[cur->num_precedences++] = value;
            }
        }
        strcpy(last, word);
    }

    compute_precedence(first_letter);
    for (i = 0; letter_ptr[i]->used && i < MAX_LETTERS; i++) {
        printf("%c", letter_ptr[i]->value);
    }
    printf("\n");

    return 0;
}
