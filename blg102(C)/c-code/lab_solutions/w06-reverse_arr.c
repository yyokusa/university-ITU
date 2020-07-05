#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void reverse(int* arr, int size);
void print_arr(int* arr, int size);    
void swap(int* arr, int left, int right);


int main()
{
    int arr[10] = {5,2,0,12,9,23,32,5,4,2};
    int size = 10;
    int* arr_ptr = arr;
    reverse(arr_ptr, size);
    print_arr(arr_ptr, size);
    return 0;
}


void reverse(int* arr, int size) {
    if (size <= 1) {
        return;
    }
    int left = 0;   // index of first element
    int right = size - 1; // index of last element
    while (right > left) {  // we might have also used for loop with int i = 0; i < size/2 ....
        swap(arr, left, right);
        --right;
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