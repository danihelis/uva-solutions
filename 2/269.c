/* 269
 * Counting Patterns
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N           12
#define MAX_PATTERNS    75000
#define HASHSIZE        999983

typedef char pattern_t[MAX_N];
pattern_t bank[MAX_PATTERNS], *dict[MAX_PATTERNS];
pattern_t pattern, lexical;
pattern_t *hashtable[HASHSIZE];
int n, k, bank_size;

/* Create a lexical entry from pattern */
void create_lexical_entry() {
    char candidate[2 * MAX_N];
    int j, i, r;
    lexical[0] = 0;
    for (j = 0; j < 4; j++) {
        switch (j) {
            case 0:
                strncpy(candidate, pattern, n);
                strncpy(candidate + n, pattern, n);
                break;
            case 1:
            case 3:
                for (i = 0, r = 2 * n - 1; i < r; i++, r--) {
                    char swap = candidate[i];
                    candidate[i] = candidate[r];
                    candidate[r] = swap;
                }
                break;
            case 2:
                for (i = 0; i < 2 * n; i++)
                    candidate[i] = 2 * k + 2 - candidate[i];
                break;
        }
        for (i = 0; i < n; i++)
            if (candidate[i] >= lexical [0] &&
                    strncmp(lexical, candidate + i, n) < 0)
                strncpy(lexical, candidate + i, n);
    }
    lexical[n] = 0;
}

/* Generate a hash code for a lexical entry */
int hashcode() {
    int i, code;
    for (i = code = 0; i < n; i++)
        code = (code * (2 * k + 2) + lexical[i] - 1) % HASHSIZE;
    return code;
}

/* Initialize hashtable */
void init_hash() {
    memset(hashtable, 0, sizeof (hashtable));
}

/* Get hash index using hash collision */
int get_hash_index() {
    int code = hashcode();
    int index = code;
    while (hashtable[index] != NULL && 
            strncmp(*hashtable[index], lexical, n) != 0) {
        index = (index + 2) % HASHSIZE;
        assert(index != code); /* overflow */
    }
    return index;
}

/* Insert a new pattern on hashtable */
int insert_new_on_hash() {
    int index;
    create_lexical_entry();
    index = get_hash_index();
    if (hashtable[index] == NULL) {
        strncpy(bank[bank_size], lexical, n);
        dict[bank_size] = &bank[bank_size];
        hashtable[index] = &bank[bank_size];
        assert(++bank_size < MAX_PATTERNS);
        return 1;
    }
    return 0;
}

/* Generate a new pattern (recursively) */
void generate_pattern() {
    int start, end;
    if (insert_new_on_hash())    
        for (start = 0; start < n; start++) {
            int max = start == 0 ? 2 * k + 1: pattern[0];
            int min = 2 * k + 2 - max;
            if (pattern[start] < max) {
                pattern[start]++;
                for (end = 1; end < n; end++)
                    if (end != start && pattern[end] > min) {
                        pattern[end]--;
                        generate_pattern();
                        pattern[end]++;
                    }
                pattern[start]--;
            }
        }
}

/* Create all patterns */
void create_all_patterns() {
    int i;
    for (i = 0; i < n; i++)
        pattern[i] = k + 1;
    bank_size = 0;
    init_hash();
    generate_pattern();
}

/* Compare patterns in order to sort them */
int compare(const void *a, const void *b) {
    pattern_t *x = * (pattern_t **) a, *y = * (pattern_t **) b;
    return strncmp(*x, *y, n);
}

/* Print all patterns found */
void print_patterns() {
    int i, j;
    qsort(dict, bank_size, sizeof (pattern_t *), compare);
    printf("%d\n", bank_size);
    for (i = 0; i < bank_size; i++) {
        putchar('(');
        for (j = 0; j < n; j++)
            printf("%d%c", (*dict[i])[j] - k - 1, j < n - 1 ? ',' : ')');
        putchar('\n');
    }
}

/* Main function */
int main() {
    int first = 1;
    while(scanf("%d %d", &n, &k) == 2) {
        create_all_patterns();
        first ? (first = 0) : printf("\n");
        print_patterns();
    }
    return EXIT_SUCCESS;
}
