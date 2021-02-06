#include <stdio.h>
#include <stdbool.h>

bool equals(int[], int, int[], int);

int main()
{

	int arr_a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int arr_b[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int a_size = sizeof(arr_a) / sizeof(arr_a[0]);
	int b_size = sizeof(arr_b) / sizeof(arr_b[0]);

	bool result = equals(arr_a, a_size, arr_b, b_size);
	printf("Two arrays are ");
	result == 1 ? printf("the same\n") : printf("not the same\n");
	return 0;
}

bool equals(int a[], int a_size, int b[], int b_size)
{
	if (a_size == b_size)
	{
		//proceed;
		for (int i = 0; i < a_size; ++i)
		{
			if (a[i] != b[i])
			{
				return false;
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}
