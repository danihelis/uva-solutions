/* 12700
 * Banglawash
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

/* Main function */
int main() {
    int test, num_tests;
    assert(scanf("%d", &num_tests) == 1);
    for (test = 1; test <= num_tests; test++) {
        int i, games, wins, draws, loses;
        assert(scanf("%d ", &games) == 1);
        for (i = wins = loses = draws = 0; i < games; i++) {
            char res;
            assert(scanf("%c", &res) == 1);
            wins += res == 'B' ? 1 : 0;
            loses += res == 'W' ? 1 : 0;
            draws += res == 'T' ? 1 : 0;
        }
        printf("Case %d: %s", test, 
                wins == 0 && loses == 0 && draws == 0 ? "ABANDONED" :
                wins == 0 && draws == 0 ? "WHITEWASH" : 
                loses == 0 && draws == 0 ? "BANGLAWASH" :
                wins == loses ? "DRAW" : 
                wins > loses ? "BANGLADESH" : "WWW");
        if (wins == loses && (draws > 0 || wins > 0))
            printf(" %d %d", wins, draws);
        else if (draws > 0 || (wins > 0 && loses > 0))
            printf(" %d - %d", wins > loses ? wins : loses,
                    wins < loses ? wins : loses);
        printf("\n");
    }
    return EXIT_SUCCESS;
}
