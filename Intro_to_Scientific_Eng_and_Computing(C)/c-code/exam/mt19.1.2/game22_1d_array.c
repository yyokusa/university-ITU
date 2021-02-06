#include <stdio.h>

int add_elements(int arr[], int size,int side);
int shift_elements(int arr[], int size,int side);
void print_arr(int arr[], int size);

int main()
{
    int flag = 1;
    int side = 1;
    const int size = 10;
    int arr[size] = {4, 2, 2, 4, 8, 2, 2, 4, 8}; // last element set to zero
    for (int i = 0; i < size; i++)
    {
        printf("enter element: ");
        scanf("%d", &arr[i]);
    }
    print_arr(arr,size);
    while(flag) {
        if (side)
        {
            flag = add_elements(arr, size, 1); //rigth
            printf("added elements: ");print_arr(arr,size);
            side = shift_elements(arr, size, 1); //rigth
            printf("shifted elements: ");print_arr(arr,size);
            print_arr(arr,size);
        } else {
            flag = add_elements(arr, size, 0); //left
            printf("added elements: ");print_arr(arr,size);
            side = shift_elements(arr, size, 0); //left
            printf("shifted elements: ");print_arr(arr,size);
        }
        print_arr(arr,size);
    }
    // flag = add_elements(arr, size, 1); //rigth
    // side = shift_elements(arr, size, 1); //rigth
    // // flag = add_elements(arr, size, 1); //rigth
    // printf("%d", flag);
    // printf("%d", side);
    print_arr(arr, size);
    return 0;
}
int add_elements(int arr[], int size,int side) {
    int flag = 0;
    if (side == 1) // add rigth
    {
        for (int i = size - 1; i > 0; --i)
        { 
            if (arr[i] == arr[i - 1] && arr[i] != 0)
            {   flag = 1;
                arr[i] *= 2;
                arr[i - 1] = 0;
            }   
        }
    }
    else if (side == 0) // add left
    {
        for (int i = 0; i < size - 1; i++)
        { 
            if (arr[i] == arr[i + 1] && arr[i] != 0) {
                flag = 1;
                arr[i] *= 2;
                arr[i + 1] = 0;
            }    
        }
    }
    return flag;
}

int shift_elements(int arr[], int size,int side) {
    
    if (side == 1) // shift rigth
    {
        int j = size - 1;
        for (int i = size - 1; i >= 0; --i)
        {
            if (arr[i] != 0)
            {
                if (arr[j] == 0)
                {
                    arr[j] = arr[i];
                    arr[i] = 0;
                    --j;
                }       
            }
        }        
    }
    else if (side == 0) // shift left
    {
        int j = 0;
        for (int i = 0; i < size; ++i)
        {
            if (arr[i] != 0 && i != 0)
            {
                if (arr[j] == 0)
                {
                    arr[j] = arr[i];
                    arr[i] = 0;
                    ++j;
                }       
            }
        }        
    }
return side == 1 ? 0 : 1;
}

void print_arr(int arr[], int size){
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}