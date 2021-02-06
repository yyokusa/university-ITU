#include <stdio.h>
#include <math.h>

#define G 9.8
#define T(x) sqrt(2*(x) / (float)G);

int calc_tot_dist(double init_height, int num_of_hits);
int calc_tot_time(double init_height, int num_of_hits);
//int T(double x); 

int main()
{

    double init_height = 0.0;
    double tot_dist = 0.0;
    double tot_time = 0.0;
    int num_of_hits = 0;

    printf("init h: ");
    scanf("%lf", &init_height);
    printf("num of hits : ");
    scanf("%d", &num_of_hits);

    tot_dist = calc_tot_dist(init_height, num_of_hits);
    tot_time = calc_tot_time(init_height, num_of_hits);

    printf("dist: %lf \n", tot_dist);
    printf("time: %lf \n", tot_time);
    return 0;
}

int calc_tot_dist(double init_height, int num_of_hits)
{
    double res = init_height;
    for (int i = 0; i < num_of_hits - 1; i++)
    {
        init_height = init_height * (3.0/4.0);
        res += (init_height * 2);
    }
    return res;
}

int calc_tot_time(double init_height, int num_of_hits)
{
    double res = 0.0;
    res += T(init_height);
    for (int i = 0; i < num_of_hits - 1; i++)
    {
        init_height = init_height * (3.0/4.0);
        res += 2 * T(init_height);
    }
    return res;
}

// int T(double x) 
// {
//     return sqrt(2*(x)) / (float)G;
// } 