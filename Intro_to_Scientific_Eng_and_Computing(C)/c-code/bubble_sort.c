// Optimized Bubble sort in C
#include <stdio.h>
void bubbleSort(int array[], int size)
{
    for (int step = 0; step < size - 1; ++step)
    {
        int swapped = 0;
        for (int i = 0; i < size - step - 1; ++i)
        {
            // To sort in descending order, change > to < in this line.
            if (array[i] > array[i + 1])
            {
                int temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;
                swapped = 1;
            }
        }
        // If there is no swap in the loop, then the array is already sorted
        if (swapped == 0)
            break;

    }

}
void printArray(int array[], int size)
{
    for (int i = 0; i < size; ++i)
    {
       printf("%d  ", array[i]);
    }
    printf("\n");
}
int main()
{
    int data[] = {-2, 45, 0, 11, -9};
    int size = sizeof(data) / sizeof(data[0]);
    bubbleSort(data, size);
    printf("Sorted Array in Ascending Order:\n");
    printArray(data, size);
}

    


// #include <stdio.h> //putchar() getchar()
// #include <stdbool.h>

// #define SIZE 11

// void swap(int *a, int *b);
// void bubble_sort(int sales[], int);
// void print_array(int[], int);

// int main(int argc, char const *argv[])
// {
//     int sales[SIZE] = {-5, 6, 4, 23, 12, 32, -4, 7, -6, 8, -5};
//     printf("initial array:\n");
//     print_array(sales, SIZE);
//     bubble_sort(sales, SIZE);
//     printf("after calling sort:\n");
//     print_array(sales, SIZE);
//     return 0;
// }

// void bubble_sort(int sales[], int size)
// {
//     // if you replace size - 1 items in the right order, the last one also replaced in the correct position
//     for (size_t i = 0; i < size - 1; i++)
//     {
//         // bool are_swapped = false;
//         for (size_t j = 0; j < size - i - 1; j++)
//         {
//             // if (sales[j] > sales[j + 1]) { swap(&sales[j], &sales[j+1]); are_swapped = true;}
//             if (sales[j] > sales[j + 1]) { swap(&sales[j], &sales[j+1]);}
//         }
//         // if (!are_swapped) {break;}
//     }
// }

// void swap(int *a, int *b)
// {
//     int temp = *a;
//     *a = *b;
//     *b = temp;
// }

// void print_array(int arr[], int size)
// {
//     for (size_t i = 0; i < size; i++)
//     {
//         printf("%d ", arr[i]);
//     }
//     printf("\n");
// }
