#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#define NUM_OF_DISKS 3
using namespace std;

void hanoi_iterative(int, Stack<int>[3]);

int main()
{
	
	Stack<int> s[3]; // array of 3 elements of stack<int>

	for (int i = 0; i < 3; i++)
		s[i].create();

	for (int i = 0; i < 5; i++)
		s[0].push(NUM_OF_DISKS - i);

	hanoi_iterative(NUM_OF_DISKS, s);

	for (int i = 0; i < 3; i++)
		s[i].close();

	getchar();
	return EXIT_SUCCESS; 
}

void hanoi_iterative(int n, Stack<int> s[3])
{
	Stack<MoveType> m; // moves stack of move types
	m.create();
	MoveType move = {n, 0, 2}; // move type structure  {n, source, destination}
	m.push(move);
	while (!m.isempty())
	{
		move = m.pop();
	
		if(move.n==1)
			cout << "From: "<< move.source << " To: " << move.destination << endl ;
	
		if (move.n == 1) s[move.destination].push(s[move.source].pop());
		else
		{
			int temp = 0 + 1 + 2 - move.destination - move.source; 

			m.push({move.n - 1, temp, move.destination});

			m.push({1, move.source, move.destination});

			m.push({move.n - 1, move.source, temp});
		}
	}
	m.close();
}
