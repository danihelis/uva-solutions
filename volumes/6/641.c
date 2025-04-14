/* 641
 * Do the Untwist
 * By Johan Schreiber
 */
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE        70
#define MAX_STRING      (MAX_SIZE + 2)
#define MAX_CODES       28
#define ORD(x)          ((x) == '_' ? 0 : (x) == '.' ? 27 : (x) + 1 - 'a')
#define CHR(x)          ((x) == 0 ? '_' : (x) == 27 ? '.' : (x) - 1 + 'a')

/* Main function */
int main() {
    char cipher[MAX_STRING];
    int code[MAX_SIZE], plain[MAX_SIZE];
    int i, k, n;
    while (scanf("%d", &k) == 1 && k) {
        assert(scanf(" %s", cipher) == 1);
        n = strlen(cipher);
        for (i = 0; i < n; i++) {
            code[i] = ORD(cipher[i]);
        }
        for (i = 0; i < n; i++) {
            plain[(k * i) % n] = (code[i] + i) % MAX_CODES;
        }
        for (i = 0; i < n; i++) {
            printf("%c", CHR(plain[i]));
        }
        printf("\n");
    }
    return EXIT_SUCCESS;
}
