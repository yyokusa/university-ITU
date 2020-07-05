#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define SIZE 10

void gen_rand_array(int*, const int);
void print_array(int* ptr, const int size);
int* get_min(int*, const int);
void selection_sort(int* ptr, const int size);
void swap(int* ptr, int* ptr2);
//int* get_max(int*, const int);

int main() {
    //int arr[SIZE];
    int ptr[SIZE];
    int* min_ptr;
    gen_rand_array(ptr, SIZE);
    print_array(ptr,SIZE);
    // min_ptr = get_min(ptr, SIZE);
    // printf("%d ", *min_ptr);
    printf("\n");
    selection_sort(ptr, SIZE);
    print_array(ptr,SIZE);
    printf("\n");

    return 0;
}

void gen_rand_array(int* ptr, const int size) {
    srand(time(0));
    for(int i = 0; i < size; ++i) {
        *(ptr + i) = rand() % 55;
    }
}

void print_array(int* ptr, const int size) {
    for(int i = 0; i < SIZE; ++i) {
        printf("%d ",*(ptr + i));
    }
}    

int* get_min(int* ptr, const int size) {
    int* min_ptr = ptr;
    for(int i = 0; i < size; ++i) {
        if(*(ptr + i) < *min_ptr) {
            min_ptr = ptr + i;
        }
    }
    return min_ptr;
}
int* get_max(int* ptr, const int size) {
    int* max_ptr = ptr;
    for(int i = 0; i < size; ++i) {
        if(*(ptr + i) > *max_ptr) {
            max_ptr = ptr + i;
        }
    }
    return max_ptr;
}
void selection_sort(int* ptr, const int size) {
    int* left_boundary = ptr;
    int* min_ptr;
    int i = 0;
    while(left_boundary != (ptr + SIZE)) {
        min_ptr = get_min(ptr + i, size - i);
        swap(left_boundary, min_ptr);
        ++left_boundary;
        ++i;
    }
}

void swap(int* ptr, int* ptr2) {
    int temp = *ptr;
    *ptr = *ptr2;
    *ptr2 = temp;
}