/* 11212
 * Editing a Book
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_HASH    999983
#define MAX_QUEUE   365000
#define MAX_N       9
#define UNDEFINED   -1

typedef struct {
    int number;
    char cost;
} elem_t;

typedef struct {
    elem_t *elem[MAX_QUEUE];
    int front, rear;
} queue_t;

elem_t *hash[MAX_N], *cur_hash;
queue_t queue[MAX_N], *cur_queue;
int n, goal;

/* Return hash element for a given number sequence */
elem_t * get_hash(int number) {
    int index = number % MAX_HASH;
    elem_t *elem;
    while (cur_hash[index].number > 0 && cur_hash[index].number != number) {
        index = (index + 2) % MAX_HASH;
    }
    elem = &cur_hash[index];
    if (elem->number == 0) elem->number = number, elem->cost = UNDEFINED;
    return elem;
}

/* Process next number from the queue */
int process_queue() {
    int i, start, length, prefix_size, length_size, suffix_size;
    elem_t *elem, *cur_elem = cur_queue->elem[cur_queue->front++];
    int number = cur_elem->number, result = UNDEFINED;
    for (start = 0, prefix_size = 1; start < n - 1; 
            start++, prefix_size *= 10) {
        int prefix = number % prefix_size;
        int remain = number / prefix_size;
        for (length = 1, length_size = 10; start + length < n;
                length++, length_size *= 10) {
            int infix = remain % length_size;
            int suffix = remain / length_size;
            for (i = start + length, suffix_size = 10; i < n; 
                    i++, suffix_size *= 10) {
                int next, comb = suffix % suffix_size;
                comb += infix * suffix_size;
                comb += (suffix / suffix_size) * (suffix_size * length_size);
                next = prefix + comb * prefix_size;
                elem = get_hash(next);
                if (elem->cost == UNDEFINED) {
                    elem->cost = cur_elem->cost + 1;
                    if (next == goal) result = elem->cost;
                    cur_queue->elem[cur_queue->rear++] = elem;
                }
            }
        }
    }
    return result;
}

/* Find goal's cost */
int find_goal() {
    int value;
    elem_t *elem = get_hash(goal);
    if (elem->cost != UNDEFINED) return elem->cost;
    do {
        value = process_queue();
    } while (value == UNDEFINED);
    return value;
}

/* Init structures */
void init() {
    int i, number;
    elem_t *elem;
    for (i = 2, number = 1; i <= MAX_N; i++) {
        number = number * 10 + i;
        hash[i - 1] = (elem_t *) calloc(MAX_HASH, sizeof (elem_t));
        cur_hash = hash[i - 1];
        elem = get_hash(number);
        elem->cost = 0;
        cur_queue = &queue[i - 1];
        cur_queue->front = 0, cur_queue->rear = 1, cur_queue->elem[0] = elem;
    }
}

/* Main function */
int main() {
    int i, test = 0;
    init();
    while (scanf("%d", &n) == 1 && n > 0) {
        int digit;
        for (i = goal = 0; i < n; i++) {
            assert(scanf("%d", &digit) == 1);
            goal = goal * 10 + digit;
        }
        cur_hash = hash[n - 1];
        cur_queue = &queue[n - 1];
        printf("Case %d: %d\n", ++test, find_goal());
    }
    return EXIT_SUCCESS;
}
