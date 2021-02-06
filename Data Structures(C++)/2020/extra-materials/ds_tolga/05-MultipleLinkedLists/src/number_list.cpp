#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <iostream>
#include "number_list.h"

using namespace std;

void Number_List::create()
{
    head = NULL;
    tail = NULL;
    nodecount = 0;
}

void Number_List::insert(Number_Record &newrecord)
{
    Number_Node *traverse;
    Number_Node *newnode;

    traverse = head;
    newnode = new Number_Node;
    newnode->build_node(newrecord);
    if (head == NULL)
    {
        head = newnode;
        tail = newnode;
    }
    else{
        tail->next=newnode;
        tail = newnode;
    }
    nodecount++;
}

void Number_List::print_list()
{
    Number_Node *traverse = head;
    for (int i = 1; traverse; i++, traverse = traverse->next)
        cout << traverse->number_record->area_code << "-" << traverse->number_record->num << " ";
    cout << endl;
}

void Number_List::clear()
{
    Number_Node *p;
    while (head)
    {
        p = head;
        head = head->next;
        delete p->number_record;
        delete p;
    }
    nodecount = 0;
}