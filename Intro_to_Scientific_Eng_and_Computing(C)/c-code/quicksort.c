#include <stdio.h>
#include <stdlib.h>

void quicksort(int arr[], int low, int high);
int partition(int arr[], int low, int high);
void swap(int* a, int* b);

int main(int argc, char const *argv[])
{
    int arr[] = {20, 89, 12, 21, 39, 19, 65, 2, 30};
    /*
    The sizeof way is the right way iff you are dealing with arrays not received as parameters.
    An array sent as a parameter to a function is treated as a pointer, so sizeof will return the pointer's size,
    instead of the array's. Thus, inside functions this method does not work. 
    Instead, always pass an additional parameter size_t size indicating the number of elements in the array.
    */
    int arr_len = sizeof(arr) / sizeof(arr[0]);
    printf("%d \n",arr_len);
    for (int i = 0; i < arr_len; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    quicksort(arr, 0, arr_len - 1);

    for (int i = 0; i < arr_len; i++)
    {
        printf("%d ", arr[i]);
    }
    return 0;
}

void quicksort(int arr[], int low, int high) {
    if(low < high) {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}


/* This function takes last element as pivot, places 
   the pivot element at its correct position in sorted 
    array, and places all smaller (smaller than pivot) 
   to left of pivot and all greater elements to right 
   of pivot */
int partition (int arr[], int low, int high) 
{ 
    int pivot = arr[high];    // pivot 
    int i = (low - 1);  // Index of smaller element 
  
    for (int j = low; j <= high- 1; j++) 
    { 
        // If current element is smaller than the pivot 
        if (arr[j] < pivot) 
        { 
            i++;    // increment index of smaller element 
            swap(&arr[i], &arr[j]); 
        } 
    } 
    swap(&arr[i + 1], &arr[high]); 
    return (i + 1); 
}
// int partition(int arr[], int low, int high) {
//     int pivot = arr[high]; // choose last var , arr[size - 1], as pivot var
//     int index_var = low;    // first element bigger than pivot_var
//     for(int j = 0; j < high; ++j) {
//         if(arr[j] < pivot) {
//             swap(&arr[j], &arr[index_var]);
//             ++index_var;  
//         }
//     }
//     --index_var;            //segmentation fault
//     swap(&pivot, &arr[index_var]);
//     return index_var;
// }


void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}