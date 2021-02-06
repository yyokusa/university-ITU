#pragma once
#include "phone_node.h"
#include "phone_record.h"

struct Phone_Tree
{
    Phone_Node* root;
    void create();
    void clear();
    void print_tree();
    bool insert(Phone_Record &);
    void remove(const char*);
    void update(const char*, Phone_Record &);
    bool search(const char *);
};