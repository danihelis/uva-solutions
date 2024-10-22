/* 661
 * Blowing Fuses
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DEVICES 20

/* Main function */
int main() {
    char on[MAX_DEVICES];
    int capacity[MAX_DEVICES];
    int num_devices, power, max_power, fuse, num_entries, num_tests, i;

    num_tests = 0;
    while (scanf("%d %d %d", &num_devices, &num_entries, &fuse) != EOF) {
        if (num_devices == 0) {
            break;
        }

        num_tests++;
        for (i = 0; i < num_devices; i++) {
            assert(scanf("%d", &capacity[i]) != EOF);
            on[i] = 0;
        }
        
        max_power = 0;
        power = 0;
        for (i = 0; i < num_entries; i++) {
            int device;
            assert(scanf("%d", &device) != EOF);
            device--;
            if (on[device]) {
                on[device] = 0;
                power -= capacity[device];
            }
            else {
                on[device] = 1;
                power += capacity[device];
                if (power > max_power) {
                    max_power = power;
                }
            }
        }
        printf("Sequence %d\nFuse was %sblown.\n", num_tests, (max_power > fuse ? "" : "not "));
        if (max_power <= fuse) {
            printf("Maximal power consumption was %d amperes.\n", max_power);
        }
        printf("\n");
    }
    return 0;
}
