#include <stdio.h>

double get_no_of_digits(double x0, int n);

int main(int argc, char const *argv[])
{
    double x0;
    int n;
    printf("enter x and n: ");
    scanf("%lf %d", &x0, &n);
    printf("Result is %lf: ", get_no_of_digits(x0, n));
    return 0;
}

double get_no_of_digits(double x0, int n)
{
    double term = x0;
    double result = x0;
    int denominator = 2;
    int sign = -1;
    while (--n)
    {
        double temp = term * x0;
        result += sign * (temp / denominator++);
        sign = -sign;
        term = temp;
    }
    return result;
}