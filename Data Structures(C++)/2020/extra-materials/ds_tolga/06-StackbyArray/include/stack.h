#pragma once
#define STACKSIZE 5
typedef char StackDataType;
struct Stack
{
    StackDataType element[STACKSIZE];
    int top;

    void create();
    void clear();
    bool push(StackDataType);
    StackDataType pop();
    StackDataType peek();
    bool isempty();
    void print_stack();
};
