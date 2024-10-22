/*
 * 10150
 * Doublets
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_ENTRIES 25150
#define MAX_WORD_SIZE 16
#define STRING_SIZE (MAX_WORD_SIZE + 2)
#define BRANCH_FACTOR 50
#define LINK_SIZE (MAX_ENTRIES * BRANCH_FACTOR)

char dictionary[MAX_ENTRIES][STRING_SIZE];
int dictionary_size;

typedef struct {
    int index, link_index; /* @dictionary, @link */
} word_t;
word_t word[MAX_ENTRIES];

typedef struct {
    int start, end; /* @word, @word */
} bucket_t;
bucket_t bucket[MAX_WORD_SIZE];

typedef struct {
    int source, neighbour; /* @word, @word */
} link_t;
link_t link[LINK_SIZE];
int link_size;

int solution[MAX_ENTRIES]; /* @link */


/* Insert word in its bucket in regard to its size */
void add_word(char *input) {
    int size, init, i;
    size = strlen(input) - 1;
    input[size] = '\0';
    strcpy(dictionary[dictionary_size], input);

    size--;
    init = bucket[size].end;
    for (i = dictionary_size; i > init; i--) {
        word[i] = word[i - 1];
    }
    word[init].index = dictionary_size;
    word[dictionary_size].link_index = -1;
    dictionary_size++;

    bucket[size].end++;
    for (i = size + 1; i < MAX_WORD_SIZE; i++) {
        bucket[i].start++;
        bucket[i].end++;
    }
}


/* Comapre two entries in an inverted list */
int compare_inverted_list(const void *a, const void *b) {
    return strcmp(dictionary[((word_t *) a)->index], dictionary[((word_t *) b)->index]);
}


/* Return true if the difference between the words is just one letter */
int words_differ_by_one(int a, int b) {
    char *ca, *cb;
    int changes = 0;
    ca = dictionary[word[a].index];
    cb = dictionary[word[b].index];
    while (*ca != '\0' && changes <= 1) {
        changes += (*ca != *cb ? 1 : 0);
        ca++;
        cb++;
    }
    return (changes == 1);
}


/* Ordain the buckets and create link between words that differ by one letter */
void create_links() {
    int i, p, q;
    link_size = 0;
    for (i = 0; i < MAX_WORD_SIZE; i++) {
        int bucket_size = bucket[i].end - bucket[i].start;
        qsort(word + bucket[i].start, bucket_size, sizeof (word_t), compare_inverted_list);

        for (p = bucket[i].start; p < bucket[i].end; p++) {
            word[p].link_index = link_size;            
            for (q = bucket[i].start; q < bucket[i].end; q++) {
                if (p != q && words_differ_by_one(p, q)) {
                    link[link_size].source = p;
                    link[link_size].neighbour = q;
                    link_size++;
                    assert(link_size < LINK_SIZE);
                }
            }
        }
    }
}


/* Find minimal solution that links one word to another via doublets */
int find_minimal_solution(int origin, int destiny) {
    static int word_distance[MAX_ENTRIES];
    static int queue[MAX_ENTRIES]; /* @word */
    int size, current;

    memset(word_distance, 0xFF, sizeof(int) * dictionary_size);
    memset(solution, 0xFF, sizeof(int) * dictionary_size);

    queue[0] = origin;
    word_distance[origin] = 0;
    current = 0;
    size = 1;
    
    while (queue[current] != destiny && current < size) {
        int far = word_distance[queue[current]] + 1;
        int i = word[queue[current]].link_index;
        while (i < link_size && link[i].source == queue[current]) {
            if (word_distance[link[i].neighbour] < 0) {
                queue[size++] = link[i].neighbour;
            }
            if (word_distance[link[i].neighbour] > far || word_distance[link[i].neighbour] < 0) {
                solution[link[i].neighbour] = i;
                word_distance[link[i].neighbour] = far;
            }
            i++;
        }
        current++;
    }
    return (queue[current] == destiny);
}


/* Look for a solution after a string with two words */
#define KEY_INDEX_FIRST (MAX_ENTRIES - 2)
#define KEY_INDEX_SECOND (MAX_ENTRIES - 1)
int obtain_solution(char *input, int *origin, int *destiny) {
    word_t key, *origin_word, *destiny_word;
    int size;

    strcpy(dictionary[KEY_INDEX_FIRST], strtok(input, " \n"));
    strcpy(dictionary[KEY_INDEX_SECOND], strtok(NULL, " \n"));
    size = strlen(dictionary[KEY_INDEX_FIRST]);
    if (size != strlen(dictionary[KEY_INDEX_SECOND])) {
        return 0;
    }

    size--;
    key.index = KEY_INDEX_FIRST;
    origin_word = bsearch(&key, word + bucket[size].start, bucket[size].end - bucket[size].start, 
            sizeof (word_t), compare_inverted_list);
    if (origin_word == NULL) {
        return 0;
    }
    key.index = KEY_INDEX_SECOND;
    destiny_word = bsearch(&key, word + bucket[size].start, bucket[size].end - bucket[size].start, 
            sizeof (word_t), compare_inverted_list);
    if (destiny_word == NULL) {
        return 0;
    }
    *destiny = origin_word - word; /* This switch will provide the correct output order */
    *origin = destiny_word - word;
    
    return find_minimal_solution(*origin, *destiny);
}


/* Print out solution */
void print_solution(int origin, int destiny) {
    int i;
    printf("%s\n", dictionary[word[destiny].index]);
    i = solution[destiny];
    while (i >= 0) {
        printf("%s\n", dictionary[word[link[i].source].index]);
        i = solution[link[i].source];
    }
}


/* Main function */
#define INPUT_SIZE 1024
int main() {
    char input[INPUT_SIZE];
    int first, start, end;

    /* Create dictionary */
    dictionary_size = 0;
    while (fgets(input, INPUT_SIZE, stdin) != NULL) {
        if (input[0] == '\n') {
            break;
        }
        add_word(input);
    }

    create_links();
    
    first = 1;
    while (fgets(input, INPUT_SIZE, stdin) != NULL) {
        (first == 1 ? first = 0 : printf("\n")); 
        if (input[0] == '\n') {
            break;
        }
        if (obtain_solution(input, &start, &end)) {
            print_solution(start, end);
        }
        else {
            printf("No solution.\n");
        }
    }
    return 0;
}
