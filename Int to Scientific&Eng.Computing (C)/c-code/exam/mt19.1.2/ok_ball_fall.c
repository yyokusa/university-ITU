#include <stdio.h>
#include <math.h>

double total_height(double *init_height, double n_of_hits);
double total_time(double *init_height, double n_of_hits);

int main(int argc, char const *argv[])
{
    double init_height;
    double n_of_hits;
    double result1;
    double result2;

    scanf("%lf", &init_height);
    scanf("%lf", &n_of_hits);

    result1 = total_height(&init_height, n_of_hits);
    result2 = total_time(&init_height, n_of_hits);

    printf("%.2lf\n", result1);
    printf("%.2lf\n", result2);
    return 0;
}

double total_height(double *init_height, double n_of_hits)
{
    double result = *init_height;
    double height;
    for (size_t i = 2; i <= n_of_hits; i++)
    {
        height = *init_height * (3 / 4);
        result += 2 * height;
    }
    return result;
}

double total_time(double *init_height, double n_of_hits)
{
    double result = sqrt(2 * (*init_height) / (9.8));
    double height;
    for (size_t i = 2; i <= n_of_hits; i++)
    {
        height = *init_height * (3 / 4);
        result += 2 * sqrt(2 * (height) / (9.8));
    }
    return result;
}