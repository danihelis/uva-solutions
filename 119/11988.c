/* 11988
 * Broken Keyboard (a.k.a. Beiju Text)
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

typedef struct char_s {
    char letter;
    struct char_s *next;
} char_t;

char_t head, *tail, *current;

/* Init list */
void init() {
    head.next = NULL;
    current = &head;
    tail = &head;
}

/* Insert after current */
void insert(char letter) {
    char_t *new = (char_t *) malloc(sizeof (char_t));
    new->letter = letter;
    new->next = current->next;
    current->next = new;
    if (tail == current) {
        tail = new;
    }
    current = new;
}

/* Print and erase list */
void print_and_erase() {
    char_t *node, *delete;
    node = head.next;
    while (node != NULL) {
        printf("%c", node->letter);
        delete = node;
        node = node->next;
        free(delete);
    }
    printf("\n");
}

/* Main function */
int main() {
    char letter;
    init();
    while (scanf("%c", &letter) != EOF) {
        switch (letter) {
            case '\n':
                print_and_erase();
                init();
                break;
            case '[':
                current = &head;
                break;
            case ']':
                current = tail;
                break;
            default:
                insert(letter);
        }
    }
    return 0;
}
