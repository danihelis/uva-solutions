/* 10906
 * Strange Integration
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_NAME    11
#define MAX_LENGTH  5001
#define MAX_EXP     50

typedef struct {
    char name[MAX_NAME];
    char param[2][MAX_NAME], op;
    char expanded[MAX_LENGTH];
} expres_t;

expres_t expres[MAX_EXP], *p_expres[MAX_EXP];
int num_express;

/* Find or insert expression */
expres_t * find(char name[], int insert) {
    int start = 0, end = num_express;
    while (start < end) {
        int middle = (start + end) / 2;
        int comp = strcmp(name, p_expres[middle]->name);
        if (comp == 0)
            return p_expres[middle];
        else if (comp > 0)
            start = middle + 1;
        else
            end = middle;
    }
    assert(insert);
    strcpy(expres[num_express].name, name);
    for (end = num_express; end > start; end--)
        p_expres[end] = p_expres[end - 1];
    p_expres[start] = &expres[num_express++];
    return p_expres[start];
}

/* Expand expression */
void expand(expres_t *e) {
    int k, use_par[2];
    expres_t *var[2];
    for (k = 0; k < 2; k++)
        var[k] = isdigit(e->param[k][0]) ? NULL : find(e->param[k], 0);
    use_par[0] = var[0] != NULL && e->op == '*' && var[0]->op == '+';
    use_par[1] = var[1] != NULL && (e->op == '*' || var[1]->op == '+');
    sprintf(e->expanded, "%s%s%s%c%s%s%s", 
            use_par[0] ? "(" : "",
            var[0] == NULL ? e->param[0] : var[0]->expanded,
            use_par[0] ? ")" : "",
            e->op,
            use_par[1] ? "(" : "",
            var[1] == NULL ? e->param[1] : var[1]->expanded,
            use_par[1] ? ")" : "");
}

/* Main function */
int main() {
    int test, num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (test = 0; test < num_tests; test++) {
        int i, k, n;
        expres_t *last;
        assert(scanf("%d", &n) != EOF);
        for (i = 0, num_express = 0, last = NULL; i < n; i++) {
            char par[3][MAX_NAME], op;
            assert(scanf(" %s = %s %c %s", par[0], par[1], &op, par[2]) 
                    != EOF);
            last = find(par[0], 1);
            last->op = op;
            for (k = 0; k < 2; k++)
                strcpy(last->param[k], par[k + 1]);
            expand(last);
        }
        assert(last != NULL);
        printf("Expression #%d: %s\n", test + 1, last->expanded);
    }
    return EXIT_SUCCESS;
}
