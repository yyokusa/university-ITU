#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define ITERATIONS 10000

double estimate_pi(int iterations);

int main()
{
    fprintf(stdout, "estimation of pi is %lf", estimate_pi(ITERATIONS));
    return 0;
}

double estimate_pi(int iterations)
{
    srand(time(0));
    int square_dots = 0;
    int circle_dots = 0;
    double dotX = 0;
    double dotY = 0;
    while (iterations--)
    {
        dotX = (rand() % 50) / 100.0;
        dotY = (rand() % 50) / 100.0;

        if (sqrt(dotX * dotX + dotY * dotY) < 0.5)
        {
            circle_dots++;
        }
        square_dots++;
    }
    // printf("%d\n", circle_dots);
    // printf("%d\n", square_dots);
    return 4.0 * (float)circle_dots / (float)square_dots;
}