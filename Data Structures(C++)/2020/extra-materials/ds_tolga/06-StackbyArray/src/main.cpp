#include <iostream>
#include <stdlib.h>
#include "stack.h"

using namespace std;

int main()
{
	/*
	int arr_len = 100;
	char array[arr_len];

	for(int i=0;i<arr_len;i++)
		array[i] = 65 +i%26;

	for(int i=0;i<arr_len;i++)
		cout << array[i] <<" ";

	cout << endl << endl << "Select an index to remove ";
	int index;
	cin >> index;
	array[index] = '-';

	for(int i=0;i<arr_len;i++)
		cout << array[i] <<" ";

	cout << endl << endl << "Input a char to insert ";
	char to_add;
	cin >> to_add;
	array[index] = to_add;

	for(int i=0;i<arr_len;i++)
		cout << array[i] <<" ";

	cout << endl;
*/
	Stack s;
	s.create();
	s.push('A');
	s.push('B');
	s.push('C');
	
	if(!s.isempty())
		cout << s.peek() <<endl;

	s.push('X');
	s.print_stack();

	getchar();
	return EXIT_SUCCESS; 
}
