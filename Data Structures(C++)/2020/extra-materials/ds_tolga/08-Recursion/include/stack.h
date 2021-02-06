#pragma once

template <typename TN>
struct Node
{
    TN data;
    Node<TN> *next;
};

template <typename TS>
struct Stack
{
    Node<TS> *head;

    void create();
    void close();
    void push(TS);
    TS pop();
    TS peek();
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
    Node<TS> *p;
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
    Node<TS> *newnode = new Node<TS>;
    newnode->data = newdata;
    newnode->next = head;
    head = newnode;
}

template <typename TS>
TS Stack<TS>::pop()
{
    Node<TS> *topnode;
    TS temp;
    topnode = head;
    head = head->next;
    temp = topnode->data;
    delete topnode;
    return temp;
}

template <typename TS>
TS Stack<TS>::peek()
{
    return head->data;
}

template <typename TS>
bool Stack<TS>::isempty()
{
    return head == NULL;
}
