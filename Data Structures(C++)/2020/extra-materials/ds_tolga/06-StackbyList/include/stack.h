#pragma once
typedef char StackDataType;
struct Node
{
    StackDataType data;
    Node *next;
};

struct Stack
{
    Node *head;
    
    void create();
    void clear();
    void push(StackDataType);
    StackDataType pop();
    StackDataType peek();
    bool isempty();
    void print_stack();
};
