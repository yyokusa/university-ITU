#ifndef STACK_H
#define STACK_H
#include <stdio.h>
#include "node.h"

struct Stack{	
	int node_count;
	Node * top;
	void initiate();
	void push(char);
	char pop();
	char peek();
	bool isEmpty();
	void close();
	void printStack();
};
#endif
