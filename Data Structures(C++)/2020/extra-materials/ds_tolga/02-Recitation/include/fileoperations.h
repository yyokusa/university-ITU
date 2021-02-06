#pragma once

#include "phone_record.h"

#define ARRAY_SIZE 10000

struct PhonebookFile{
	const char* filename;
	FILE* phonebook;
	void create_file(const char *);
	void close_file();
	void add_to_file(Phone_Record *);
	int search_file(char []);
	void remove_from_file(int );
	void update_file(int , Phone_Record *);

	Phone_Record records[ARRAY_SIZE];
	int records_count = 0;
};
