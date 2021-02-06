#include <iostream>
#include <stdlib.h>
#include "stack.h"

using namespace std;

int main()
{
	Stack s;

	s.create();

	s.push('5');
	s.push('3');
	s.push('7');
	s.push('1');
	s.print_stack();

	s.pop();
	s.pop();
	s.print_stack();

	char a;
	cin>>a;
	s.clear();
	return EXIT_SUCCESS; 
}
