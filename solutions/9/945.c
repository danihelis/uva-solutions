/* 945
 * Loading a Cargo Ship
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_CONTAINERS      9
#define MAX_ITEMS           1000

typedef struct {
    char stack[MAX_ITEMS];
    int size, weight;
} container_t;

/* Main function */
int main() {
    int num_conts, first = 1;
    while (scanf("%d", &num_conts) != EOF) {
        container_t container[MAX_CONTAINERS], *c, *b;
        int i, pack, num_packages, sum, unloaded, accepting, unused, maxsize;
        for (i = 0; i < num_conts; i++) {
            c = &container[i];
            assert(scanf("%d", &c->weight) == 1);
            c->size = 0;
        }
        assert(scanf("%d", &num_packages) == 1);
        for (accepting = 1, sum = unloaded = 0; num_packages > 0; 
                num_packages--) {
            assert(scanf("%d", &pack) == 1);
            if (!accepting)
                unloaded += pack;
            else {
                for (b = &container[0], i = 1; i < num_conts; i++) {
                    c = &container[i];
                    if (c->size < b->size || (c->size == b->size &&
                                c->weight > b->weight))
                        b = c;
                }
                if (b->weight >= pack) {
                    b->stack[b->size++] = pack;
                    b->weight -= pack, sum += pack;
                }
                else
                    accepting = 0, unloaded += pack;
            }
        }
        for (i = unused = maxsize = 0; i < num_conts; i++) {
            c = &container[i];
            unused += c->weight;
            maxsize = c->size > maxsize ? c->size : maxsize;
        }
        (first ? (first = 0) : printf("\n"));
        for (maxsize--; maxsize >= 0; maxsize--)
            for (i = 0; i < num_conts; i++) {
                c = &container[i];
                printf("%c%s", maxsize < c->size ? 
                        c->stack[maxsize] + '0' : ':', 
                        i == num_conts - 1 ? "\n" : " ");
            }
        for (i = 1; i < 2 * num_conts; i++)
            printf("=");
        printf("\n");
        for (i = 0; i < num_conts; i++)
            printf("%d%s", i + 1, i == num_conts - 1 ? "\n" : " ");
        printf("\n");
        printf("cargo weight: %d\nunused weight: %d\nunloaded weight: %d\n",
                sum, unused, unloaded);
    }
    return EXIT_SUCCESS;
}
