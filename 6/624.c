/* 624
 * CD
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_TRACKS  20

int tracK_length[MAX_TRACKS], sequence[MAX_TRACKS];
char used[MAX_TRACKS];
int best_sequence[MAX_TRACKS], best_size, best_length;
int num_tracks, tape_space;

/* Try to complete the tape with the best sequence of CD tracks */
void complete_tape(int track, int position, int length) {
    for (; track < num_tracks; track++) {
        if (!used[track]) {
            int new_length = tracK_length[track] + length;
            if (new_length <= tape_space) {
                used[track] = 1, sequence[position] = tracK_length[track];
                if (new_length > best_length) {
                    best_length = new_length;
                    best_size = position + 1;
                    memcpy(best_sequence, sequence, best_size * sizeof (int));
                }
                complete_tape(track + 1, position + 1, new_length);
                used[track] = 0;
            }
        }
    }
}

/* Main function */
int main() {
    while (scanf("%d %d", &tape_space, &num_tracks) != EOF) {
        int i;
        for (i = 0; i < num_tracks; i++) {
            assert(scanf("%d", &tracK_length[i]) != EOF);
        }
        best_length = 0;
        complete_tape(0, 0, 0);
        assert(best_length > 0);
        for (i = 0; i < best_size; i++) {
            printf("%d ", best_sequence[i]);
        }
        printf("sum:%d\n", best_length);
    }
    return 0;
}
