/* 10870
 * Recurrences
 * By Johan Schreiber
 */
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIM         16

typedef struct {
    long matrix[MAX_DIM][MAX_DIM];
    int dim;
} matrix_t;


/* Multiply two matrices using modulo M */
void multiply_matrix(matrix_t *r, matrix_t *a, matrix_t *b, long modulo) {
    int i, j, k;

    assert(a->dim == b->dim);
    r->dim = a->dim;

    for (i = 0; i < r->dim; i++) {
        for (j = 0; j < r->dim; j++) {
            long sum = 0;
            for (k = 0; k < r->dim; k++) {
                sum += (a->matrix[i][k] % modulo) * (b->matrix[k][j] % modulo);
                sum %= modulo;
            }
            r->matrix[i][j] = sum;
        }
    }
}

/* Raise matrix to N-th power using modulo M */
void power_matrix(matrix_t *r, matrix_t *m, long exp, long modulo) {
    matrix_t base = *m;

    int i, j;

    r->dim = m->dim;
    for (i = 0; i < r->dim; i++) {
        for (j = 0; j < r->dim; j++) {
            r->matrix[i][j] = i == j ? 1 : 0;
        }
    }

    while (exp > 0) {
        matrix_t result;

        if (exp % 2 == 1) {
            multiply_matrix(&result, r, &base, modulo);
            *r = result;
        }

        exp /= 2;
        multiply_matrix(&result, &base, &base, modulo);
        base = result;
    }
}


/* Compute recurrence F(N) modulo M. We use matrices:
 *
 * F_n = [f_n+d-1  f_n-d-2  ...  f_n]
 * F_0 = [f_d-1    f_d-2    ...  f_0]
 *
 * F_n = A^n · F_0
 *
 * where A = [ a_0  a_1  ...  a_d-2 a_d-1 ]
 *           [ 1    0    ...  0     0     ]
 *           [ .    .    ...  .     .     ]
 *           [ 0    0    ...  1     0     ]
 *
 * The Fibonacci sequence would be:
 *
 * [f_n+1] = [1 1]^n · [1]
 * [f_n  ]   [1 0]     [1]
 */
long compute_recurrence(long coefs[], long initials[], int dim, long n,
        long modulo) {
    matrix_t a, result;
    int i, j;
    long value;

    a.dim = dim;
    for (i = 0; i < dim; i++) {
        a.matrix[0][i] = coefs[i] % modulo;
    }
    for (i = 0; i < dim - 1; i++) {
        for (j = 0; j < dim; j++) {
            a.matrix[i + 1][j] = i == j ? 1 : 0;
        }
    }

    power_matrix(&result, &a, n, modulo);
    for (i = value = 0; i < dim; i++) {
        value += (result.matrix[dim - 1][i] * initials[dim - i - 1] % modulo);
        value %= modulo;
    }

    return value;
}


/* Main function */
int main() {
    long coefs[MAX_DIM], initials[MAX_DIM];
    int i, d;
    long n, modulo;

    while (scanf("%d %ld %ld", &d, &n, &modulo) == 3 && d > 0) {
        assert(d <= MAX_DIM);

        for (i = 0; i < d; i++) {
            assert(scanf("%ld", &coefs[i]) == 1);
        }
        for (i = 0; i < d; i++) {
            assert(scanf("%ld", &initials[i]) == 1);
        }
        printf("%ld\n", compute_recurrence(coefs, initials, d, n - 1, modulo));
    }

    return EXIT_SUCCESS;
}
