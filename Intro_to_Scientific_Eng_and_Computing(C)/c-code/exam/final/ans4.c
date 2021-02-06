#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 10

//int* double_size(int* arr, int size);
void print_arr(int arr[], int size);


int main()
{
    int i = 0;
    int size = 2;
    int* arr = (int*) malloc(sizeof(int) * size);
    int inp = 0;
    int a = 0;
    while ((a = scanf("%d", &inp)) != EOF) {
        arr[i++] = inp;
        if(i == size) {
            // arr = double_size(arr, size);
            arr = realloc(arr, 2*size);
            size *= 2;
        }
        
    }
    print_arr(arr, size);
    free(arr);
    return 0;
}

// int* double_size(int* arr, int size) {
//     int new_size = 2 * size;
//     int* new_arr = (int *) malloc(sizeof(int) * new_size);
//     for (int i = 0; i < size; i++)
//     {
//         new_arr[i] = arr[i];
//     }
//     free(arr);
//     return new_arr;
// }

void print_arr(int arr[], int size) {
    for(int i = 0; i < size; ++i) {
        printf("%d ", arr[i]);
    }
}