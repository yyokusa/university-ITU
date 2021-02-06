#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 1000

int weird_op(int* arr, int len);
int pop(int* arr, int len);
void push(int* arr, int len, int val);
void print_arr(int arr[], int size);

int main()
{
    int* arr = (int* ) malloc(sizeof(int) * SIZE);
    int inp = -1;
    int len = 0;
    int val = 0;
    while(inp != 0) 
    {
        switch (inp)
        {
        case 1:
            puts("Enter val");
            scanf("%d", &val);
            len++;
            push(arr, len, val);
            print_arr(arr, len);
            break;
        case 2:
            puts("Pop");
            pop(arr, len);
            print_arr(arr, len);
            len--;
            break;
        case 3:
            puts("adding last two removing 2 replacing ..");
            weird_op(arr, len);
            print_arr(arr, len);
            len--;
            break;
        case 0:
            return EXIT_SUCCESS;
            break;
        default:
            break;
        }
        puts("Enter menu item");
        scanf("%d", &inp);
    }
    print_arr(arr, len);
    free(arr);
    return EXIT_SUCCESS;
}

void push(int* arr, int len, int val) {
    arr[len - 1] = val;
}

int pop(int* arr, int len) {
    int val = arr[len - 1];
    arr[len - 1] = 0; // ?????????
    return val;
}

int weird_op(int* arr, int len) {
    int val1 = arr[len - 1];
    int val2 = arr[len - 2];
    arr[len - 2] = val1 + val2;
    arr[len - 1] = 0;
    return val1 + val2;
}


void print_arr(int arr[], int size) {
    for(int i = 0; i < size; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");

}