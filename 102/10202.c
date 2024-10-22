/*
 * 10202
 * Pairsumonious Numbers
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>


#define MAX_NUMBER 10
#define MAX_VECTOR_SIZE ((MAX_NUMBER * MAX_NUMBER) / 2)

int summation[MAX_VECTOR_SIZE];
int used[MAX_VECTOR_SIZE];
int number[MAX_NUMBER];
int n, total_numbers;


/* Compare two integer in order to sort them */
int compare(const void *a, const void *b) {
    return *((int *) a) - *((int *) b);
}


/* Recursive function that determine the remaining numbers that compound summations */
int complete_determining(int num, int start) {
    int k, i;
    if (num >= n) {
        return 1;
    }

    while (used[start] && start < total_numbers) {
        start++;
    }
    assert(start < total_numbers);
    number[num] = summation[start] - number[0];
    used[start] = 1;
    start++;

    for (k = 1, i = start; k < num && i < total_numbers; i++) {
        if (!used[i] && summation[i] == number[k] + number[num]) {
            used[i] = 1;
            k++;
        }
    }
    return (k >= num ? complete_determining(num + 1, start) : 0);
}


/* Attempt to determine values of n1, n2 and n3, noting that
     s[0] = n1 + n2
     s[1] = n1 + n3
     s[x] = n2 + n3
   Thus, p = s[1] - s[0] = n1 + n3 - n1 - n2 = n3 - n2
         q = p + s[x] = n3 - n2 + n2 + n3 = 2.n3
   We have n3 = q/2, n1 = s[1] - n3 and n2 = s[0] - n1
 */
int determine_numbers() {
    int p, q, i;

    qsort(summation, total_numbers, sizeof (int), compare);
    p = summation[1] - summation[0];

    for (i = 0; i < n - 2; i++) {
        q = p + summation[2 + i];

        if (q % 2 == 0) {
            number[2] = q / 2;
            number[0] = summation[1] - number[2];
            number[1] = summation[0] - number[0];
            
            memset(used, 0, sizeof (int) * total_numbers);
            used[2 + i] = 1;
            if (complete_determining(3, 2)) {
                return 1;
            }
        }
    }
    return 0;
}


/* Main function */
int main() {
    int i;
    while (scanf("%d", &n) != EOF) {
        total_numbers = n * (n - 1) / 2;

        for (i = 0; i < total_numbers; i++) {
            assert(scanf("%d", &summation[i]) != EOF);
        }

        if (determine_numbers()) {
            for (i = 0; i < n; i++) {
                printf("%d%c", number[i], (i == n - 1 ? '\n' : ' '));
            }
        }
        else {
            printf("Impossible\n");
        }
    }
    return 0;
}
