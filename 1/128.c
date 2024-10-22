/**
 * 127
 * Software CRC
 * by Daniel Donadon
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEXT 1050
#define CRC_MOD 34943


/* Calculate and print CRC */
void print_crc(char *text) {
    unsigned int crc = 0;
    int i, size = strlen(text);

    for (i = 0; i < size; i++) {
        crc <<= 8;
        crc += (unsigned int) text[i];
        crc %= CRC_MOD;
    }
    crc = (crc << 16) % CRC_MOD;
    crc = (CRC_MOD - crc) % CRC_MOD;

    printf("%02X %02X\n", (0x00ff & (crc >> 8)), (0x00ff & crc));
}


/* Main */ 
#define REMOVE_ENDLINE(c, k) \
    do { \
        char *k_pos_ = strchr(c, k); \
        if (k_pos_ != NULL) { \
            *k_pos_ = '\0'; \
        } \
    } while (0)

int main() {
    char text[MAX_TEXT];

    while (fgets(text, MAX_TEXT, stdin) != NULL) {
        if (text[0] == '#') {
            break;
        }
        REMOVE_ENDLINE(text, '\n');
        REMOVE_ENDLINE(text, '\r');
        print_crc(text);
    }
    return 0;
}

