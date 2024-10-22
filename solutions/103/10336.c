/* 10336
 * Rank the Languages
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIMENSION   1000
#define MAX_STRING      (MAX_DIMENSION + 2)
#define MAX_LANGUAGES   26
#define NUM_DIRECTIONS  4

typedef struct {
    char lang;
    int states;
} lang_t, *lang_p;

typedef struct {
    int row, column;
} point_t, *point_p;

int drow[] = {-1, 0, 1, 0}, dcol[] = {0, 1, 0, -1};

lang_t language[MAX_LANGUAGES];
lang_p lang_ptr[MAX_LANGUAGES];
char map[MAX_DIMENSION][MAX_STRING];
int width, height;

/* Compare two pointers of lang_t */
int compare(const void *a, const void *b) {
    lang_p x = *((lang_p *) a), y = *((lang_p *) b);
    if (x->states == y->states) {
        return x->lang - y->lang;
    }
    return y->states - x->states;
}

/* Initialize the vector of languages */
void initialize() {
    int i;
    for (i = 0; i < MAX_LANGUAGES; i++) {
        lang_ptr[i] = &language[i];
        language[i].lang = i + 'a', language[i].states = 0;
    }
}

/* Mark a region as a visited state */
#define IS_IN(x, max)   ((x) >= 0 && (x) < (max))
void mark_region(int row, int col) {
    point_t stack[MAX_DIMENSION * MAX_DIMENSION];
    int i, top = 1;
    char lang = map[row][col];
    stack[0].row = row, stack[0].column = col;
    while (top > 0) {
        point_t cur, new;
        top--;
        cur.row = stack[top].row, cur.column = stack[top].column;
        map[cur.row][cur.column] = 0;
        for (i = 0; i < NUM_DIRECTIONS; i++) {
            new.row = cur.row + drow[i], new.column = cur.column + dcol[i];
            if (IS_IN(new.row, height) && IS_IN(new.column, width) && 
                    map[new.row][new.column] == lang) {
                stack[top++] = new;
            }
        }
    }
    language[lang - 'a'].states++;
}

/* Main function */
int main() {
    int test, num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (test = 1; test <= num_tests; test++) {
        int row, col;
        printf("World #%d\n", test);
        assert(scanf("%d %d", &height, &width) != EOF);
        for (row = 0; row < height; row++) {
            assert(scanf(" %s", map[row]) != EOF);
        }
        initialize();
        for (row = 0; row < height; row++) {
            for (col = 0; col < width; col++) {
                if (map[row][col] != 0) {
                    mark_region(row, col);
                }
            }
        }
        qsort(lang_ptr, MAX_LANGUAGES, sizeof (lang_p), compare);
        for (row = 0; row < MAX_LANGUAGES && lang_ptr[row]->states > 0; row++) {
            printf("%c: %d\n", lang_ptr[row]->lang, lang_ptr[row]->states);
        }
    }
    return 0;
}
