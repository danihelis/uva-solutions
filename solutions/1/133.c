/**
 * 133
 * The Dole Queue
 * by Daniel Donadon
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_N 20

int queue[MAX_N];
int n, k, m;


/* Remove an individual from queue and update the indexes */
void remove_from_queue(int i, int *a, int *b) {
    if (*a > i) {
        (*a)--;
    }
    if (*b > i) {
        (*b)--;
    }
    for (; i < n - 1; i++) {
        queue[i] = queue[i + 1];
    }
    n--;
    if (n > 0) {
        *a %= n;
        *b %= n;
    }
}


/* Main */
int main() {
    int i, posK, posM;

    while (scanf("%d %d %d", &n, &k, &m) == 3) {
        if (n == 0) {
            break;
        }
        for (i = 0; i < n; i++) {
            queue[i] = i + 1;
        }
        k--;
        m--;
        posK = 0;
        posM = 0;
        while (n > 0) {
            posK = (posK + (k % n)) % n;
            posM = (n + posM - 1 - (m % n)) % n;
            printf("%3d", queue[posK]);
            if (posM != posK) {
                printf("%3d", queue[posM]);
                remove_from_queue(posM, &posK, &posM);
            }
            remove_from_queue(posK, &posK, &posM);
            if (n > 0) {
                printf(",");
            }
        }
        printf("\n");
    }
    return 0;
}
