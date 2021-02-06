#include <stdio.h>
#include <stdlib.h>

int find_average();

int main(int argc, char const *argv[])
{
    find_average();
    return 0;
}

int find_average() {

    double input_num;
    double sum_of_pos = 0.0;
    double sum_of_neg = 0.0;
    double res_pos_average = 1.0;
    double res_neg_average = 1.0;
    int pos_counter = 0;
    int neg_counter = 0;
    
    printf("enter a number\n");
    while (scanf("%lf", &input_num) == 1) //scanf works as expected      !!!!!!! https://en.cppreference.com/w/c/io/fscanf
    {    
        if (input_num >= 0) // num is positive
        {
            sum_of_pos += input_num;
            ++pos_counter;
        }
        else if (input_num < 0) // num is negative
        {
            sum_of_neg += input_num;
            ++neg_counter;
        }
        printf("enter a number\n");
    }

    printf("%lf\n", sum_of_pos);
    printf("%lf\n", sum_of_neg);
    printf("%d\n", pos_counter);
    printf("%d\n", neg_counter);
    res_pos_average = sum_of_pos / pos_counter;
    res_neg_average = sum_of_neg / neg_counter;
    printf("%lf\n", res_pos_average);
    printf("%lf\n", res_neg_average);
    
    printf("This is not a number.\n");
    return EXIT_FAILURE;
    // figure out what to use to get input until user presses chars like this '_'  ???
    
}