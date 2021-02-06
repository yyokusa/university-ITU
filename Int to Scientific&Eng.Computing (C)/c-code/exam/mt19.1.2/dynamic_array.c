#include <stdio.h>
#include <stdlib.h>

void double_the_size(int ptr[], int array_length);
void print_array(int ptr[], int array_length);

int main(int argc, char const *argv[])
{
    int array_length = 2;
    int* ptr;
	int i = 0;
	
	ptr = (int*)malloc(array_length * sizeof(int)); 
    printf("Enter array elements: \n");
    // scanf("%d", &(*(ptr)) );      // *arr = arr[0]        !!!!      *ptr = ptr[0]
    
	// while (scanf("%d", &(*(ptr + i))) != EOF)
	while (scanf("%d", &(ptr[i])) != EOF)
	{
		if (i == array_length - 1)
		{
			double_the_size(ptr, array_length);
			array_length *= 2;
		}
		++i;
	}
	print_array(ptr, array_length);

    return 0;
}
/*
Firstly, realloc might decide to

1-    Allocate a new memory block, copy data, and free the original one, or

2-    Simply expand/contract the original block "in place" without allocating the new one. 
*/

void double_the_size(int ptr[], int array_length) {
	// printf("%p\n",&ptr[0]);
	// printf("%d\n",ptr[0]);
	ptr = realloc(ptr, 2 * array_length * sizeof(int));					
	// printf("%p\n",&ptr[0]);
	// printf("%d\n",ptr[0]);
	if (ptr == NULL) { 
		printf("Memory not allocated.\n"); 
	}
	else { 
		printf("Memory successfully allocated using malloc.\n"); 
	}
}


void print_array(int ptr[], int size) {                         	// how you declare ptr variable is very important	
	printf("The elements of the array are: "); 	
	for (int i = 0; i < (size); ++i) { 
		printf("\nelement %d: %d\n", i, ptr[i]);				 	
	} 
}




/*
//Without realloc

int *double_the_size(int ptr[], int array_length);

int main(int argc, char const *argv[])
{
    int array_length = 2;
    int *ptr;
    int *array;
    int i = 0;

    array = (int *)malloc(array_length * sizeof(int));
    printf("Enter array elements: \n");
    // scanf("%d", &(*(ptr)) );      // *arr = arr[0]        !!!!      *ptr = ptr[0]

    // while (scanf("%d", &(*(ptr + i))) != EOF)
    while (scanf("%d", &(array[i])) != EOF)
    {
        if (i == array_length - 1)
        {
            ptr = double_the_size(array, array_length);
            array_length *= 2;
            array = ptr;
        }
        ++i;
    }
    print_array(ptr, array_length);

    return 0;
}

int *double_the_size(int ptr[], int array_length)
{

    int *newptr = (int *)malloc(sizeof(int) * array_length * 2);
    if (ptr == NULL)
    {
        printf("Memory not allocated.\n");
    }
    else
    {
        printf("Memory successfully allocated using malloc.\n");
    }
    for (size_t i = 0; i < array_length; i++)
    {
        newptr[i] = ptr[i];
    }
    printf("Memory successfully copied to new array.\n");
    free(ptr);
    return newptr;
}
*/