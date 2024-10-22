/* 10058
 * Jimmi's Riddles
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_WORD        10
#define MAX_STRING      100000

#define NUM_ARTICLES    2
#define NUM_NOUNS       8
#define NUM_VERBS       8

#define COMMA           ","
#define AND             "and"

char articles[NUM_ARTICLES][MAX_WORD] = {"a", "the"};

char nouns[NUM_NOUNS][MAX_WORD] = {
    "cat", "dog", "goofy", "jerry", "jimmy", "mickey", "mouse", "tom"};

char verbs[NUM_VERBS][MAX_WORD] = {
    "hate", "hates", "know", "knows", "like", "likes", "love", "loves"};

/* Compare two words */
int compare(const void *a, const void *b) {
    return strcmp((char *) a, (char *) b);
}

#define NEXT_TOKEN      strtok(NULL, " \n")

/* Parse an actor name */
int parse_actor(char **next) {
    if (*next != NULL && bsearch(*next, articles, NUM_ARTICLES, MAX_WORD, 
                compare) != NULL)
        *next = NEXT_TOKEN;
    if (*next == NULL || bsearch(*next, nouns, NUM_NOUNS, MAX_WORD, 
                compare) == NULL)
        return 0;
    *next = NEXT_TOKEN;
    if (*next != NULL && strcmp(*next, AND) == 0) {
        *next = NEXT_TOKEN;
        return parse_actor(next);
    }
    return 1;
}

/* Parse action */
int parse_action(char *line) {
    char *next = strtok(line, " \n");
    if (!parse_actor(&next))
        return 0;
    if (next == NULL || bsearch(next, verbs, NUM_VERBS, MAX_WORD, 
                compare) == NULL)
        return 0;
    next = NEXT_TOKEN;
    return parse_actor(&next) && next == NULL;
}

/* Parse statement */ 
int parse_statement(char *line) {
    char *find, *statement[MAX_STRING];
    int i, n;
    for (n = 0, find = line - 1; find != NULL; 
            find = strchr(statement[n++], ',')) {
        statement[n] = find + 1;
        if (find >= line)
            *find = 0;
    }
    for (i = 0; i < n; i++)
        if (!parse_action(statement[i]))
            return 0;
    return n > 0;
}

/* Main function */
int main() {
    char line[MAX_STRING];
    while (fgets(line, MAX_STRING, stdin) != NULL)
        printf("%s\n", parse_statement(line) ? "YES I WILL" : "NO I WON'T");
    return EXIT_SUCCESS;
}
