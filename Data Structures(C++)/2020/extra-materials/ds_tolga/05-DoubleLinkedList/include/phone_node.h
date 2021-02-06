#pragma once
#include "phone_record.h"

struct Phone_Node
{
    Phone_Record* phone_record;
    Phone_Node *next;
    Phone_Node *prev;
    void build_node(Phone_Record&);
};