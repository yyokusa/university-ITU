#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include "phone_node.h"

using namespace std;

void Phone_Node::build_node(Phone_Record& tocopy){
    phone_record = new Phone_Record;
    phone_record->name = new char[strlen(tocopy.name)+1];
    strcpy(phone_record->name, tocopy.name);
    phone_record->numbers = tocopy.numbers;
    next = NULL;
}