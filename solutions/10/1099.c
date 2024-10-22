/* 1099
 * Sharing Chocolate
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIM     100
#define MAX_PIECES  15
#define MAX_COMB    33000

typedef struct {
    int num_comb;
    int *comb;
} config_t;

config_t config[MAX_DIM][MAX_DIM];
int piece[MAX_PIECES], num_pieces, rows, cols;

/* Insert unique */
void insert_unique(int value, int v[], int *n) {
    int start = 0, end = *n;
    while (start < end) {
        int middle = (start + end) / 2;
        if (v[middle] == value)
            return;
        else if (v[middle] > value)
            end = middle;
        else
            start = middle + 1;
    }
    for (end = *n; end > start; end--)
        v[end] = v[end - 1];
    v[start] = value;
    (*n)++;
}

/* Create combinations */
void create_combs(config_t *a, config_t *b, int *c, int *n) {
    int i, j;
    for (i = 0; i < a->num_comb; i++)
        for (j = 0; j < b->num_comb; j++) {
            int pa = a->comb[i], pb = b->comb[j];
            if ((pa & pb) == 0)
                insert_unique(pa | pb, c, n);
        }
}

/* Find combinations */
void find_combs(config_t *conf, int r, int c) {
    int combs[MAX_COMB], n;
    int i, j;
    for (i = 0, n = 0; i < num_pieces; i++)
        if (piece[i] == r * c)
            combs[n++] = 1 << i;
    for (i = 1; i * 2 <= r; i++)
        create_combs(&config[i - 1][c - 1], &config[r - i - 1][c - 1],
                combs, &n);
    for (j = 1; j * 2 <= c; j++)
        create_combs(&config[r - 1][j - 1], &config[r - 1][c - j - 1],
                combs, &n);
    conf->num_comb = n;
    conf->comb = NULL;
    if (n > 0) {
        conf->comb = (int *) malloc(n * sizeof (int));
        memcpy(conf->comb, combs, n * sizeof (int));
    }
}

/* Find solution */
int find_solution() {
    int i, j, sol;
    for (i = 0; i < rows; i++)
        for (j = 0; j < cols; j++)
            find_combs(&config[i][j], i + 1, j + 1);
    sol = config[rows - 1][cols - 1].num_comb > 0;
    for (i = 0; i < rows; i++)
        for (j = 0; j < cols; j++)
            if (config[i][j].num_comb > 0)
                free(config[i][j].comb);
    return sol;
}

/* Main function */
int main() {
    int test = 0;
    while (scanf("%d", &num_pieces) == 1 && num_pieces > 0) {
        int i, sum, sol;
        assert(scanf("%d %d", &rows, &cols) == 2);
        for (i = sum = 0; i < num_pieces; i++) {
            assert(scanf("%d", &piece[i]) == 1);
            sum += piece[i];
        }
        sol = (sum == rows * cols) && find_solution();
        printf("Case %d: %s\n", ++test, sol ? "Yes" : "No");
    }
    return EXIT_SUCCESS;
}
