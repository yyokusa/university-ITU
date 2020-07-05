#include <stdlib.h>
#include <stdio.h>
#include <math.h>
double f(double x, double a, double b, double c);    
double derivative_func(double x, double a, double b);

#define EPSILON 0.001

int main() {
    double x_guess;
    double x_approx;
    double error = 0.0;
    double a, b, c;
    printf("a, b, c:\n");
    scanf("%lf %lf %lf",&a,&b,&c);
    printf("guess x:\n");
    scanf("%lf", &x_guess);

    x_approx = x_guess - f(x_guess,a,b,c) / derivative_func(x_guess,a,b);
    error = fabs(x_guess - x_approx);
    x_guess = x_approx;
    printf("x is %lf, y is %lf\n", x_guess, f(x_guess,a,b,c));
    
    if(0 == error) {
        printf("guess is true, root is %lf", x_guess);
        return EXIT_SUCCESS;
    }
    while (error > EPSILON)
    {
        x_approx = x_guess - f(x_guess,a,b,c) / derivative_func(x_guess,a,b);
        error = fabs(x_guess - x_approx);
        x_guess = x_approx;
        printf("x is %lf, y is %lf\n", x_guess, f(x_guess,a,b,c));
    }
    return EXIT_SUCCESS;
}

double f(double x, double a, double b, double c){
    return (a*x*x + b*x + c);
}
double derivative_func(double x, double a, double b){
    return (2*a*x + b);
}