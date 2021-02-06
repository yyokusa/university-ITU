#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// overflows with big numbers, use log int and maybe use res = r then res = n-r then n maybe in one pass
/*
Write a function functions ) to c alculate combination
•
C(n , r ))= n ! / (r! * (n - r)!)
•
Design your code considering performance and functionality
•
Test with inputs i.e . n=9, r=3
*/
int results[3]; // n r (n - r)
void factorial(int, int);
int combination(int n, int r);
int main() {
    int n = 0;
    int r = 0;
    scanf("%d %d", &n, &r);
    printf("%d", combination(n, r));
    return 0;
}

int combination(int n, int r) {   
    printf("t1: %d\n", results[0]);
    printf("t2: %d\n", results[1]);
    printf("t3: %d\n", results[2]);
    factorial(n, r);
    printf("t1: %d\n", results[0]);
    printf("t2: %d\n", results[1]);
    printf("t3: %d\n", results[2]);
    return  results[0] / (results[1] * results[2]);
}

void factorial(int n, int r) {
    if (n <= 1) {
        results[0] = 1;
    }
    if (r <= 1) {
        results[1] = 1;
    }
    if (n - r <= 1) {
        results[2] = 1;
    }
    int res = 1;
    for(int i = 2; i <= n; ++i) {
        res *= i;
        if (i == n) {
            results[0] = res;
        }
        if (i == r) {
            results[1] = res;
        }
        if (i == n - r) {
            results[2] = res;
        }
    }
}

// if (results[n] != 0) {
//         return;
//     }
//     else if (n == 0 || n == 1) {
//         results[n] = 1;
//     } else {
//         for(int i = 2; i <= n; ++i ) {
//             results[i] = results[i - 1] * i;
//         }
//     }