#include <stdio.h>

void add(int *arr, int size, char way);
int shift(int *arr, int size, char way);
void print(int arr[], int size);

#define SIZE 20

int main()
{

    int arr[SIZE] = {4, 2, 2, 4, 8, 2, 2, 4, 8, 0, 10,10,20,4,4,2,2,4,4,4};
    print(arr, SIZE);
    char way = way;
    int flag = 1;
    while(flag) 
    {
        add(arr, SIZE, way);
        flag = shift(arr,SIZE,way);
        print(arr, SIZE);
        way = way == 'r' ? 'w' : 'r';
    }
    return 0;
}

void print(int arr[], int size) {
    for(int i = 0; i < size; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void add(int *arr, int size, char way)
{
    if (way == 'r')
    {
        for (int i = size - 1; i > 0; i--)
        {
            if (arr[i] == arr[i - 1])
            {
                arr[i - 1] = 0;
                arr[i] *= 2;
                i--;
            }
        }
    }
    else if (way == 'l')
    {
        for (int i = 0; i < size - 1; i++)
        {
            if (arr[i] == arr[i + 1])
            {
                arr[i + 1] = 0;
                arr[i] *= 2;
                i++;
            }
        }
    }
}

int shift(int *arr, int size, char way)
{
    int flag = 1;
    if (way == 'r')
    {
        for (int i = size - 1; i >= 0; i--)
        {
            for (int j = size - 1; j >= i; j--)
            {
                if (arr[i] != 0 && arr[j] == 0)
                {
                    arr[j] = arr[i];
                    arr[i] = 0;
                    flag = 0;
                    break;
                }
                else
                {
                    continue;
                }
            }   
        }
    }
    else if (way == 'l')
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j <= i; j++)
            {
                if (arr[i] != 0 && arr[j] == 0)
                {
                    arr[j] = arr[i];
                    arr[i] = 0;
                    flag = 0;
                    break;
                }
                else
                {
                    continue;
                }
            }   
        }
    }
    return flag;
}