/* 1056
 * Degrees of Separation
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       50
#define INFINITY    (MAX_N + 1)
#define MAX_STRING  200

typedef struct {
    char name[MAX_STRING];
    int index;
} person_t;

person_t person[MAX_N], *book[MAX_N];
int distance[MAX_N][MAX_N], n, num_people;

/* Find or insert */
person_t * find_insert(char *name) {
    int start = 0, end = num_people;
    while (start < end) {
        int middle = (start + end) / 2;
        int cmp = strcmp(name, book[middle]->name);
        if (cmp == 0)
            return book[middle];
        else if (cmp < 0)
            end = middle;
        else
            start = middle + 1;
    }
    for (end = num_people; end > start; end--)
        book[end] = book[end - 1];
    strcpy(person[num_people].name, name);
    person[num_people].index = num_people;
    book[start] = &person[num_people++];
    return book[start];
}

/* Compute all distances using Floyd-Marshall's and return largest */
int compute_distances() {
    int i, j, k, largest;
    for (k = 0; k < n; k++)
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++) {
                int cut = distance[i][k] + distance[k][j];
                if (cut < distance[i][j])
                    distance[i][j] = cut;
            }
    for (i = 0, largest = 0; i < n; i++)
        for (j = i + 1; j < n; j++)
            if (distance[i][j] > largest)
                largest = distance[i][j];
    return largest;
}

/* Main function */
int main() {
    int i, j, r, net = 0;
    while (scanf("%d %d", &n, &r) != EOF && n > 0) {
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                distance[i][j] = i == j ? 0 : INFINITY;
        for (num_people = 0; r > 0; r--) {
            char n1[MAX_STRING], n2[MAX_STRING];
            person_t *p1, *p2;
            assert(scanf(" %s %s", n1, n2) != EOF);
            p1 = find_insert(n1);
            p2 = find_insert(n2);
            distance[p1->index][p2->index] = 1;
            distance[p2->index][p1->index] = 1;
        }
        r = compute_distances();
        printf("Network %d: ", ++net);
        (r == INFINITY ? printf("DISCONNECTED\n\n") : printf("%d\n\n", r));
    }
    return EXIT_SUCCESS;
}
