/* 763
 * Fibinary Numbers
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIGITS  110
#define MAX(x, y)   ((x) > (y) ? (x) : (y))

typedef struct {
    char digit[MAX_DIGITS];
    int num_digits;
} fibinary_t, *fibinary_p;

/* Convert sequence of chars to fibinary */
void convert(char *s, fibinary_p f) {
    int i;
    f->num_digits = strlen(s);
    for (i = f->num_digits - 1; i >= 0; s++, i--) {
        f->digit[i] = *s - '0';
    }
}

/* Normalize fibinary */
#define INCREASE(i, f) do { \
        if (i == f->num_digits - 1) { \
            f->num_digits++; \
            f->digit[i + 1] = 0; \
        } \
    } while (0)
void normalize(fibinary_p f) {
    int i = 0;
    while (i < f->num_digits) {
        /* Double digit: shift 1 forwards and backwards */
        if (f->digit[i] >= 2) {
            INCREASE(i, f);
            f->digit[i + 1]++;
            f->digit[i] -= 2;
            if (i > 0) {
                f->digit[(i == 1 ? 0 : i - 2)]++;
                i = MAX(0, i - 2);
            }
            continue;
        }
        /* Sequence 11: shifts 1 forwards */
        else if (f->digit[i] > 0 && i > 0 && f->digit[i - 1] > 0) {
            INCREASE(i, f);
            f->digit[i]--, f->digit[i - 1]--, f->digit[i + 1]++;
        }
        i++;
    }
}

/* Sum two fibinaries */
void sum_fibinary(fibinary_p a, fibinary_p b, fibinary_p c) {
    int i;
    for (i = 0; i < a->num_digits || i < b->num_digits; i++) {
        c->digit[i] = (i < a->num_digits ? a->digit[i] : 0) + 
            (i < b->num_digits ? b->digit[i] : 0);
    }
    c->num_digits = i;
    normalize(c);
}

/* Print a fibinary */
void print_fibinary(fibinary_p f) {
    int i;
    for (i = f->num_digits - 1; i >= 0; i--) {
        printf("%c", f->digit[i] + '0');
    }
}

/* Main function */
int main() {
    char first = 1, input[MAX_DIGITS];
    fibinary_t n1, n2;
    while (scanf(" %s", input) != EOF) {
        (first ? (void) (first = 0) : (void) printf("\n"));
        convert(input, &n1);
        assert(scanf(" %s", input) != EOF);
        convert(input, &n2);
        sum_fibinary(&n1, &n2, &n1);
        print_fibinary(&n1);
        printf("\n");
    }
    return 0;
}
