#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubble_sort(int* arr, int size);
void print_arr(int* arr, int size);    
void swap(int* arr, int left, int right);


int main()
{
    int arr[100] = {5,2,0,12,9,23,32,5,4,2};
    int size = 100;
    int* arr_ptr = arr;
    bubble_sort(arr_ptr, size);
    print_arr(arr_ptr, size);
    return 0;
}


void bubble_sort(int* arr, int size) {
    if (size <= 2) {
        return;
    }
    int upper_bound = size;
    int left = 0;
    int right = 1;
    while (right <= upper_bound) {
        if (right == upper_bound) {
            --upper_bound;
            left = 0;
            right = 1;
            continue;
        }
        if (arr[left] > arr[right]) {
            swap(arr, left, right);
        }
        ++right;
        ++left;
    }
}

void print_arr(int* arr, int size) {
    printf("printing array:\n");
    for (int i = 0; i < size; ++i) {
        printf("%d, ", arr[i]);
    }
}

void swap(int* arr, int left, int right) {
    int temp = 0;
    temp = arr[left];
    arr[left] = arr[right];
    arr[right] = temp;
}