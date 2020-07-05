#include <stdio.h> // fgets
//#include <stdlib.h> // atoi
//#include <string.h> // strlen, strcpy

void *memchr1(const void *src, int val, size_t n)
{
    unsigned char *ptr = (unsigned char *)src;
    for (int i = 0; i < n; ++i)
        if (ptr[i] == val)
            return (ptr + i);

    return NULL;
}

int main()
{
    // double doubles[10] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 100.0, 9.2, 0.0, 12.2};
    // double *p = NULL;
    // char c[10] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'j', 'k'};
    // char *p = NULL;
    // int nums[10] = {1, 2, 3, 4, 5, 6, 100, 9, 0, 12};
    // int *p = NULL;

    // chars if (!(p = (char *)memchr1(c, 'e', sizeof(c))))
    // {
    //     printf("No instance of that char \n");
    // }
    // else
    // {
    //     printf("%ld \n", p - c);
    // }

    // int if (!(p = (int *)memchr1(nums, 782, sizeof(nums))))
    // {
    //     printf("No instance of that num \n");
    // }
    // else
    // {
    //     printf("%ld \n", p - nums);
    // }

    // //double
    // if (!(p = (double *)memchr1(doubles, 1.0, sizeof(doubles))))
    // {
    //     printf("No instance of that double \n");
    // }
    // else
    // {
    //     printf("%ld \n", p - doubles);
    // }
    return 0;
}
