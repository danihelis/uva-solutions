/**
 * 130
 * Roman Roulette
 * by Daniel Donadon
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PEOPLE 100

/* Does the first person (me) survive when starting in i-th position? */
int do_I_live(int n, int k, int i) {
    int digger, dead, my_position;

    my_position = 0;
    dead = (n + i - 1) % n;
    while (n > 1) {
        dead = (dead + k) % n;
        if (dead == my_position) {
            return 0;
        }
        else if (my_position > dead) {
            my_position--;
        }
        n--;
        digger = (dead - 1 + k) % n;
        if (digger < dead) {
            dead--;
        }
        if (digger == my_position) {
            my_position = dead;
        }
        else if (my_position > digger && my_position <= dead) {
            my_position--;
        }
        else if (my_position < digger && my_position >= dead) {
            my_position++;
        }
    }
    return 1;
}


/* Get the best position by brute force */
int get_safe_start(int n, int k) {
    int start;
    for (start = 0; start < n - 1; start++) {
        if (do_I_live(n, k, start)) {
            return start + 1;
        }
    }
    return n;
}


/* Main */
int main() {
    int n, k, position;

    while (scanf("%d %d", &n, &k) == 2) {
        if (n == 0) {
            break;
        }
        position = get_safe_start(n, k);
        printf("%d\n", position);
    }
    return 0;
}

