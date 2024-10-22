/* 535
 * Globetrotter
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define RADIUS          6378
#define MAX_NAME        40
#define MAX_LOCATIONS   100

#define RAD(x)          ((x) / 90.0 * acos(0))

typedef struct {
    char name[MAX_NAME];
    double x, y, z;
} loc_t;

loc_t locations[MAX_LOCATIONS];
loc_t *list[MAX_LOCATIONS];
int num_locations;

/* Compute the cartesian coordinates from spherical coordinates */
void into_cartesian(loc_t *loc, double lat, double lon) {
    double theta = RAD(lat + 90.0), phi = RAD(lon + 180.0);
    loc->x = sin(theta) * sin(phi);
    loc->y = sin(theta) * cos(phi);
    loc->z = cos(theta);
}

/* Insert new location */
loc_t * insert_search(char *name, int should_insert) {
    int start = 0, end = num_locations;
    while (start < end) {
        int middle = (start + end) / 2;
        int comp = strcmp(name, list[middle]->name);
        if (comp == 0)
            return list[middle];
        else if (comp < 0)
            end = middle;
        else
            start = middle + 1;
    }
    if (!should_insert)
        return NULL;
    for (end = num_locations; end > start; end--) 
        list[end] = list[end - 1];
    list[start] = &locations[num_locations];
    strcpy(locations[num_locations++].name, name);
    return list[start];
}

/* Return the spherical distance between two coordinates */
int get_distance(loc_t *a, loc_t *b) {
    if (a == b)
        return 0;
    else {
        double cosine = a->x * b->x + a->y * b->y + a->z * b->z;
        double distance = acos(cosine) * RADIUS;
        int fdist = floor(distance);
        return fdist + (distance - fdist > 0.5 ? 1 : 0);
    }
}

/* Main function */
#define MAX_LINE    100
#define READ(x)     (fgets(x, MAX_LINE, stdin) != NULL)
int main() {
    char line[MAX_LINE];
    num_locations = 0;
    while (READ(line) && line[0] != '#') {
        char name[MAX_NAME];
        double lat, lon;
        loc_t *loc;
        assert(sscanf(line, "%s %lf %lf", name, &lat, &lon) == 3);
        loc = insert_search(name, 1);
        into_cartesian(loc, lat, lon);
    }

    while (READ(line) && line[0] != '#') {
        char a[MAX_NAME], b[MAX_NAME];
        loc_t *la, *lb;
        assert(sscanf(line, "%s %s", a, b) == 2);
        printf("%s - %s\n", a, b);
        la = insert_search(a, 0);
        lb = insert_search(b, 0);
        if (la != NULL && lb != NULL)
            printf("%d km\n", get_distance(la, lb));
        else
            printf("Unknown\n");
    }
    return EXIT_SUCCESS;
}
