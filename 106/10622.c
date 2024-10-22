/* 10622
 * Perfect P-th Powers
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_VALUE   0x80000000
#define MAX_TABLE   100000

typedef struct expo {
    long number;
    int expo, odd_exp;
} expo_t;

expo_t table[MAX_TABLE];
int size;


/* Binary search */
int find(long number, int *pos) {
    int start = 0, end = size;
    while (start < end) {
        int middle = (start + end) / 2;
        if (table[middle].number == number) {
            *pos = middle;
            return 1;
        }
        else if (table[middle].number > number)
            end = middle;
        else 
            start = middle + 1;
    }
    *pos = start;
    return 0;
}


/* Insert number */
void insert(long number, int expo) {
    int i, pos;
    if (find(number, &pos)) {
        if (expo > table[pos].expo)
            table[pos].expo = expo;
        if (expo % 2 == 1 && expo > table[pos].odd_exp)
            table[pos].odd_exp = expo;
    }
    else {
        for (i = size; i > pos; i--)
            table[i] = table[i - 1];
        table[pos].number = number;
        table[pos].expo = expo;
        table[pos].odd_exp = expo % 2 == 1 ? expo : 1;
        size++;
    }
}

/* Create table */
void create_table() {
    long n, base;
    int exp;
    size = 0;
    for (base = 2; base < MAX_VALUE; base++) {
        n = base * base;
        if (n > MAX_VALUE)
            break;
        for (exp = 2; n <= MAX_VALUE; exp++, n *= base)
            insert(n, exp);
    }
}


/* Main function */
int main() {
    int n, pos;
    create_table();
    while (scanf("%d", &n) == 1 && n != 0) {
        if (find(labs(n), &pos))
            printf("%d\n", n > 0 ? table[pos].expo : table[pos].odd_exp);
        else
            printf("1\n");
    }
    return EXIT_SUCCESS;
}
