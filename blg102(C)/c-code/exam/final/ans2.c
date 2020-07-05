#include <stdio.h>
#include <math.h>


int main()
{
    double value = 0.0;
    double root_guess = 0.0;
    double closeness = 0.0;
    double result = 0.0;
    puts("value: ");
    scanf("%lf",&value);
    puts("initial root guess: ");
    scanf("%lf",&root_guess);
    puts("closeness: ");
    scanf("%lf",&closeness);
    result = root_guess * root_guess;
    printf("   x            x-square\n");
    printf("==========   ===========\n");
    printf("%3.3lf   %8.4lf\n", root_guess, result);
    while (closeness <= result - value)
    {
        double x = root_guess; 
        root_guess = (x + (value/x))/2;
        result = root_guess * root_guess;
        printf("%3.3lf   %8.4lf\n", root_guess, result);
    }
    return 0;
}
