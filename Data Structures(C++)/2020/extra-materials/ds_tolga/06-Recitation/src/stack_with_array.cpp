#include <iostream>
#include "stack_with_array.h"

using namespace std;

void StackA::initiate(){
	array =new char[MAX_SIZE];
	node_count=0;
}

void StackA::push(char input){
	if(node_count<MAX_SIZE)
		array[node_count++]=input;
}

char StackA::pop(){
	if(node_count>0)
		return array[--node_count];	
	else
		return ' ';	
}

char StackA::peek()
{
	return array[node_count-1];
}

bool StackA::isEmpty(){
	return node_count==0?true:false;
}

void StackA::close(){
	delete [] array;
}

void StackA::printStack()
{
	cout<<endl<<"CURRENT VERSION OF STACK"<<endl;
	for (int i=node_count;i>0;i--)
		cout<<" "<<array[i];
	cout<<endl;
}

