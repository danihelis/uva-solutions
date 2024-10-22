/* 343
 * What Base Is This?
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  1000
#define MAX_DIGITS  (MAX_STRING)
#define MIN_BASE    2
#define MAX_BASE    36

typedef struct {
    int digit[MAX_DIGITS];
    int num_digits, base;
} bigint_t, *bigint_p;

/* Set initial value of bigint */
void set_bigint(bigint_p n, int v, int b) {
    n->digit[0] = v;
    n->num_digits = 1;
    n->base = b;
}

/* Sum two bigints of same base */
void sum_bigint(bigint_p a, int m, bigint_p b, bigint_p c) {
    int i, carry;
    assert(a->base == b->base && a->base > 1);
    for (i = 0, carry = 0; carry > 0 || i < a->num_digits || i < b->num_digits; i++) {
        int sum = carry + (i < a->num_digits ? a->digit[i] : 0) +
            (i < b->num_digits ? m * b->digit[i] : 0);
        c->digit[i] = sum % a->base;
        carry = sum / a->base;
    }
    assert(i < MAX_DIGITS);
    c->base = a->base;
    c->num_digits = i;
}

/* Convert from one base into another */
void convert_base(bigint_p a, int base, bigint_p b) {
    bigint_t factor;
    int i;
    set_bigint(b, 0, base);
    for (i = 0; i < a->num_digits; i++) {
        if (i == 0) {
            set_bigint(&factor, 1, base);
        }
        else {
            bigint_t zero;
            set_bigint(&zero, 0, base);
            sum_bigint(&zero, a->base, &factor, &zero);
            factor = zero;
        }
        sum_bigint(b, a->digit[i], &factor, b);
    }
}

/* Print bigint */
#if 0
void print_bigint(bigint_p n) {
    int i;
    for (i = n->num_digits - 1; i >= 0; i--) {
        int v = n->digit[i];
        fprintf(stderr, "%c", (v < 10 ? v + '0' : v - 10 + 'A'));
    }
    fprintf(stderr, "(%d)", n->base);
}
#endif

/* Compare two bigints */
int compare_bigint(bigint_p a, bigint_p b) {
    int i;
    bigint_t temp;
#if 0
    {
        fprintf(stderr, "Comparing: A = ");
        print_bigint(a);
        fprintf(stderr, "  B = ");
        print_bigint(b);

    }
#endif
    if (a->base != b->base) {
        convert_base(a, b->base, &temp);
        a = &temp;
    }
#if 0
    {
        fprintf(stderr, " --- converted: A = ");
        print_bigint(a);
        fprintf(stderr, "\n");
    }
#endif
    if (a->num_digits != b->num_digits) {
        return a->num_digits - b->num_digits;
    }
    for (i = a->num_digits - 1; i >= 0; i--) {
        if (a->digit[i] != b->digit[i]) {
            return a->digit[i] - b->digit[i];
        }
    }
    return 0;
}

/* Convert char sequence into baseless bigint and return least base */
int to_bigint(char *sequence, bigint_p n) {
    int i, base;
    n->num_digits = strlen(sequence);
    n->base = 0;
    for (i = n->num_digits - 1, base = MIN_BASE; i >= 0; sequence++, i--) {
        n->digit[i] = (isdigit(*sequence) ? *sequence - '0' : *sequence - 'A' + 10);
        if (n->digit[i] >= base) {
            base = n->digit[i] + 1;
        }
    }
    return base;
}

/* Binary-search for a base in which both numbers are equal (b's base is fixed)  */
int find_base(bigint_p a, int start, bigint_p b) {
    int comp, middle, end = MAX_BASE;
    while (start <= end) {
        middle = (start + end) / 2;
        a->base = middle;
        comp = compare_bigint(a, b);
        if (comp == 0) {
            return 0;
        }
        else if (comp < 0) {
            start = middle + 1;
        }
        else {
            end = middle - 1;
        }
    }
    return (start > MAX_BASE ? -1 : 1);
}

/* Find the minimum bases so that both sequences are equal numbers */
void find_both_bases(char *seq1, char *seq2) {
    bigint_t n1, n2, *n[2];
    int s1, s2, *s[2];
    int not_found;
    s1 = to_bigint(seq1, &n1), s2 = to_bigint(seq2, &n2);
    if (s1 < s2) {
        s[0] = &s1, s[1] = &s2, n[0] = &n1, n[1] = &n2;
    }
    else {
        s[0] = &s2, s[1] = &s1, n[0] = &n2, n[1] = &n1;
    }
    if (strcmp(seq1, seq2) == 0) {
        printf("%s (base %d) = %s (base %d)\n", seq1, s1, seq2, s2);
        return;
    }
    
    for (not_found = 1; not_found > 0 && *(s[1]) <= MAX_BASE; (*(s[1]))++) {
        n[1]->base = *(s[1]);
        not_found = find_base(n[0], *(s[0]), n[1]);
    }
    if (not_found) {
        printf("%s is not equal to %s in any base %d..%d\n", seq1, seq2, MIN_BASE, MAX_BASE);
    }
    else {
        printf("%s (base %d) = %s (base %d)\n", seq1, n1.base, seq2, n2.base);
    }
}

/* Main function */
int main() {
    char input[2][MAX_STRING];
    while (scanf(" %s %s", input[0], input[1]) != EOF) {
        find_both_bases(input[0], input[1]);
    }
    return 0;
}
