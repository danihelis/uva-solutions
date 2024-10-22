/* 10405
 * Longest Common Subsequence
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  1005

#define MAX(x,y)    ((x) > (y) ? (x) : (y))

/* Longest common subsequence */
int lcs(char *s1, char *s2) {
    int count[MAX_STRING], previous[MAX_STRING];
    int i, j, n1 = strlen(s1) - 1, n2 = strlen(s2) - 1;
    memset(previous, 0, (n1 + 1) * sizeof (int));
    for (i = 0; i < n2; i++) {
        memcpy(count, previous, (n1 + 1) * sizeof (int));
        for (j = 0; j < n1; j++) {
            count[j + 1] = MAX(count[j], previous[j + 1]);
            count[j + 1] = MAX(count[j + 1], previous[j] + (s2[i] == s1[j] ? 1 : 0));
        }
        memcpy(previous, count, (n1 + 1) * sizeof (int));
    }
    return count[n1];
}

/* Main function */
#define READ(x)     (fgets(x, MAX_STRING, stdin) != NULL)
int main() {
    char s1[MAX_STRING], s2[MAX_STRING];
    while (READ(s1) && READ(s2)) {
        printf("%d\n", lcs(s1, s2));
    }
    return 0;
}
