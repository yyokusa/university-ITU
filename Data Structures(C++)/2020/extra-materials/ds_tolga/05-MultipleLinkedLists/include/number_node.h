#pragma once
#include "number_record.h"

struct Number_Node
{
    Number_Record *number_record;
    Number_Node *next;
    void build_node(Number_Record &);
};