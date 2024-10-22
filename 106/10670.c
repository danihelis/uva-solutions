/* 10670
 * Work Reduction
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_PAPERS      100001
#define MAX_AGENCIES    100
#define MAX_NAME        20

#define MIN(x, y)       ((x) < (y) ? (x) : (y))
#define INFINITY        (1 << 30)

typedef struct {
    char name[MAX_NAME];
    int half, unit, cost;
} agency_t, *agency_p;

agency_t agency[MAX_AGENCIES];
agency_p agency_ptr[MAX_AGENCIES];
int num_agencies;

/* Compare two agencies */
int compare_agencies(const void *a, const void *b) {
    agency_p x = *((agency_p *) a), y = *((agency_p *) b);
    return (x->cost == y->cost ? strcmp(x->name, y->name) : x->cost - y->cost);
}

/* Determine the minimum cost for an agency */
void find_minimum_cost(agency_p a, int start, int end) {
    static int cost[MAX_PAPERS];
    int i;
    cost[start] = 0;
    for (i = start - 1; i >= end; i--) {
        int unit_cost = cost[i + 1] + a->unit;
        int double_cost[2];
        double_cost[0] = (2 * i + 1 <= start ? cost[2 * i + 1] + a->half : INFINITY);
        double_cost[1] = (2 * i <= start ? cost[2 * i] + a->half : INFINITY);
        cost[i] = MIN(double_cost[0], double_cost[1]);
        cost[i] = MIN(cost[i], unit_cost);
    }
    a->cost = cost[end];
}

/* Main function */
int main() {
    int test, num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (test = 1; test <= num_tests; test++) {
        int i, start, end;
        assert(scanf("%d %d %d", &start, &end, &num_agencies) != EOF);
        for (i = 0; i < num_agencies; i++) {
            agency_p a = &agency[i];
            assert(scanf(" %[^:]:%d,%d", a->name, &a->unit, &a->half) != EOF);
            agency_ptr[i] = a;
            find_minimum_cost(a, start, end);
        }
        qsort(agency_ptr, num_agencies, sizeof (agency_p), compare_agencies);
        printf("Case %d\n", test);
        for (i = 0; i < num_agencies; i++) {
            printf("%s %d\n", agency_ptr[i]->name, agency_ptr[i]->cost);
        }
    }
    return 0;
}
