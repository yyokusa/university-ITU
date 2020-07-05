#include <stdio.h>
#include <math.h>

#define EPSILON 0.00001

typedef struct func
{
    double a;
    double b;
    double c;
} Func;

double find_derivative(Func *f, double k);
double generate_func_result(Func *f, double x);
double find_root(Func *f, double xold);

int main()
{
    Func f;
    double xinit = 0;
    fprintf(stdout, "func katsayilar: ");
    fscanf(stdin, "%lf %lf %lf", &f.a, &f.b, &f.c);
    fprintf(stdout, "initial guess: ");
    fscanf(stdin, "%lf", &xinit);
    fprintf(stdout, "result is: %lf\n", find_root(&f, xinit));
    return 0;
}

double find_root(Func *f, double xold)
{
    double xnew = 0;
    xnew = xold - (generate_func_result(f, xold) / find_derivative(f, xold));
    double error = fabs(xnew - xold);
    xold = xnew;
    printf("x is %lf, y is %lf\n", xold, generate_func_result(f, xold));
    while (error > EPSILON)
    {
        xnew = xold - (generate_func_result(f, xold) / find_derivative(f, xold));
        printf("x is %lf, y is %lf\n", xold, generate_func_result(f, xold));
        error = fabs(xnew - xold);
        xold = xnew;
    }
    printf("x is %lf, y is %lf\n", xold, generate_func_result(f, xold));
    return xnew;
}

double generate_func_result(Func *f, double x)
{
    return (f->a) * x * x + (f->b) * x + (f->c);
}

double find_derivative(Func *f, double k)
{
    return 2 * (f->a) * k + (f->b);
}