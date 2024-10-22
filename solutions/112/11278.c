/* 11278
 * One-Handed Typist
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

char querty[] = "1234567890-=!@#$%^&*()_+"
                "qwertyuiop[]QWERTYUIOP{}"
                "asdfghjkl;'ASDFGHJKL:\""
                "zxcvbnm,./ZXCVBNM<>?";
char dvorak[] = "123qjlmfp/[]!@#QJLMFP?{}"
                "456.orsuyb;=$%^>ORSUYB:+"
                "789aehtdck-&*(AEHTDCK_"
                "0zx,inwvg')ZX<INWVG\"";

/* Main function */
int main() {
    char symbol, *loc;
    while (scanf("%c", &symbol) != EOF) {
        loc = strchr(querty, symbol);
        printf("%c", loc == NULL ? symbol : dvorak[loc - querty]);
    }
    return EXIT_SUCCESS;
}
