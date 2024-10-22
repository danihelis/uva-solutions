/* 11060
 * Beverages
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_VERTICES    101
#define MAX_NAME        52

#define PARENT(x)   (((x) - 1) / 2)
#define CHILD(x)    ((x) * 2 + 1)
#define SWAP(x, y)  do { \
        vertex_t *swap = heap[x]; \
        heap[x] = heap[y]; \
        heap[y] = swap; \
    } while (0)


typedef struct vertex_s {
    char name[MAX_NAME];
    struct vertex_s *allows[MAX_VERTICES];
    int num_allows, num_depends, satisfied;
} vertex_t;

vertex_t vertices[MAX_VERTICES], 
         *ptr_vertices[MAX_VERTICES],
         *heap[MAX_VERTICES];
int num_vertices, size;

/* Compare two vertex pointers by name */
int compare_name(const void *a, const void *b) {
    return strcmp((* (vertex_t **) a)->name, (* (vertex_t **) b)->name);
}

/* Insert into heap */
void insert(vertex_t *v) {
    int index = size++;
    heap[index] = v;
    while (index > 0 && heap[PARENT(index)] > heap[index]) {
        SWAP(index, PARENT(index));
        index = PARENT(index);
    }    
}

/* Remove minimum from heap */
vertex_t * remove_minimum() {
    vertex_t *minimum = heap[0];
    int index = 0;
    heap[0] = heap[--size];
    while (CHILD(index) < size) {
        int child = CHILD(index);
        if (child + 1 < size && heap[child] > heap[child + 1])
            child++;
        if (heap[child] < heap[index]) {
            SWAP(index, child);
            index = child;
        } else 
            break;
    }
    return minimum;
}

/* Main function */
int main() {
    int test_number = 0;

    while (scanf("%d", &num_vertices) != EOF) {
        int i, num_edges;
        printf("Case #%d: Dilbert should drink beverages in this order:", 
                ++test_number);

        for (i = 0; i < num_vertices; i++) {
            vertex_t *v = &vertices[i];
            assert(scanf(" %s", v->name) != EOF);
            v->num_allows = v->num_depends = v->satisfied = 0;
            ptr_vertices[i] = v;
        }
        qsort(ptr_vertices, num_vertices, sizeof (vertex_t *), compare_name);
        
        assert(scanf("%d", &num_edges) != EOF);
        for (i = 0; i < num_edges; i++) {
            vertex_t k1, k2;
            vertex_t *kp1 = &k1, *kp2 = &k2, **v1, **v2;
            assert(scanf(" %s %s", k1.name, k2.name) != EOF);
            v1 = bsearch(&kp1, ptr_vertices, num_vertices, 
                    sizeof (vertex_t *), compare_name);
            v2 = bsearch(&kp2, ptr_vertices, num_vertices, 
                    sizeof (vertex_t *), compare_name);
            assert(v1 != NULL && v2 != NULL);
            (*v1)->allows[(*v1)->num_allows++] = *v2;
            (*v2)->num_depends++;
        }

        size = 0;
        for (i = 0; i < num_vertices; i++) {
            vertex_t *v = &vertices[i];
            if (v->satisfied == v->num_depends) /* == 0 */
                insert(v);
        }
        while (size > 0) {
            vertex_t *v = remove_minimum();
            printf(" %s", v->name);
            for (i = 0; i < v->num_allows; i++) {
                vertex_t *n = v->allows[i];
                n->satisfied++;
                if (n->satisfied == n->num_depends)
                    insert(n);
            }
        }        
        printf(".\n\n");
    }
    return EXIT_SUCCESS;
}
