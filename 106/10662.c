/* 10662
 * The Wedding
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIMENSION   20

#define READ(cost,pair,rows,cols)   do { \
        int i, j; \
        for (i = 0; i < (rows); i++) { \
            assert(scanf("%d", &(cost)[i]) != EOF); \
            for (j = 0; j < cols; j++) \
                assert(scanf("%d", &(pair)[i][j]) != EOF); \
        } \
    } while (0)

int travel[MAX_DIMENSION], restaurant[MAX_DIMENSION], hotel[MAX_DIMENSION];
int travel_restaurant[MAX_DIMENSION][MAX_DIMENSION],
     restaurant_hotel[MAX_DIMENSION][MAX_DIMENSION],
     hotel_travel[MAX_DIMENSION][MAX_DIMENSION];
int num_travels, num_restaurants, num_hotels;

/* Main function */
int main() {
    while (scanf("%d %d %d", &num_travels, &num_restaurants, &num_hotels) != EOF) {
        int t, r, h, sum, minimum = -1, best_t, best_r, best_h;
        READ(travel, travel_restaurant, num_travels, num_restaurants);
        READ(restaurant, restaurant_hotel, num_restaurants, num_hotels);
        READ(hotel, hotel_travel, num_hotels, num_travels);
        for (t = 0; t < num_travels; t++) {
            for (r = 0; r < num_restaurants; r++) {
                if (travel_restaurant[t][r] == 0) {
                    for (h = 0; h < num_hotels; h++) {
                        if (restaurant_hotel[r][h] == 0 && hotel_travel[h][t] == 0) {
                            sum = travel[t] + restaurant[r] + hotel[h];
                            if (minimum == -1 || sum < minimum) {
                                minimum = sum;
                                best_t = t;
                                best_r = r;
                                best_h = h;
                            }
                        }
                    }
                }
            }
        }
        if (minimum == -1) {
            printf("Don't get married!\n");
        }
        else {
            printf("%d %d %d:%d\n", best_t, best_r, best_h, minimum);
        }       
    }
    return 0;
}
