#pragma once

#include <fstream>
#include "phone_record.h"

#define INIT_SIZE 1000

struct PhonebookFile{
	const char* filename;
	std::fstream phonebook;

	void increaseSize();
	void create_file(const char *);
	void close_file();
	void add_to_file(Phone_Record *);
	int search_file(const char*);
	void remove_from_file(int );
	void update_file(int , Phone_Record *);

	Phone_Record **records;
	int records_count = 0;
	int size = 0;
};
