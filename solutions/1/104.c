/* 104
 * Arbitrage
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX 20

double convertion[MAX][MAX];
double table[MAX][MAX];
int stack[MAX][MAX][MAX], top;
int result[MAX], size;
int n;


/* Find an exchange grater than 1 */
int find_exchange(int *i, int *m) {
    for (*i = 0; *i < n; (*i)++) {
        for (*m = 0; *m < n; (*m)++) {
            if (*i != *m) {
                double exchange = convertion[*i][*m] * table[*m][*i];
                if (exchange > 1.01) {
                    return 1;
                }
            }
        }
    }
    return 0;
}


/* Create new convertion rate */
void create_new_table() {
    int i, j, k;
    static double new_table[MAX][MAX];
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            int best_k = -1;
            double best_exchange = -1;
            for (k = 0; k < n; k++) {
                double exchange = convertion[i][k] * table[k][j];
                if (exchange > best_exchange) {
                    best_exchange = exchange;
                    best_k = k;
                }
            }
            new_table[i][j] = best_exchange;
            stack[i][j][top] = best_k;
        }
    }
    top++;
    memcpy(table, new_table, sizeof (double) * MAX * MAX);
}


/* Try to find an arbitrage */
int find_arbritrage() {
    int i, j, k;

    top = 0;
    memcpy(table, convertion, sizeof(double) * MAX * MAX);
    for (k = 0; k < n - 1; k++) {
        if (find_exchange(&i, &j)) {
            result[0] = i;
            result[1] = j;
            size = 2;
            while (top > 0) {
                result[size] = stack[j][i][--top];
                j = result[size++];
            }
            return 1;
        }
        else if (k <= n - 2) {
            create_new_table();
        }
    }
    return 0;
}


/* Main function */
int main() {
    int i, j;
    while (scanf("%d", &n) != EOF) {
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                if (i == j) {
                    convertion[i][j] = 1.0;
                }
                else {
                    assert(scanf("%lf", &convertion[i][j]) != EOF);
                }
            }
        }
        if (!find_arbritrage()) {
            printf("no arbitrage sequence exists\n");
        }
        else {
            double val = 1;
            for (i = 0; i < size; i++) {
                printf("%d ", result[i] + 1);
                val *= convertion[result[i]][result[(i + 1) % size]];
            }
            printf("%d\n", result[0] + 1);
        }
    }    
    return 0;
}
