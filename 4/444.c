/* 444
 * Encoder and Decoder
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  1000

/* Main function */
int main() {
    char string[MAX_STRING];
    while (fgets(string, MAX_STRING, stdin) != NULL) {
        int encode = !isdigit(string[0]);
        char *p = string + strlen(string) - 2; 
        while (p >= string) {
            if (encode) {
                int code = *p;
                while (code > 0) {
                    printf("%d", code % 10);
                    code /= 10;
                }
                p--;
            }
            else {
                char code = 0;
                while (code < ' ') {
                    code = code * 10 + *p - '0';
                    p--;
                }
                printf("%c", code);
            }
        }
        printf("\n");
    }
    return 0;
}
