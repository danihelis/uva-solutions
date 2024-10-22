/* 762
 * We Ship Cheap
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define NUM_CODES   26
#define MAX_CITIES  (NUM_CODES * NUM_CODES)
#define MAX_STRING  4
#define ORIGIN      -1

typedef struct node_s {
    int link[MAX_CITIES];
    int num_links, arrival, visited;
} node_t, *node_p;

node_t city[MAX_CITIES];

#define ENCODE(x)       printf("%c%c", (x) / NUM_CODES + 'A', ((x) % NUM_CODES) + 'A')
#define DECODE(v, s)    (v) = ((s)[0] - 'A') * NUM_CODES + (s)[1] - 'A'
#define ADD_EDGE(a, b)  city[a].link[city[a].num_links++] = (b)

/* Find minimum path to reach origin from destiny (yes, in reverse order) */
int find_path(int origin, int destiny) {
    node_p current, queue[MAX_CITIES];
    int i, front, end;

    city[destiny].visited = 1, city[destiny].arrival = -1;
    queue[0] = &city[destiny];
    front = 0, end = 1;
    while (front < end) {
        current = queue[front++];
        if (current - city == origin) {
            return 1;
        }
        for (i = 0; i < current->num_links; i++) {
            node_p next = &city[current->link[i]];
            if (!next->visited) {
                next->visited = 1;
                next->arrival = current - city;
                queue[end++] = next;
            }
        }
    }
    return 0;
}


/* Print minimum path */
void print_path(int origin) {
    while (city[origin].arrival != -1) {
        ENCODE(origin);
        printf(" ");
        origin = city[origin].arrival;
        ENCODE(origin);
        printf("\n");
    }
}

/* Main function */
int main() {
    int n, first = 1;
    while (scanf(" %d", &n) != EOF) {
        char a[MAX_STRING], b[MAX_STRING];
        (first ? (void) (first = 0) : (void) printf("\n"));
        memset(city, 0, MAX_CITIES * sizeof (node_t));
        for (; n >= 0; n--) {
            int va, vb;
            assert(scanf(" %s %s", a, b) != EOF);
            DECODE(va, a);
            DECODE(vb, b);
            if (n > 0) {
                ADD_EDGE(va, vb);
                ADD_EDGE(vb, va);
            }
            else if (find_path(va, vb)) {
                print_path(va);
            }
            else {
                printf("No route\n");
            }
        }
    }
    return 0;
}
