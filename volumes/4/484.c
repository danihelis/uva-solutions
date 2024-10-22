/* 484
 * The Department of Redundancy Department
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define HASH_SIZE   999983

typedef struct count_s {
    struct count_s *next;
    int number, total;
} count_t, *count_p;

typedef struct node_s {
    struct node_s *next;
    count_p count;
} node_t, *node_p;

node_p hashtable[HASH_SIZE];
count_p list, *list_rear;

/* Insert new node on the list */
void insert(int n, int key) {
    node_p node = (node_p) malloc(sizeof (node_t));
    count_p count = (count_p) malloc(sizeof (count_t));
    
    count->number = n, count->total = 1, count->next = NULL;
    *list_rear = count;
    list_rear = &count->next;

    node->count = count, node->next = hashtable[key];
    hashtable[key] = node;
}

/* Search for number on hashtable and sum one to counter */
void count(int n) {
    int key = (n > 0 ? n : -n) % HASH_SIZE;
    node_p node;
    for (node = hashtable[key]; node != NULL && node->count->number != n; node = node->next)
        ;
    if (node == NULL) {
        insert(n, key);
    }
    else {
        node->count->total++;
    }
}

/* Print list of numbers */
void print_list() {
    count_p count;
    for (count = list; count != NULL; count = count->next) {
        printf("%d %d\n", count->number, count->total);
    }
}

/* Main function */
int main() {
    int number;
    memset(hashtable, 0, sizeof (node_p) * HASH_SIZE);
    list = NULL, list_rear = &list;
    while (scanf("%d", &number) != EOF) {
        count(number);
    }
    print_list(); 
    return 0;
}
