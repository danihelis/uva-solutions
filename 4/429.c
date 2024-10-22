/* 429
 * Word Transformation
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  15
#define MAX_LINE    (MAX_STRING * 3)
#define MAX_WORDS   200
#define INFINITY    (1 << 30)
#define READ(x)     (fgets(x, MAX_LINE, stdin) != NULL)

typedef struct word_s {
    char word[MAX_STRING];
    struct word_s *next[MAX_WORDS];
    int num_next, distance, visited, queued;
} word_t;

word_t word[MAX_WORDS], *dict[MAX_WORDS];
int size;

/* Compare two word_t pointers */
int compare(const void *a, const void *b) {
    word_t *x = * (word_t **) a, *y = * (word_t **) b;
    return strcmp(x->word, y->word);
}

/* Is word close? */
int is_close(char *a, char *b) {
    int diff = 0;
    while (diff <= 1 && (*a != 0 || *b != 0)) {
        if (*a == 0)
            diff++, b++;
        else if (*b == 0)
            diff++, a++;
        else
            diff += (*(a++) == *(b++) ? 0 : 1);
    }
    return diff == 1;
}

/* Find shortest path */
int shortest_path(word_t *s, word_t *t) {
    word_t *queue[MAX_WORDS];
    int i, best, front, rear;

    for (i = 0; i < size; i++) {
        word_t *w = dict[i];
        w->distance = INFINITY; 
        w->visited = w->queued = 0;
    }
    queue[0] = s, front = 0, rear = 1;
    s->distance = 0;
    while (front < rear) {
        word_t *w = queue[front++];
        if (w == t)
            return w->distance;
        w->visited = 1;
        for (i = 0; i < w->num_next; i++) {
            word_t *n = w->next[i];
            if (!n->visited && n->distance > w->distance + 1) {
                n->distance = w->distance + 1;
                if (!n->queued)
                    queue[rear++] = n, n->queued = 1;
            }
        }
        for (best = front, i = front + 1; i < rear; i++)
            if (queue[i]->distance < queue[best]->distance)
                best = i;
        if (best != front) {
            word_t *swap = queue[best];
            queue[best] = queue[front];
            queue[front] = swap;
        }
    }
    return INFINITY;
}

/* Main function */
int main() {
    int num_tests, first, i;
    char line[MAX_LINE];
    assert(READ(line) && sscanf(line, "%d", &num_tests) == 1);
    for (first = 1; num_tests > 0; num_tests--) {
        if (first) {
            assert(READ(line) && line[0] == '\n');
            first = 0;
        }
        else
            printf("\n");
        size = 0;
        while (READ(line) && line[0] != '*') {
            word_t *w = &word[size];
            line[strlen(line) - 1] = 0;
            strcpy(w->word, line);
            w->num_next = 0;
            for (i = 0; i < size; i++) {
                word_t *n = &word[i];
                if (is_close(w->word, n->word)) {
                    w->next[w->num_next++] = n;
                    n->next[n->num_next++] = w;
                }
            }
            dict[size++] = w;
        }
        qsort(dict, size, sizeof (word_t *), compare);
        while (READ(line) && line[0] != '\n') {
            word_t w1, w2, *p1, *p2;
            assert(sscanf(line, "%s %s", w1.word, w2.word) == 2);
            for (i = 0; i < 2; i++) {
                word_t *key = (i == 0 ? &w1 : &w2), **pos;
                pos = bsearch(&key, dict, size, sizeof (word_t *), compare);
                (i == 0 ? (p1 = *pos) : (p2 = *pos));
            }
            printf("%s %s %d\n", p1->word, p2->word, shortest_path(p1, p2));
        }
    }
    return EXIT_SUCCESS;
}
