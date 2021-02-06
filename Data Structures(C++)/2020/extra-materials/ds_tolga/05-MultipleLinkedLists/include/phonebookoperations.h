#pragma once
#include "phone_list.h"
#include "number_list.h"


using namespace std;

void add_record(Phone_List&);
void search_record(Phone_List&);
void update_record(Phone_List&);
void delete_record(Phone_List&);
void clear_records(Phone_List&);
void add_numbers(string, Number_List *);