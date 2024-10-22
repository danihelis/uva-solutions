/* 516
 * Prime Land
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_PRIMES  4000
#define MAX_NUMBER  32767
#define MAX_LINE    1000

int primes[MAX_PRIMES];

/* Generate all possible primes in the range */
void generate_primes() {
    int total, n;
    primes[0] = 2, total = 1;
    for (n = 3; n <= MAX_NUMBER; n += 2) {
        int k, is_prime;
        for (k = 1, is_prime = 1; k < total; k++) {
            if (n % primes[k] == 0) {
                is_prime = 0;
                break;
            }
        }
        if (is_prime) {
            primes[total++] = n;
        }
    }
}

/* Readn prime representation of number */
#define CONSUME(t, p)   assert(p != NULL); t = atoi(p); p = strtok(NULL, " ")
int read_prime_notation() {
    char line[MAX_LINE];
    assert(fgets(line, MAX_LINE, stdin) != NULL);
    if (line[0] == '0') {
        return 0;
    }
    else {
        char *p = strtok(line, " ");
        int k, number = 1;
        while (p != NULL) {
            int prime, power;
            CONSUME(prime, p);
            CONSUME(power, p);
            for (k = 0; k < power; k++) {
                number *= prime;
            }            
        }
        return number;
    }
}

/* Print prime representation of number */ 
void print_prime_notation(int n) {
    int power[MAX_PRIMES];
    int p = 0;
    while (n > 1) {
        power[p] = 0;
        while (n % primes[p] == 0) {
            n /= primes[p];
            power[p]++;
        }
        p++;
        assert(p < MAX_PRIMES);
    }
    for (--p; p >= 0; p--) {
        if (power[p] > 0) {
            printf("%s%d %d", (n ? "" : " "), primes[p], power[p]);
            n = 0;
        }
    }
    printf("\n");
}

/* Main function */
int main() {
    int input;
    generate_primes();
    while ((input = read_prime_notation()) != 0) {
        print_prime_notation(input - 1);
    }
    return 0;
}
