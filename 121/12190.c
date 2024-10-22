/* 12190
 * Electric Bill
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_RANGES  5
#define MIN(a,b)    ((a) < (b) ? (a) : (b))

const long LIMIT[MAX_RANGES] = {0, 100, 10000, 1000000, 1 << 30},
           PRICE[MAX_RANGES] = {0, 2, 3, 5, 7};

/* Convert watt into price */
long watt_into_price(long watt) {
    int i;
    long cost, charged;
    for (i = 1, cost = charged = 0; charged < watt && i < MAX_RANGES; i++) {
        long amount = MIN(LIMIT[i], watt) - LIMIT[i - 1];
        cost += amount * PRICE[i];
        charged += amount;
    }
    return cost;
}

/* Convert price into watt */
long price_into_watt(long price) {
    int i;
    long watt;
    for (i = 1, watt = 0; price > 0 && i < MAX_RANGES; i++) {
        long ceil = (price + PRICE[i] - 1) / PRICE[i];
        long amount = MIN(ceil, LIMIT[i] - LIMIT[i - 1]);
        watt += amount;
        price -= amount * PRICE[i];
    }
    return watt;
}

/* Binary search the answer */
long binary_search(long total, long difference) {
    long start = 0, end = total / 4;
    while (start < end) {
        long watt = (start + end) / 2;
        long cost = watt_into_price(watt);
        long total_watt = watt + price_into_watt(cost + difference);
        long middle = watt_into_price(total_watt);
        /*
        fprintf(stderr, "S=%ld E=%ld -- W=%ld C=%ld TW=%ld -- TC=%ld <> %ld\n",
                start, end, watt, cost, total_watt, middle, total);
        */
        if (middle == total) return cost;
        if (middle < total) start = watt + 1;
        else end = watt;
    }
    return watt_into_price(start);
}

/* Main function */
int main() {
    long total, difference;
    while (scanf("%ld %ld", &total, &difference) == 2 && total > 0) {
        printf("%ld\n", binary_search(total, difference));
    }
    return EXIT_SUCCESS;
}
