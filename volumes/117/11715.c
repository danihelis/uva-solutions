/* 11715
 * Car
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

/*  v(t) = a·t + v0; s(t) = 1/2·a·t² + v0·t
    1. v0 v t => s, a  | a = (v - v0)/t
    2. v0 v a => s, t  | t = (v - v0)/a 
    3. v0 a s => v, t  | b = (v0² + 2·a·s); t = (-v0 + sqrt(b))/a
    4. v a s => v0, t  | v0 = sqrt(-2·s·a - v²)
*/

/* Velocity given constant acceleration, time and V0 */
double get_v(double a, double t, double v0) {
    return a * t + v0;
}

/* Displacement given constant acceleration, time and V0 */
double get_s(double a, double t, double v0) {
    return 0.5 * a * t * t + v0 * t;
}

/* Acceleration given velocities and time */
double get_a(double v, double t, double v0) {
    return (v - v0) / t;
}

/* Time given initial velocity, displacement and acceleration */
double get_t(double s, double v0, double a) {
    double b = v0 * v0 + 2 * a * s;
    assert(b >= 0);
    return (-v0 + sqrt(b)) / a;
}

/* Initial velocity given final velocity, acceleration and displacement */
double get_v0(double v, double a, double s) {
    double b = v * v - 2 * s * a;
    assert(b >= 0);
    return sqrt(b);
}

/* Main function */
int main() {
    int option, test = 0;
    double v0, v, a, s, t, p[3];
    while (scanf("%d", &option) != EOF && option > 0) {
        assert(scanf("%lf %lf %lf", &p[0], &p[1], &p[2]) != EOF);
        printf("Case %d: ", ++test);
        switch (option) {
            case 1: v0 = p[0], v = p[1], t = p[2];
                    a = get_a(v, t, v0), s = get_s(a, t, v0);
                    printf("%.3f %.3f\n", s, a);
                    break;
            case 2: v0 = p[0], v = p[1], a = p[2];
                    t = get_a(v, a, v0), s = get_s(a, t, v0);
                    printf("%.3f %.3f\n", s, t);
                    break;
            case 3: v0 = p[0], a = p[1], s = p[2];
                    t = get_t(s, v0, a), v = get_v(a, t, v0);
                    printf("%.3f %.3f\n", v, t);
                    break;
            case 4: v = p[0], a = p[1], s = p[2];
                    v0 = get_v0(v, a, s), t = get_a(v, a, v0);
                    printf("%.3f %.3f\n", v0, t);
                    break;
            default:
                    assert(NULL);
        }
    }
    return 0;
}
