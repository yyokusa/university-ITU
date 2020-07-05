#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM 2
#define SIZE 5
void print_array(char arr[], int len);
void rotate_rigth(char dst[], char src[], int num, int str_size);

int main()
{
	char source[SIZE] = "hello";
	char destination[SIZE] = {'\0'};
	int size = sizeof(source) / sizeof(source[0]);
	fprintf(stdout, "size: %d\n", size);
	
	print_array(source, SIZE);
	rotate_rigth(destination, source, NUM, SIZE);
	print_array(destination, SIZE);
	return 0;
}

void rotate_rigth(char dst[], char src[], int num, int len)
{
	for (size_t i = 0; i < num; i++)
	{
		dst[i] = src[len - num + i];
	}
	for (size_t i = 0; i < len - num; i++)
	{
		dst[i + num] = src[i];
	}
}

void print_array(char arr[], int len)
{
    for (size_t i = 0; i < len; i++)
	{
        printf("%c", arr[i]);
    }
    printf("\n");
}