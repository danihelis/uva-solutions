/* 10242
 * Fourth Point !!
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

typedef struct {
    int x, y;
} point_p;

/* Read a point */
int read(point_p *p) {
    int i, f, k, v;
    for (k = 0; k < 2; k++) {
        if (scanf("%d.%d", &i, &f) != 2)
            return 0;
        v = (abs(i) * 1000 + f) * (i < 0 ? -1 : 1);
        (k == 0 ? (p->x = v) : (p->y = v));
    }
    return 1;
}

/* Print point */
void print_point(point_p *p) {
    int k;
    for (k = 0; k < 2; k++) {
        int v = k == 0 ? p->x : p->y;
        printf("%s%d.%03d%c", v < 0 ? "-" : "", abs(v) / 1000, 
                abs(v) % 1000, k == 0 ? ' ' : '\n');
    }
}

/* Main function */
int main() {
    point_p s1[2], s2[2], dir, p;
    int i1, i2, i, j;
    while (read(&s1[0])) {
        assert(read(&s1[1]) && read(&s2[0]) && read(&s2[1]));
        for (i = 0, i1 = i2 = -1; i1 == -1 && i < 2; i++)
            for (j = 0; i1 == -1 && j < 2; j++)
                if (s1[i].x == s2[j].x && s1[i].y == s2[j].y)
                    i1 = i, i2 = j;
        dir.x = s1[i1].x - s1[1 - i1].x, dir.y = s1[i1].y - s1[1 - i1].y;
        p.x = s2[1 - i2].x - dir.x, p.y = s2[1 - i2].y - dir.y;
        print_point(&p);
    }
    return EXIT_SUCCESS;
}
