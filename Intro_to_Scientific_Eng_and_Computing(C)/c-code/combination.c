#include <stdio.h>
#include <time.h>

long double factorial_with_x(double n, double x);
long double combination(double n, double r);
long double better_combination(double n, double r);
int main()
{
    long double a = 0;
    long double b = 0;
    fprintf(stdout, "enter n and r: ");
    fscanf(stdin, "%Lf %Lf", &a, &b);
    clock_t t; 
    t = clock(); 
    fprintf(stdout, "result: %Lf\n", combination(a, b));
    t = clock() - t; 
    long double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
    printf("fun() took %Lf seconds to execute \n", time_taken); 
    
    t = clock(); 
    fprintf(stdout, "result: %Lf\n", better_combination(a, b));
    t = clock() - t; 
    time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
    printf("better one () took %Lf seconds to execute \n", time_taken); 
    return 0;
}

long double better_combination(double n, double r)
{
    long double term2 = factorial_with_x(r, 0);
    long double term3 = factorial_with_x(n - r, r);
    term3 = term2 * term3;
    long double temp = r > (n - r) ? r : (n - r);
    long double term1 = factorial_with_x(n, temp);
    long double temp2 = term2 > term3 ? term2 : term3;
    term1 = term1 * temp2;
    return term1 / (term2 * term3);
}

long double combination(double n, double r)
{
    long double term1 = factorial_with_x(n, 0);
    long double term2 = factorial_with_x(r, 0);
    long double term3 = factorial_with_x(n - r, 0);
    return term1 / (term2 * term3);
}

long double factorial_with_x(double n, double x)
{
    if (n == 0)
        return 0;
    long double res = n;

    while (--n > x)
    {
        res *= n;
    }
    return res;
}