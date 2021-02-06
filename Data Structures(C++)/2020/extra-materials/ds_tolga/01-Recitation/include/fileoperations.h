#pragma once

#include "phone_record.h"

struct PhonebookFile{
	const char* filename;
	FILE* phonebook;
	void create_file(const char*);
	void close_file();
	void add_to_file(Phone_Record *);
	int search_file(char []);
	void remove_from_file(int );
	void update_file(int , Phone_Record *);
};
