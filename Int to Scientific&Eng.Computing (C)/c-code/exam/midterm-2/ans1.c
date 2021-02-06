#include <stdio.h>


double series(int nums) ;
double parallel(int nums);

int main()
{
    char connection_type = 'P';
    int nums = 0;
    puts("P for parallel, S for series");
    scanf("%c", &connection_type);
    puts("num of resistors: ");
    scanf("%d", &nums);
    char c;

    while (1){
        double result = connection_type == 'P' ? parallel(nums) : series(nums);
        while((c = getchar()) != '\n');
        printf("results is %lf\n", result);
        printf("P for parallel, S for series\n");
        printf("X for exit\n");
        scanf("%c", &connection_type);
        if (connection_type == 'X') {
            break;
        }
        printf("num of resistors: \n");
        scanf("%d", &nums);
    } 

    return 0;
}

double parallel(int nums) 
{
    
    double res = 0;
    double value = 0;
    for (int i = 0; i < nums; i++)
    {
        printf("Value of R: \n");
        scanf("%lf", &value);
        res += (1.0 / value);
    }
    return (1.0 / res);    
}
double series(int nums) 
{
    double res = 0;
    double value = 0;

    for (int i = 0; i < nums; i++)
    {
        printf("Value of R: \n");
        scanf("%lf", &value);
        res += (value);
    }
    return res;
}

