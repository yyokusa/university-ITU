#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10

double calculate_cumulative_average(int nums[], int size);
double calculate_moving_average(int nums[], int size, int n);
void generate_random_array(int* nums, int size);
void print_array(int* nums, int size);

int main()
{
    int *nums = (int *) malloc(sizeof(int) * SIZE);
    generate_random_array(nums, SIZE);
    fprintf(stdout, "randomly generated array is: \n");
    print_array(nums, SIZE);
    double cumulative_average = calculate_cumulative_average(nums, SIZE);
    int moving_avg_n = 0;
    fprintf(stdout, "enter n for moving avg: \n");
    fscanf(stdin, "%d", &moving_avg_n);
    double moving_average = calculate_moving_average(nums, SIZE, moving_avg_n);
    fprintf(stdout, "cumulative_average result is : %lf\n", cumulative_average);
    fprintf(stdout, "moving_average result is : %lf\n", moving_average);
	return 0;
}

double calculate_cumulative_average(int nums[], int size)
{
    double total = 0;
    for (size_t i = 0; i < size; i++)
    {
        total += nums[i];
    }
    return total / size;
}

double calculate_moving_average(int nums[], int size, int n)
{
    double total = 0;
    for (size_t i = size - n; i < size; i++)
    {
        total += nums[i];
    }
    return total / (n);
}

void generate_random_array(int* nums, int size)
{
    srand(time(0));
    for (size_t i = 0; i < size; i++)
    {
        int number = rand() % 100;
        nums[i] = number;
    }
}
void print_array(int* nums, int size)
{
    for (size_t i = 0; i < size; i++)
    {
        fprintf(stdout, "%d ", nums[i]);
    }
    fprintf(stdout, "\n");
}