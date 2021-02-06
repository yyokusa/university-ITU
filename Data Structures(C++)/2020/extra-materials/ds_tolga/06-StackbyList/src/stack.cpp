#include <iostream>
#include "stack.h"

using namespace std;

void Stack::create()
{
    head = NULL;
}

void Stack::clear()
{
    Node *p;
    while (head)
    {
        p = head;
        head = head->next;
        delete p;
    }

}

void Stack::print_stack(){
    Node* traverse=head;

    cout << "[ ";
    while(traverse){
        cout << traverse->data << " ";
        traverse = traverse->next;
    }
    cout<<"]"<<endl;
}

void Stack::push(StackDataType newdata)
{
    Node *newnode = new Node;
    newnode->data = newdata;
    newnode->next = head;
    head = newnode;
}

StackDataType Stack::pop()
{
    Node *topnode;
    StackDataType temp;
    topnode = head;
    head = head->next;
    temp = topnode->data;
    delete topnode;
    return temp;
}

StackDataType Stack::peek()
{
    return head->data;
}

bool Stack::isempty()
{
    return head == NULL;
}
