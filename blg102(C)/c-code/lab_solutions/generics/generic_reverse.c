#include <stdio.h> // fgets

#define SIZE 10
#define NULL (void *) 0

void generic_swap(void *vp1, void *vp2, size_t byte_size)
{
    unsigned char *ptr1 = (unsigned char *)vp1;
    unsigned char *ptr2 = (unsigned char *)vp2;
    while (byte_size--)
    {
        unsigned char temp = *ptr1;
        *ptr1++ = *ptr2;
        *ptr2++ = temp;
    }
}
void generic_reverse(void *vp1, size_t arr_size, size_t byte_size)
{
    unsigned char *ptr1 = (unsigned char *)vp1;
    unsigned char *ptr2 = (unsigned char *)vp1;
    for (size_t i = 0; i < arr_size / 2; i++)
    {
        generic_swap(ptr1 + (i)*byte_size, ptr2 + (arr_size - 1 - i) * byte_size, byte_size);
    }
}

void *generic_search(const void *vp_source, size_t arr_size, size_t byte_size, const void *vp_val)
{
    unsigned char *ptr1 = (unsigned char *)vp_source;
    unsigned char *val = (unsigned char *)vp_val;
    for (size_t i = 0; i < arr_size; i++)
    {
        if (*ptr1 == *val)
        {
            return ptr1;
        }
        ptr1 += byte_size;
    }
    // for (size_t i = 0; i < arr_size*byte_size; i++)
    // {
    //     if (*ptr1 == *val)
    //     {
    //         return ptr1;
    //     }
    //     ptr1++;
    // }
    return NULL;
}

int main()
{
    int arr[SIZE] = {1, 2, 3, 4, 5, 6, 12, 35, 0, 12};
    // generic_reverse(arr, 10, sizeof(int));
    // for (int i = 0; i < SIZE; ++i)
    // {
    //     printf("%d ", *(arr + i));
    // }
    // printf("\n");

    // int *p = NULL;
    // int a = 5;
    // if ((p = (int*) generic_search(arr, SIZE, sizeof(int), &a)) == NULL) {
    //     printf("something went wrong \n");
    // } else {
    //     printf("index of element with the value %d is %ld \n", a, p - arr);
    // }

    return 0;
}
