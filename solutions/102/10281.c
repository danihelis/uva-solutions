/* 10281
 * Average Speed
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_INPUT 100

typedef struct {
    int hour, minute, second;
} timestamp_t;

/* Main function */
int main() {
    char line[MAX_INPUT];
    int speed = 0;
    timestamp_t time = {0, 0, 0};
    double distance = 0;

    while (fgets(line, MAX_INPUT, stdin) != NULL) {
        timestamp_t now, input_time;
        int new_speed;
        int time_elapsed;
        int read = sscanf(line, "%d:%d:%d %d", &now.hour, &now.minute, &now.second, &new_speed);
        assert(read >= 3);
        input_time = now;
        if (now.second < time.second) {
            now.second += 60;
            now.minute--;
        }
        if (now.minute < time.minute) {
            now.minute += 60;
            now.hour--;
        }
        time_elapsed = (now.second - time.second) + (now.minute - time.minute) * 60 + 
                (now.hour - time.hour) * 3600;
        distance += time_elapsed * speed / 3600.0;
        time = input_time;
        if (read == 3) {
            printf("%02d:%02d:%02d %.2f km\n", input_time.hour, input_time.minute, input_time.second,
                    distance);
        }
        else {
            speed = new_speed;
        }
    }
    return 0;
}
