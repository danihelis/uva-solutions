/* 10141
 * Request for Proposal
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING 100

/* Main function */
int main() {
    int requirements, proposals, best_req;
    double best_price;
    char best_name[MAX_STRING];
    int i, j, test_case = 0;

    while (scanf("%d %d", &requirements, &proposals) != EOF) {
        if (requirements == 0) {
            break;
        }
        test_case++;
        printf("%sRFP #%d\n", (test_case == 1 ? "" : "\n"), test_case);

        for (i = 0; i < requirements; i++) {
            assert(scanf(" %*[^\n]") != EOF);
        }
        best_req = 0;
        for (i = 0; i < proposals; i++) {
            char name[MAX_STRING];
            double price;
            int req;
            assert(scanf(" %[^\n] %lf %d", name, &price, &req) != EOF);
            if (i == 0 || req > best_req || (req == best_req && price < best_price)) {
                best_req = req;
                best_price = price;
                strcpy(best_name, name);
            }
            for (j = 0; j < req; j++) {
                assert(scanf(" %*[^\n]") != EOF);
            }
        }
        printf("%s\n", best_name);
    }
    return 0;
}
