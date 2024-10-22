/*
 * 843
 * Crypt Kicker
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define DICTIONARY_SIZE 1000
#define NUM_LETTERS 26
#define WORD_LENGTH 16
#define STRING_SIZE (WORD_LENGTH + 2)
#define INPUT_STRING_LENGTH 82
#define MAX_INPUT_WORDS (INPUT_STRING_LENGTH / 2)
#define UNDEFINED 0x00
#define AS_INDEX(c) ((c) - 'a')

typedef char string[STRING_SIZE];
string dictionary[DICTIONARY_SIZE];
int dict_size;

typedef struct {
    short entry[DICTIONARY_SIZE];
    short num_entries;    
} length_t;
length_t dict_by_length[WORD_LENGTH];

string input_word[MAX_INPUT_WORDS];
int num_words;

typedef struct {
    short word, length, diff_letters;
} encrypted_word_t;
encrypted_word_t encrypted_word[MAX_INPUT_WORDS];
int num_enc_words;

typedef struct {
    char value;
    short level;
} crypt_t;
crypt_t crypt[NUM_LETTERS];
char crypt_respective[NUM_LETTERS];


/* Read dictionary and prepare indexed vectors */
void read_dictionary() {
    int i, length;
    string input;

    for (i = 0; i < WORD_LENGTH; i++) {
        dict_by_length[i].num_entries = 0;
    }
    dict_size = 0;
    
    assert(fgets(input, STRING_SIZE, stdin) != NULL);
    assert(sscanf(input, "%d", &dict_size) != EOF);
    for (i = 0; i < dict_size; i++) {
        assert(fgets(dictionary[i], STRING_SIZE, stdin) != NULL);
        length = strlen(dictionary[i]) - 1;
        dictionary[i][length] = '\0';
        length--;
        dict_by_length[length].entry[dict_by_length[length].num_entries] = i;
        dict_by_length[length].num_entries++;
    }
}


/* Sort encrypted words by the number of different  letters they have */
int sort_by_different_letters(const void *a, const void *b) {
    encrypted_word_t *x = (encrypted_word_t *) a, *y = (encrypted_word_t *) b;
    if (x->diff_letters == y->diff_letters) {
        return y->length - x->length;
    }
    return y->diff_letters - x->diff_letters;
}


/* Process input counting different letters. Return false if the input is unacceptable. */
int validate_and_process_input(string line) {
    char *word, valid = 1;

    num_words = 0;
    num_enc_words = 0;
    word = strtok(line, " \n");
    while (word != NULL) {
        char new_word = 1;
        short i;
        strcpy(input_word[num_words], word);

        for (i = 0; valid && i < num_enc_words && new_word; i++) {
            if (strcmp(word, input_word[encrypted_word[i].word]) == 0) {
                new_word = 0;
            }
        }
        if (valid && new_word) {
            short length, diff = 0;
            long int letters = 0L;
            for (length = 0; word[length] != '\0'; length++) {
                if (((1 << (word[length] - 'a')) & letters) == 0) {
                    letters |= 1 << (word[length] - 'a');
                    diff++;
                }
            }
            length--;
            if (dict_by_length[length].num_entries == 0) {
                valid = 0;
            }
            encrypted_word[num_enc_words].word = num_words;
            encrypted_word[num_enc_words].length = length;            
            encrypted_word[num_enc_words].diff_letters = diff;
            num_enc_words++;
        }
        num_words++;
        word = strtok(NULL, " \n");
    }

    if (valid) {
        qsort(encrypted_word, num_enc_words, sizeof (encrypted_word_t), sort_by_different_letters);
    }
    return valid;
}


/* Recursive function to decrypt all words */
#define DECRYPT() (decrypt_words(0, 0))
int decrypt_words(short index, short depth) {
    short i, c;
    short length = encrypted_word[index].length;
    char *input = input_word[encrypted_word[index].word];

    if (index >= num_enc_words) {
        return 1;
    }

    for (i = 0; i < dict_by_length[length].num_entries; i++) {
        char *dict = dictionary[dict_by_length[length].entry[i]];
        for (c = 0; c <= length; c++) {
            if (crypt[AS_INDEX(input[c])].value == UNDEFINED 
                    && crypt_respective[AS_INDEX(dict[c])] == UNDEFINED) {
                crypt[AS_INDEX(input[c])].value = dict[c];
                crypt[AS_INDEX(input[c])].level = depth;
                crypt_respective[AS_INDEX(dict[c])] = input[c];
            }
            else if (crypt[AS_INDEX(input[c])].value != dict[c]) {
                break;
            }
        }
        if (c > length && decrypt_words(index + 1, depth + 1)) {
            return 1;
        }
        else {
            for (c -= 1; c >= 0; c--) {
                if (crypt[AS_INDEX(input[c])].level == depth) {
                    crypt[AS_INDEX(input[c])].value = UNDEFINED;
                    crypt_respective[AS_INDEX(dict[c])] = UNDEFINED;
                }
            }
        }
    }
    return 0;
}


/* Main function */
int main() {
    char input[INPUT_STRING_LENGTH];
    int valid_crypt;

    read_dictionary();
    while (fgets(input, INPUT_STRING_LENGTH, stdin) != NULL) {
        int i, c;
        for (i = 0; i < NUM_LETTERS; i++) {
            crypt[i].value = UNDEFINED;
            crypt_respective[i] = UNDEFINED;
        }

        valid_crypt = validate_and_process_input(input);
        if (valid_crypt) {
            valid_crypt = DECRYPT();
        }
        for (i = 0; i < num_words; i++) {
            for (c = 0; input_word[i][c] != '\0'; c++) {
                printf("%c", (valid_crypt ? crypt[AS_INDEX(input_word[i][c])].value : '*'));
            }
            printf("%c", (i < (num_words - 1) ? ' ' : '\n'));
        }
    }

    return 0;
}
