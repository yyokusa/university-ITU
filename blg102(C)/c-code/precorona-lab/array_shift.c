#include <stdio.h>

#define SIZE 10
void shift_array(int*);

int main() {
	
	int arr[SIZE] = {};
	int flag = 1;
	// for(int i = 0; i < SIZE; ++i) {
		// scanf("%d", &arr[i]);
	// }
	
	// for(int i = 0; i < SIZE; ++i) {
		// printf("%d\n", arr[i]);
	// }
	
	while(1) 
	{
		if(flag == 1) 
		{
			for(int i = size - 1; i > 0; --i) {
				if(arr[i] == arr[i-1]) {
					arr[i] *= 2;
					arr[i - 1] = 0;
					flag = 0;
				}
			}
		} 
		else 
		{
			;
		}
		
		shift_array(arr);
		
		if(flag == 0) 
		{
			for(int i = size - 1; i > 0; --i) {
				if(arr[i] == arr[i-1]) {
					arr[i - 1] *= 2;
					arr[i] = 0;
					flag = 1;
				}
			}
		} 
		else 
		{
			;
		}
		
		
	}
	
	
	return 0;	
}


void shift_array(int* arr[])
{

}

void swap(int* a, int* b) {
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
	return;
}