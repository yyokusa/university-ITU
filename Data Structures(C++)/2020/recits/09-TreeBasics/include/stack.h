#pragma once

template <typename TN>
struct StackNode
{
    TN data;
    StackNode<TN> *next;
};

template <typename TS>
struct Stack
{
    StackNode<TS> *head;

    void create();
    void close();
    void push(TS);
    TS pop();
    bool isempty();
};

template <typename TS>
void Stack<TS>::create()
{
    head = NULL;
}

template <typename TS>
void Stack<TS>::close()
{
    StackNode<TS> *p;
    while (head)
    {
        p = head;
        head = head->next;
        delete p;
    }
}

template <typename TS>
void Stack<TS>::push(TS newdata)
{
    StackNode<TS> *newnode = new StackNode<TS>;
    newnode->data = newdata;
    newnode->next = head;
    head = newnode;
}

template <typename TS>
TS Stack<TS>::pop()
{
    StackNode<TS> *topnode;
    TS temp;
    topnode = head;
    head = head->next;
    temp = topnode->data;
    delete topnode;
    return temp;
}

template <typename TS>
bool Stack<TS>::isempty()
{
    return head == NULL;
}
