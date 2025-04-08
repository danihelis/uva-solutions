/* 188
 * Perfect Hash
 * By Johan Schreiber
 */
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS       13
#define MAX_SIZE        7
#define MAX_LINE        (MAX_WORDS * MAX_SIZE)
#define MIN(a,b)        ((a) < (b) ? (a) : (b))
#define MAX(a,b)        ((a) > (b) ? (a) : (b))

typedef struct {
    int hash;
    int index;
} hash_t;

char line[MAX_LINE];
int words[MAX_WORDS];
int num_words;

/* Compare integers */
int compare(const void *a, const void *b) {
    return *((int *) a) - *((int *) b);
}

/* Compare two hashes */
int compare_hashes(const void *a, const void *b) {
    return ((hash_t *) a)->hash - ((hash_t *) b)->hash;
}

/* Process a line */
void process_line() {
    char *tok = strtok(line, " \n");
    num_words = 0;
    while (tok != NULL) {
        int w;
        for (w = 0; *tok != 0; tok++) {
            w = (w << 5) + (*tok - 'a' + 1);
        }
        words[num_words++] = w;

        tok = strtok(NULL, " \n");
    }
    qsort(words, num_words, sizeof (int), compare);
}

/* Compute value C such that floor(C / w_i) % |w| is unique for each i */
int compute_hash() {
    int i, next, c = 0;
    hash_t hashes[MAX_WORDS];
    while (c >= 0) {
        for (i = 0; i < num_words; i++) {
            hashes[i].hash = (c / words[i]) % num_words;
            hashes[i].index = i;
        }
        qsort(hashes, num_words, sizeof (hash_t), compare_hashes);
        next = 0, i = 1;
        while (i < num_words) {
            if (hashes[i].hash != hashes[i - 1].hash) {
                i++;
            } else {
                int value, index = hashes[i - 1].index;
                int min = ((c / words[index]) + 1) * words[index];
                while (i < num_words && hashes[i].hash == hashes[i - 1].hash) {
                    index = hashes[i++].index;
                    value = ((c / words[index]) + 1) * words[index];
                    min = MIN(value, min);
                }
                next = MAX(min, next);
            }
        }
        if (next == 0) return c;
        c = next;
    }
    assert(NULL);
    return 0;
}

/* Main function */
int main() {
    while (fgets(line, MAX_LINE, stdin) != NULL) {
        printf("%s", line);
        process_line();
        printf("%d\n\n", compute_hash());
    }
    return EXIT_SUCCESS;
}
