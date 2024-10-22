/* 1347
 * Tour
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   500
#define SQ(x)   ((x) * (x))

typedef struct {
    int x, y;
} point_t;

point_t point[MAX_N];
int n;

/* Compute best bitonic euclidian tour.
 *
 * Let P{i,j} = <p_i, p_i-k, ..., p_0, p_k, p_j> be a path from p_i to
 * p_0 leftwards and from p_0 to p_j rightwards, with i < j, and 
 * which includes all points from 0..j.
 *
 * Let d(i,j) denote the distance between p_i and p_j.
 * Let B[i,j] represent the best route for P{i,j}. We have that:
 *
 *      B[0,1]   = d(0,1)
 * (1)  B[i,j]   = B[i,j-1] + d(j-1,j)    for i < j-1
 * (2)  B[j-1,j] = min[0<=k<j-1] B[k,j-1] + d(k,j)
 *
 * For (1), observe that, since i < j-1, p_{j-1} is connected rightwards to 
 * p_k. Therefore, the best route in P{i,j} is the one postulated.
 *
 * For (2), p_{j-1} is not connected rightwards to p_j (otherwise we would be
 * on case (1)). Therefore, there is a p_k, k < j, that connects p_j. We
 * find that using a reversed path P_{k,j-1}.
 *
 * The solution is B[n,n] = B[n-1,n] + d(n-1,n).
 */
double best_path() {
    double best[MAX_N][MAX_N], dist[MAX_N][MAX_N];
    int i, j, k;
    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j < n; j++)
            dist[i][j] = sqrt(SQ(point[i].x - point[j].x) +
                    SQ(point[i].y - point[j].y));
    for (i = 0; i < n - 1; i++) {
        if (i == 0)
            best[0][1] = dist[0][1];
        else {
            double min = HUGE_VAL;
            for (k = 0; k < i; k++) {
                double d = best[k][i] + dist[k][i + 1];
                if (d < min)
                    min = d;
            }
            best[i][i + 1] = min;
        }
        for (j = i + 2; j < n; j++)
            best[i][j] = best[i][j - 1] + dist[j - 1][j];
    }
    return best[n - 2][n - 1] + dist[n - 2][n - 1];
}

/* Main function */
int main() {
    while (scanf("%d", &n) != EOF) {
        int i;
        for (i = 0; i < n; i++) {
            point_t *p = &point[i];
            assert(scanf("%d %d", &p->x, &p->y) != EOF);
        }
        printf("%.2f\n", best_path());
    }
    return EXIT_SUCCESS;
}
