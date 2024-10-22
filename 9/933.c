/* 933
 * Water Flow
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DEPOSITS    26
#define MIN(x, y)       ((x) < (y) ? (x) : (y))

int n, maximum, deposit[MAX_DEPOSITS], tube[MAX_DEPOSITS];

/* Read data */
void read_data() {
    char param;
    int value;
    n = -1, maximum = 0;
    while (scanf(" %c=%d%*[;\n]", &param, &value) == 2) {
        if (param == 'N' && n < 0) {
            n = value;
            continue;
        }
        if (islower(param)) {
            tube[param - 'a'] = value;
        }
        else {
            deposit[param - 'A'] = value;
            maximum += value;
        }
    }
    assert(feof(stdin));
}

/* Main function */
int main() {
    int i, time, stop;
    read_data();
    for (i = -1; i < n; i++) {
        printf("%s  %c", i == -1 ? "" : " ", i == -1 ? 't' : i + 'A');
    }
    printf("\n");
    for (i = 0; i < 4 * n + 3; i++) {
        printf("-");
    }
    printf("\n");
    for (time = 0, stop = 0; !stop; time++) {
        printf("%3d", time);
        for (i = 0; i < n; i++) {
            printf(" %3d", deposit[i]);
        }
        printf("\n");
        stop = deposit[n - 1] == maximum;
        for (i = n - 1; i > 0; i--) {
            int displace = MIN(tube[i - 1], deposit[i - 1]);
            deposit[i] += displace, deposit[i - 1] -= displace;
        }
    }
    return 0;
}
