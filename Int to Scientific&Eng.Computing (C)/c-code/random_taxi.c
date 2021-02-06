// reverse an array
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 20

void swap(int *a, int *b);
void shuffle_array(int *nums, int size);
void fill_array(int *nums, int size);
void swap(int *a, int *b);
void reverse_array(int *nums, int size);
void print_array(int *nums, int size);

int main()
{
    int nums[SIZE];
    fill_array(nums, SIZE);
    fprintf(stdout, "taxis: \n");
    print_array(nums, SIZE);

    shuffle_array(nums, SIZE);
    fprintf(stdout, "original array: \n");
    print_array(nums, SIZE);
    
    
    reverse_array(nums, SIZE);
    fprintf(stdout, "reversed array:\n");
    print_array(nums, SIZE);

    
    return EXIT_SUCCESS;
}

void shuffle_array(int *nums, int size)
{
    srand(time(0));
    for (size_t i = 0; i < size; i++)
    {
        int taxi1 = rand() % SIZE;
        int taxi2 = rand() % SIZE;
        swap(&nums[taxi1], &nums[taxi2]);
    }
}

void fill_array(int *nums, int size)
{
    for (size_t i = 0; i < size; i++)
    {
        nums[i] = i;
    }
}
void print_array(int *nums, int size)
{
    for (size_t i = 0; i < size; i++)
    {
        // fprintf(stdout, "%-5d ", nums[i]);
        fprintf(stdout, "%d ", nums[i]);
    }
    fprintf(stdout, "\n");
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void reverse_array(int *nums, int size)
{
    for (size_t i = 0; i < size / 2; i++)
    {
        swap(&nums[i], &nums[size - 1 - i]);
    }
}
