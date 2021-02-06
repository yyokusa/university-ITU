#pragma once
#include "number_node.h"
#include "number_record.h"

struct Number_List
{
    Number_Node *head;
    Number_Node *tail;
    int nodecount;
    void create();
    void clear();
    void print_list();
    void insert(Number_Record&);
};