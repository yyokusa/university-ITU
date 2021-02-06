#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include "number_node.h"

using namespace std;

void Number_Node::build_node(Number_Record &tocopy)
{
    number_record = new Number_Record;
    number_record->area_code = tocopy.area_code;
    number_record->num = tocopy.num;
    next = NULL;
}