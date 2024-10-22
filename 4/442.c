/* 442
 * Matrix Chain Multiplication
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       26
#define MAX_STRING  500

typedef struct {
    int rows, cols;
} matrix_t;

matrix_t matrix[MAX_N];

/* Evaluate expression and compute number of elementary ops */
long compute_ops(char **s, matrix_t *res) {
    if (**s == '(') {
        matrix_t m[2] = {{0, 0}, {0, 0}};
        long o[2] = {0, 0};
        int i, valid;
        for (i = 0, valid = 1, (*s)++; valid && i < 2; i++) {
            o[i] = compute_ops(s, &m[i]);
            valid = o[i] >= 0;
        }
        valid = valid && m[0].cols == m[1].rows;
        if (valid) {
            assert(**s == ')');
            (*s)++;
            res->rows = m[0].rows, res->cols = m[1].cols;
            return o[0] + o[1] + m[0].rows * m[0].cols * m[1].cols;
        }
        return -1;
    } 
    *res = matrix[**s - 'A'];
    (*s)++;
    return 0;
}

/* Main function */
int main() {
    int num_matrices;
    char expression[MAX_STRING], *s;
    assert(scanf("%d", &num_matrices) == 1);
    for (; num_matrices > 0; num_matrices--) {
        char name;
        matrix_t *m;
        assert(scanf(" %c", &name) == 1);
        m = &matrix[name - 'A'];
        assert(scanf("%d %d", &m->rows, &m->cols) == 2);
    }
    while (scanf(" %s", expression) != EOF) {
        matrix_t result;
        long res;
        s = expression;
        res = compute_ops(&s, &result);
        (res < 0 ? printf("error\n") : printf("%ld\n", res));
    }
    return EXIT_SUCCESS;
}
