#pragma once
#include "phone_node.h"
#include "phone_record.h"

#define INDEX_SIZE 26

struct Phone_List
{
    Phone_Node* head;
    Phone_Node *index[INDEX_SIZE];
    int nodecount;
    void create();
    void clear();
    void print_list();
    void insert(Phone_Record &);
    void remove(int ordernum);
    int search(const char *);
    void update(int recordnum, Phone_Record&);
};