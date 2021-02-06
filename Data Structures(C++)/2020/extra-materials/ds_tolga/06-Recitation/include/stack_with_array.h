#ifndef STACKA_H
#define STACKA_H

#define MAX_SIZE 30 

class StackA{
public:
    int node_count;
    char * array;
	void initiate();
	void push(char);
	char pop();
	bool isEmpty();
	void close();
	void printStack();
	char peek();
};
#endif