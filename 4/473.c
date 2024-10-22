/* 473
 * Raucous Rockers
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_TIME 200
#define MAX_SONGS 800

#define MAX(x, y) ((x) > (y) ? (x) : (y))

typedef int bag_t[MAX_SONGS][MAX_TIME];

int song[MAX_SONGS];
int num_songs;

int maximize_number_songs(int bags, int time) {
    bag_t previous, current;
    int i, b, t;
    memset(current, 0, MAX_TIME * num_songs * sizeof (int));
    for (b = 0; b < bags; b++) {
        memcpy(previous, current, MAX_TIME * num_songs * sizeof (int));
        for (i = num_songs - 1; i >= 0; i--) {
            for (t = 0; t <= time; t++) {
                int put = (song[i] <= t ? 1 + (i < num_songs - 1 ? 
                            current[i + 1][t - song[i]] : 0) : 0);
                int open = (i < num_songs - 1 ? current[i + 1][t] : 0);
                int close = previous[i][time];
                int best = MAX(put, open);
                best = MAX(best, close);
                current[i][t] = best;
            }
        }
    }
    return current[0][time];
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        int i, num_bags, time_limit;
        assert(scanf("%d %d %d", &num_songs, &time_limit, &num_bags) != EOF);
        assert(time_limit < MAX_TIME && num_songs <= MAX_SONGS);
        for (i = 0; i < num_songs - 1; i++) {
            assert(scanf("%d,", &song[i]) != EOF);
        }
        assert(scanf("%d", &song[i]) != EOF);
        printf("%d%s\n", maximize_number_songs(num_bags, time_limit), (num_tests > 1 ? "\n" : ""));
    }
    return 0;
}
