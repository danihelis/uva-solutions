/**
 * 126
 * The Errant Physicist
 * by Daniel Donadon
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TERMS 80
#define MAX_LINE 1000

typedef struct {
    int x, y, coef;
} monomial_t;

monomial_t poly1[MAX_TERMS], poly2[MAX_TERMS];
int poly_size1, poly_size2;
monomial_t result[MAX_TERMS];
int poly_size_result;


/* Compare two monomials to see which is smaller */
int compare_monomial(monomial_t *a, monomial_t *b) {
    if (a->x != b->x) {
        return b->x - a->x;
    }
    else {
        return a->y - b->y;
    }
}


/* Insert an monomial inside a polynomial, summing it if already existent */
void sum_monomial(monomial_t *mono, monomial_t *poly, int *size) {
    int i, min, max, pos, existent;

    if (mono->coef == 0) {
        return;
    }

    /* Binary search */
    existent = 0;
    min = 0;
    max = *size - 1;
    while (!existent && min <= max) {
        int cmp;
        pos = (min + max) / 2;
        cmp = compare_monomial(mono, &poly[pos]);
        if (cmp == 0) {
            existent = 1;
        }
        else if (cmp < 0) {
            max = pos - 1;
        }
        else {
            min = pos + 1;
        }
    }

    /* Insertion or sum */
    if (existent) {
        poly[pos].coef += mono->coef;
        if (poly[pos].coef == 0) {
            for (i = pos; i < *size; i++) {
                poly[i] = poly[i + 1];
            }
            *size -= 1;
        }
    }
    else {
        for (i = *size; i > min; i--) {
            poly[i] = poly[i - 1];
        }
        poly[min] = *mono;
        *size += 1;
    }
}


/* Calculate the multiplication of two polynomials */
void multiply() {
    int i, j;
    poly_size_result = 0;
    for (i = 0; i < poly_size1; i++) {
        for (j = 0; j < poly_size2; j++) {
            monomial_t multi;
            multi.x = poly1[i].x + poly2[j].x;
            multi.y = poly1[i].y + poly2[j].y;
            multi.coef = poly1[i].coef * poly2[j].coef;
            sum_monomial(&multi, result, &poly_size_result);            
        }
    }        
}


/* Macros for reading */
#define READ_NUMBER(c, num, exp) \
    do { \
        int read_signal_ = 1; \
        num = 0; \
        if (!exp && (*(c) == '-' || *(c) == '+')) { \
            read_signal_ = (*(c) == '-' ? -1 : 1);\
            (c)++; \
        } \
        while (*(c) != '\0' && isdigit((int) *(c))) { \
            num *= 10; \
            num += *(c) - '0'; \
            (c)++; \
        } \
        num *= read_signal_; \
        if (num == 0 && *(c - 1) != '0') { \
            num = 1 * read_signal_; \
        } \
    } while (0)

#define READ_VARIABLE(c, var) \
    do { \
        var = tolower((int) *c); \
        if (var == 'x' || var == 'y') { \
            c++; \
        } \
    } while (0)

#define REMOVE_CHAR(line, k) \
    do { \
        char *line_pos_ = strchr((line), (k)); \
        if (line_pos_ != NULL) { \
            *line_pos_ = '\0'; \
        } \
    } while (0)


/* Read a polynomial */
void read_polynomial(monomial_t *poly, int *size, char *line) {
    char var, *c = line;

    REMOVE_CHAR(c, '\n');
    REMOVE_CHAR(c, '\r');
    *size = 0;
    while (*c != '\0') {
        int repeat;
        monomial_t mono;
        mono.x = 0;
        mono.y = 0;
        READ_NUMBER(c, mono.coef, 0);
        for (repeat = 0; repeat < 2; repeat++) {
            READ_VARIABLE(c, var);
            switch (var) {
                case 'x': READ_NUMBER(c, mono.x, 1); break;
                case 'y': READ_NUMBER(c, mono.y, 1); break;
            }
        }
        sum_monomial(&mono, poly, size);
    }
}

/* Print a polynomial */
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define ABS(x) ((x) > 0 ? (x) : -(x))

#define CONCAT_NUMBER(line, text, num, var) \
    do { \
        if (num == 0) { \
            continue; \
        } \
        strcat(line, var); \
        if (num > 1 || var[0] == '\0') { \
            sprintf(text, "%d", (num)); \
            strcat(line, text); \
        } \
    } while (0)

void print_polynomial(monomial_t *poly, int size) {
    char line[MAX_LINE], power[MAX_LINE], *var;
    int i;

    line[0] = '\0';
    for (i = 0; i < size; i++) {
        char text[10];
        if (i == 0) {
            strcat(line, (poly[i].coef < 0 ? "-" : ""));
        }
        else {
            strcat(line, (poly[i].coef < 0 ? " - " : " + "));
        }
        if (ABS(poly[i].coef) != 1 || (poly[i].x == 0 && poly[i].y == 0)) {
            CONCAT_NUMBER(line, text, ABS(poly[i].coef), "");
        }
        CONCAT_NUMBER(line, text, poly[i].x, "x");
        CONCAT_NUMBER(line, text, poly[i].y, "y");
    }

    memset(power, 0x20, strlen(line));
    power[strlen(line)] = '\0';

    var = line;
    while (var != NULL) {
        char *px, *py;
        px = strchr(var, 'x');
        py = strchr(var, 'y');
        var = (px == NULL ? py : (py == NULL ? px : MIN(px, py)));
        if (var != NULL) {
            var++;
            while (isdigit((int) *var)) {
                power[var - line] = *var;
                *var = ' ';
                var++;
            }
        }
    }
    
    printf("%s\n", power);
    printf("%s\n", line);
}


/* Main */
int main() {
    char line[MAX_LINE];

    while (fgets(line, MAX_LINE, stdin) != NULL) {
        if (line[0] == '#') {
            break;
        }
        read_polynomial(poly1, &poly_size1, line);
        fgets(line, MAX_LINE, stdin);
        read_polynomial(poly2, &poly_size2, line);
        multiply();
        print_polynomial(result, poly_size_result);
    }
    return 0;
}

