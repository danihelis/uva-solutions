/*
 * 10267
 * Graphical Editor
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Helpful macro */
#define ORDAIN(a, b) \
    do { \
        if (a > b) { \
            int x = a; \
            a = b; \
            b = x; \
        } \
    } while (0)

#define INSIDE(a, sup) ((a) >= 0 && (a) < (sup))

/* Global variables */
#define MAX_STRING 1024
char input[MAX_STRING];

#define MAX_DIM 250
#define MAP_SIZE (MAX_DIM * MAX_DIM)
char image[MAX_DIM][MAX_DIM];
int width, height;

/* Fill a region of the same color with a new one from a given point */
void fill(int r, int c, char color) {
    static int dr[4] = {0, 1, 0, -1};
    static int dc[4] = {1, 0, -1, 0};
    static char on_queue[MAX_DIM][MAX_DIM];
    static struct {
        short row, column;
    } queue[MAP_SIZE];
    int queue_top, queue_size;
    char shared_color;

    /* The region is already colored */
    if (color == image[r][c]) {
        return;
    }

    memset(on_queue, 0, MAP_SIZE);
    shared_color = image[r][c];
    queue[0].row = r;
    queue[0].column = c;
    on_queue[r][c] = 1;
    queue_top = 0;
    queue_size = 1;
    
    while (queue_top < queue_size) {
        int i;
        r = queue[queue_top].row;
        c = queue[queue_top].column;
        queue_top++;
        image[r][c] = color;

        for (i = 0; i < 4; i++) {
            if (INSIDE(r + dr[i], height) && INSIDE(c + dc[i], width) && 
                    image[r + dr[i]][c + dc[i]] == shared_color &&
                    !on_queue[r + dr[i]][c + dc[i]]) {
                queue[queue_size].row = r + dr[i];
                queue[queue_size].column = c + dc[i];
                on_queue[r + dr[i]][c + dc[i]] = 1;
                queue_size++;
            }
        }        
    }
}


/* Main function */
int main() {
    int run = 1;
    int row, column, x1, x2, y1, y2;
    char color, filename[50], *params;
    width = 0;
    height = 0;

    while (run && fgets(input, MAX_STRING, stdin) != NULL) {
        params = input + 1;
        switch (input[0]) {
            /* Create image */
            case 'I':
                sscanf(params, "%d %d", &width, &height);

            /* Clear image */
            case 'C':
                memset(image, 'O', MAP_SIZE);
                break;

            /* Color a pixel */
            case 'L':
                sscanf(params, "%d %d %c", &column, &row, &color);
                image[row - 1][column - 1] = color;
                break;

            /* Draw a vertical line */
            case 'V':
                sscanf(params, "%d %d %d %c", &column, &y1, &y2, &color);
                ORDAIN(y1, y2);
                for (row = y1 - 1; row < y2; row++) {
                    image[row][column - 1] = color;
                }
                break;

            /* Draw a horizontal line */
            case 'H':
                sscanf(params, "%d %d %d %c", &x1, &x2, &row, &color);
                ORDAIN(x1, x2);
                for (column = x1 - 1; column < x2; column++) {
                    image[row - 1][column] = color;
                }
                break;

            /* Draw a rectangle box */
            case 'K':
                sscanf(params, "%d %d %d %d %c", &x1, &y1, &x2, &y2, &color);
                for (column = x1 - 1; column < x2; column++) {
                    for (row = y1 - 1; row < y2; row++) {
                        image[row][column] = color;
                    }
                }
                break;

            /* Fill a region of the same color with a new one */
            case 'F':
                sscanf(params, "%d %d %c", &column, &row, &color);
                fill(row - 1, column - 1, color);
                break;

            /* Display the image and its name */
            case 'S':
                sscanf(params, "%s", filename);
                printf("%s\n", filename);
                for (row = 0; row < height; row++) {
                    for (column = 0; column < width; column++) {
                        printf("%c", image[row][column]);
                    }
                    printf("\n");
                }
                break;

            /* End of script */
            case 'X':
                run = 0;
                break;
        }
    }

    return 0;
}
