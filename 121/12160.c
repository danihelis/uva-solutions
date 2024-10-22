/* 12160
 * Unlock the Lock
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       10000
#define MAX_EDGES   10

int edge[MAX_EDGES], num_edges;

/* Return the shortest distance from start to end */
int distance(int start, int end) {
    struct {
        int index, dist;
    } queue[MAX_N], cur;
    int i, front, rear;
    char visited[MAX_N];

    memset(visited, 0, MAX_N);
    queue[0].index = start, queue[0].dist = 0;
    visited[start] = 1;
    front = 0, rear = 1;
    
    while (front < rear) {
        cur = queue[front++];
        if (cur.index == end)
            return cur.dist;
        for (i = 0; i < num_edges; i++) {
            int next = (cur.index + edge[i]) % MAX_N;
            if (!visited[next]) {
                visited[next] = 1;
                queue[rear].index = next;
                queue[rear].dist = cur.dist + 1;
                rear++;
            }
        }
    }
    return -1;
}

/* Main function */
int main() {
    int start, end, test = 0;
    while (scanf("%d %d %d", &start, &end, &num_edges) != EOF && 
            num_edges > 0) {
        int i, dist;
        for (i = 0; i < num_edges; i++)
            assert(scanf("%d", &edge[i]) != EOF);
        dist = distance(start, end);
        printf("Case %d: ", ++test);
        (dist < 0 ? printf("Permanently Locked\n") : printf("%d\n", dist));
    }
    return EXIT_SUCCESS;
}
