/* 325
 * Identifying Legal Pascal Real Constants
 * by Daniel Donadon
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
    char input[MAX_STRING];
    while (scanf("%[^\n] ", input) != EOF && strcmp(input, "*") != 0) {
        char *entry, *trail, *s;
        int valid, state, before, after, dot, expo;
        for (entry = input; *entry == ' '; entry++)
            ;
        for (trail = entry + strlen(entry) - 1; 
                trail >= entry && *trail == ' '; trail--)
            *trail = 0;
        valid = 1, state = 0, s = entry; 
        before = after = dot = expo = 0;
        while (valid && *s != 0) {
            switch (state) {
                case 0: 
                case 10:
                    if (isdigit(*s))
                        state++;
                    else {
                        valid = *s == '+' || *s == '-';
                        state++, s++;
                    }
                    break;
                case 1: 
                    if (isdigit(*s))
                        (dot > 0 ? after++ : before++), s++;
                    else if (*s == '.') {
                        valid = before > 0 && dot == 0;
                        dot++, s++;
                    }
                    else if (*s == 'e' || *s == 'E') {
                        valid = before > 0 && (dot == 0 || after > 0);
                        state = 10, s++, expo++;
                        before = after = dot = 0;
                    }
                    else
                        valid = 0;
                    break;
                case 11:
                    if (isdigit(*s))
                        s++, before++;
                    else
                        valid = 0;
                    break;
                default:
                    assert(NULL);
            }
        }
        valid &= before > 0 && ((dot == 0 && expo > 0) || after > 0);
        printf("%s is %s.\n", entry, valid ? "legal" : "illegal");
    }
    return EXIT_SUCCESS;
}
