/*
 * 10044
 * Erdos Numbers
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAX_AUTHORS 5000
#define MAX_AUTHOR_NAME 32
#define INFINITY (MAX_AUTHORS + 1)

typedef char author_t[MAX_AUTHOR_NAME];
author_t author[MAX_AUTHORS];
short index[MAX_AUTHORS];
int num_authors;

short co_authors[MAX_AUTHORS][MAX_AUTHORS];
short num_co_authors[MAX_AUTHORS];
short erdos_number[MAX_AUTHORS];


/* Search for an author given and return its index */
typedef enum {
    FIND_ONLY,
    FIND_OR_INSERT
} operation_t;
short get_author(author_t name, operation_t op) {
    short begin, end, pointer;
    begin = 0;
    end = num_authors;
    while (begin < end) {
        int result;
        pointer = (begin + end) / 2;
        result = strcmp(name, author[index[pointer]]);
        if (result == 0) {
            return index[pointer];
        }
        else {
            begin = (result > 0 ? pointer + 1 : begin);
            end = (result < 0 ? pointer : end);
        }
    }
    if (op == FIND_OR_INSERT) {
        for (pointer = num_authors; pointer > begin; pointer--) {
            index[pointer] = index[pointer - 1];
        }
        strcpy(author[num_authors], name);
        index[begin] = num_authors;
        erdos_number[num_authors] = INFINITY;
        num_co_authors[num_authors] = 0;
        num_authors++;
        return index[begin];
    }
    return -1;
}


/* Process new article */
void process_article(char *line) {
    char *colon, *word;
    author_t name;
    static short person[MAX_AUTHORS];
    int num_people;
    int i, j;
    
    num_people = 0;

    /* Split people's names and get (or generate) their author IDs */
    colon = strstr(line, ": ") + 2;
    word = strtok(line, ", ");
    while (word != colon) {
        sprintf(name, "%s, ", word);
        word = strtok(NULL, " ,:");
        strcat(name, word);
        person[num_people] = get_author(name, FIND_OR_INSERT);
        num_people++;
        word = strtok(NULL, " ,:");
    }

    /* Add their relationship as co-authors of the article */
    for (i = 0; i < num_people; i++) {
        for (j = 0; j < num_people; j++) {
            if (i != j) {
                co_authors[person[i]][num_co_authors[person[i]]] = person[j];
                num_co_authors[person[i]]++;
            }
        }
    }
}


/* Set Erdos number */
#define MINIMUM(x, y) ((x) < (y) ? (x) : (y))
void set_erdos_number() {
    static short queue[MAX_AUTHORS];
    static char enqueued[MAX_AUTHORS];
    int i, queue_size, queue_top;

    memset(enqueued, 0, num_authors);
    queue[0] = 0;
    enqueued[0] = 1;
    queue_top = 0;
    queue_size = 1;

    while (queue_top < queue_size) {
        short person = queue[queue_top++];
        for (i = 0; i < num_co_authors[person]; i++) {
            erdos_number[co_authors[person][i]] = MINIMUM(
                    erdos_number[person] + 1,
                    erdos_number[co_authors[person][i]]);
            if (!enqueued[co_authors[person][i]]) {
                queue[queue_size++] = co_authors[person][i];
                enqueued[co_authors[person][i]] = 1;
            }
        }
    }
}


/* Main function */
#define INPUT_SIZE 1024
int main() {
    int scenario, num_scenaria;
    char input[INPUT_SIZE];

    strcpy(author[0], "Erdos, P.");
    assert(fgets(input, INPUT_SIZE, stdin) != NULL);
    assert(sscanf(input, "%d", &num_scenaria) != EOF);

    for (scenario = 1; scenario <= num_scenaria; scenario++) {
        int article, num_articles, name, list_size;
        index[0] = 0;
        num_co_authors[0] = 0;
        num_authors = 1;

        assert(fgets(input, INPUT_SIZE, stdin) != NULL);
        assert(sscanf(input, "%d %d", &num_articles, &list_size) != EOF);
        for (article = 0; article < num_articles; article++) {
            assert(fgets(input, INPUT_SIZE, stdin) != NULL);
            process_article(input);
        }
        assert(num_authors <= MAX_AUTHORS);

        set_erdos_number();
       
        printf("Scenario %d\n", scenario);
        for (name = 0; name < list_size; name++) {
            short author_index;
            assert(fgets(input, INPUT_SIZE, stdin) != NULL);
            input[strlen(input) - 1] = '\0';
            printf("%s ", input);
            author_index = get_author(input, FIND_ONLY);
            if (author_index == -1 || erdos_number[author_index] == INFINITY) {
                printf("infinity\n");
            }
            else {
                printf("%d\n", erdos_number[author_index]);
            }
        }
    }

    return 0;
}
