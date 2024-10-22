/* 10212
 * The Last Non-zero Digit.
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

/*
 * We want to compute the last nonzero digit of N!
 * Let f(n) be the function tha removes all right zeros from its argument,
 *      f(n) = n / 2^a·5^b, where a and b are the highest values such that
 *                          f(n) is integer
 * Therefore, to compute the last nonzero digit, we compute
 *      [ f(N!) · 2^a · 5^b ] % 10,  since N! = 2^a · 5^b · f(N!)
 * If a == b, then we may just compute f(N!) % 10; 
 * if a < b, it is enough to compute [ f(N!) · 5^(b-a) ] % 10; 
 * otherwise, [ f(N!) · 2^(a-b) ] % 10.
 *
 * To compute f(N!) % 10 = f(N)·f(N-1)·...·f(1) % 10 = Π{ f(n) % 10 }, 
 * we can observe that f(n) % 10 always ends in either 1, 3, 7 or 9. 
 * Since we want only the last digits, we can
 * compute how many f(n) terms from f(N!) end in each value, and obtain:
 *      [ f(N!) · 2^a · 5^b ] % 10 = [ 2^a · 5^b · 3^c · 7^d · 9^e ] % 10
 *       
 * Observe that:
 * 2^a ends in 6, 2, 4, 8 depending on a % 4, in order, if a > 0. 
 * 5^b ends in 5, if b > 0.
 * 3^c ends in 1, 3, 9, 7, depending on c % 4, in order.
 * 7^d ends in 1, 7, 9, 3, depending on d % 4, in order.
 * 9^e ends in 1, 9, depending on e % 2, in order.
 *
 * To determine a and b, we compute the following:
 * a = (N\2) + (N\2)\2 + ((N\2)\2)\2 + ..., with \ meaning integer division.
 * b = (N\5) + (N\5)\5 + ...
 *
 * The compute how many factors f(n) end in 3, 7, 9, observe that if 
 * f(n) = n, then n ends in 1, 3, 7 or 9. Therefore, there are N \ 10
 * of such terms, plus one if N ends with digit equal or larger than 3, 7, 9.
 * Moreover, if f(n) != n, then f(n/L) = n/L, where L = 2^a·5^b.
 * Therefore, for each L <= N, there are (N\L) \ 10 terms ending in 3, 7, 9,
 * plus one if (N\L) ends with digit equal or larger than 3, 7, 9.
 *
 * Time: O(log²N)
 */

typedef struct {
    int two, five, three, seven, nine;
} endings_t;

/* Compute how many terms ending with a digit N! has */
endings_t compute(int n) {
    endings_t end = {0, 0, 0, 0, 0};
    int k, p;
    for (k = n; k >= 2; k /= 2)
        end.two += k / 2;
    for (k = n; k >= 5; k /= 5)
        end.five += k / 5;
    for (p = 1; p <= n; p *= 5)
        for (k = p; k <= n; k *= 2) {
            int size = n / k;
            int count = size / 10;
            end.three += count + (size % 10 >= 3 ? 1 : 0);
            end.seven += count + (size % 10 >= 7 ? 1 : 0);
            end.nine += count + (size % 10 >= 9 ? 1 : 0);
        }
    return end;
}

/* Compute last digit from an ending */
int last_digit(endings_t end) {
    int THREE[] = {1, 3, 9, 7},
        SEVEN[] = {1, 7, 9, 3},
        NINE[] = {1, 9},
        TWO[] = {6, 2, 4, 8};
    int digit = THREE[end.three % 4] * SEVEN[end.seven % 4] *
            NINE[end.nine % 2];
    if (end.two > end.five)
        digit *= TWO[(end.two - end.five) % 4];
    else if (end.five > end.two)
        digit *= 5;
    return digit % 10;
}

/* Main function */
int main() {
    int n, m;
    while (scanf("%d %d", &n, &m) != EOF) {
        endings_t end_n = compute(n), end_m = compute(n - m);
        end_n.two -= end_m.two;
        end_n.five -= end_m.five;
        end_n.three -= end_m.three;
        end_n.seven -= end_m.seven;
        end_n.nine -= end_m.nine;
        printf("%d\n", last_digit(end_n));
    }
    return EXIT_SUCCESS;
}
