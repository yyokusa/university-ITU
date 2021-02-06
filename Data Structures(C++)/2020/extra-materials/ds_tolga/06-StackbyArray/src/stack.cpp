#include <iostream>
#include "stack.h"

using namespace std;

void Stack::create()
{
    top = 0;
}

void Stack::clear()
{
    top = 0;
}

void Stack::print_stack(){
    cout<<"[ ";
    for(int i=top;i>0;i--)
        cout<<element[i-1]<<" ";
    cout<<"]"<<endl;
} 

bool Stack::push(StackDataType newelement)
{
    if (top < STACKSIZE)
    {
        element[top++] = newelement;
        return true;
    }
    return false;
}
StackDataType Stack::pop()
{
    return element[--top];
}

StackDataType Stack::peek()
{
    return element[top-1];
}

bool Stack::isempty()
{
    return (top == 0);
}
