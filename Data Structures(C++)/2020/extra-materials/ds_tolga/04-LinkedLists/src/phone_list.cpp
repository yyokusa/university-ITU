#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <iostream>
#include "phone_list.h"

using namespace std;

void Phone_List::create()
{
    head = NULL;
    nodecount = 0;
}

int Phone_List::search(const char *target)
{
    Phone_Node* traverse;
    int counter = 0;
    int found = 0;
    traverse = head;
    bool all = false;
    if (strcmp(target, "*") == 0)
        all = true;
    while (traverse)
    {
        counter++;
        if (all)
        {
            cout << counter << "." << traverse->phone_record->name << " " << traverse->phone_record->phonenum << endl;
            found++;
        }
        else if (strncasecmp(traverse->phone_record->name, target, strlen(target)) == 0)
        {
            found++;
            cout << counter << "." << traverse->phone_record->name << " " << traverse->phone_record->phonenum
                 << endl;
        }
        traverse = traverse->next;
    }
    return found;
}

void Phone_List::remove(int ordernum)
{
    Phone_Node* traverse;
    Phone_Node* predecessor;
    int counter = 1;
    traverse = head;
    if (ordernum <= 0)
    {
        cout << "Invalid record order number.\n";
        return;
    }
    if (ordernum == 1)
    {
        head = head->next;
        delete[] traverse->phone_record->name;
        delete[] traverse->phone_record->phonenum;
        delete traverse->phone_record;
        delete traverse;
        nodecount--;
        return;
    }
    while ((traverse != NULL) && (counter < ordernum))
    {
        predecessor = traverse;
        traverse = traverse->next;
        counter++;
    }
    if (counter < ordernum)
    {
        // given order num too large
        cout << "Could not find record to delete.\n ";
    }
    else
    { // record found
        predecessor->next = traverse->next;
        delete[] traverse->phone_record->name;
        delete[] traverse->phone_record->phonenum;
        delete traverse->phone_record;
        delete traverse;
        nodecount--;
    }
}

void Phone_List::insert(Phone_Record& newrecord)
{
    Phone_Node* traverse;
    Phone_Node* predecessor;
    Phone_Node* newnode;

    traverse = head;
    newnode = new Phone_Node;
    newnode->build_node(newrecord); 
    if (head == NULL)
    {
        //first node being added
        head = newnode;
        nodecount++;
        return;
    }
    if (strcmp(newnode->phone_record->name, head->phone_record->name) < 0)
    {
        //Insert to head of list
        newnode->next = head;
        head = newnode;
        nodecount++;
        return;
    }
    while (traverse &&
           (strcmp(newnode->phone_record->name, traverse->phone_record->name) > 0))
    {
        predecessor = traverse;
        traverse = traverse->next;
    }
    if (traverse)
    { // Insert into a position
        newnode->next = traverse;
        predecessor->next = newnode;
    }
    else // Insert to end
        predecessor->next = newnode;
    nodecount++;
}

void Phone_List::update(int recordnum, Phone_Record& newrecord)
{
    Phone_Node* traverse;

    int counter = 1;
    traverse = head;
    while (traverse && (counter < recordnum))
    {
        counter++;
        traverse = traverse->next;
    }
    if (traverse)
    {
        delete[] traverse->phone_record->name;
        delete[] traverse->phone_record->phonenum;
        traverse->phone_record->name = new char[strlen(newrecord.name) + 1];
        traverse->phone_record->phonenum = new char[strlen(newrecord.phonenum) + 1];
        strcpy(traverse->phone_record->name, newrecord.name);
        strcpy(traverse->phone_record->phonenum, newrecord.phonenum);
    }
    else
        cout << "Invalid number for record to be updated.\n";
}

void Phone_List::clear()
{
    Phone_Node *p;
    while (head)
    {
        p = head;
        head = head->next;
        delete[] p->phone_record->name;
        delete[] p->phone_record->phonenum;
        delete p->phone_record;
        delete p;
    }
    nodecount = 0;
}

void Phone_List::print_list()
{
    Phone_Node *traverse = head;
    cout << endl
         << "CURRENT VERSION OF LINKED LIST" << endl;
    for (int i = 1; traverse; i++, traverse = traverse->next)
        cout << i << ". " << traverse->phone_record->name << " " << traverse->phone_record->phonenum << endl;
    cout << endl;
}