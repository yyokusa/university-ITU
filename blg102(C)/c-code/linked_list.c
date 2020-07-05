#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // true(1) false(0) bool(_Bool)

typedef struct Node
{
    int val;
    struct Node *ptr;
} Node;

Node *createNode(int val);
Node *append(Node *start, Node *newDigptr);
void printList(Node *start);
void freeNode(Node *ptr);

int main()
{
    Node *node1 = createNode(10);
    Node *node2 = createNode(56);
    Node *node3 = createNode(32);
    Node *node4 = createNode(87);
    append(node1, node2);
    append(node1, node3);
    append(node1, node4);
    printList(node1);
    freeNode(node1);
    return 0;
}

Node *createNode(int val)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode)
    {
        newNode->val = val;
        newNode->ptr = NULL;
        return newNode;
    }
    return NULL;
}

Node *append(Node *start, Node *newDigptr)
{
    if (newDigptr)
    {
        Node *temp = start;
        while (temp->ptr)
        {
            temp = temp->ptr;
        }
        temp->ptr = newDigptr;
        printf("value: %d appended to the list with the head Node value %d\n", newDigptr->val, start->val);
        return newDigptr;
    }
    return NULL;
}

void printList(Node *start)
{
    if (start)
    {
        printf("Printing started\n");
        Node *temp = start;
        while (temp)
        {
            printf("value: %d\n", temp->val);
            temp = temp->ptr;
        }
    }
}

void freeNode(Node *start)
{
    Node *ptr = start;
    if (start)
    {
        Node *temp = start;
        while (temp)
        {
            printf("value: %d freed\n", temp->val);
            ptr = temp;
            temp = temp->ptr;
            free(ptr);
        }
    }
}