/* 573
 * The Snail
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
    int well, down, fatigue_factor, day, success;
    double height, fatigue, climb;
    while (scanf("%d %lf %d %d", &well, &climb, &down, &fatigue_factor) != EOF) {
        if (well == 0) {
            break;
        }
        day = 1;
        success = 0;
        fatigue = climb * fatigue_factor / 100.0;
        height = 0.0;
        while (1) {
            height += climb;
            climb -= fatigue;
            if (climb < 0) {
                climb = 0;
            }
            if (height > well) {
                success = 1;
                break;
            }
            height -= down;
            if (height < 0) {
                break;
            }
            day++;
        }
        printf("%s on day %d\n", (success ? "success" : "failure"), day);        
    }
    return 0;
}
