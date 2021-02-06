#include <stdlib.h>
#include <stdio.h>
#include <math.h>
double f(double x, double a, double b, double c);
double f_der(double x, double a, double b);

#define EPSILON 2.71

int main()
{
    double x_guess;
    //double x_approx;
    double y_1;
    double y_2 = 0.0;
    scanf("%lf", &x_guess);

    printf("a, b, c:\n");
    double a, b, c;
    a = b = c = 0.0;
    scanf("%lf%lf%lf", &a, &b, &c);
    double error = 0.0;
    error = fabs(f(x_guess, a, b, c) - f_der(x_guess, a, b));
    while (error > 2 * EPSILON)
    {
        x_guess = x_guess - fabs(f(x, a, b, c) / f_der(x, a, b));
        printf("%lf\n", x_guess);
    }
    return 0;
}

double f(double x, double a, double b, double c)
{
    return (a * x * x + b * x + c);
}
double f_der(double x, double a, double b)
{
    return (2 * a * x + b);
}