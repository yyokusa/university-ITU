#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <fstream>

using namespace std;

#include "fileoperations.h"
#include "phone_record.h"

void read_fromfile(Phone_List& alist, const char *filename)
{
	fstream phonebook;
	phonebook.open(filename, fstream::in | fstream::binary);
	if (!phonebook.is_open())
	{
		phonebook.open(filename, fstream::out | fstream::binary);
		if (!phonebook.is_open())
		{
			cerr << "Cannot open file";
			exit(1);
		}
	}
	else{
		string temp_name;
		string temp_phonenum;

		phonebook >> temp_name >> temp_phonenum;
		while (!phonebook.eof())
		{
			Phone_Record newrecord;
			newrecord.name = new char[temp_name.length() + 1];
			newrecord.phonenum = new char[temp_phonenum.length() + 1];
			strcpy(newrecord.name, temp_name.c_str());
			strcpy(newrecord.phonenum, temp_phonenum.c_str());
			alist.insert(newrecord);
			phonebook >> temp_name >> temp_phonenum;
			delete[] newrecord.name;
			delete[] newrecord.phonenum;
		}
	}
	phonebook.close();
}

void write_tofile(Phone_List& alist, const char *filename)
{
	fstream phonebook;

	Phone_Record record;
	Phone_Node *p;
	phonebook.open(filename, fstream::out | fstream::binary);
	if (!phonebook.is_open())
	{
		cerr << "File could not be opened" << endl;
		exit(1);
	}
	p = alist.head;
	while (p)
	{
		phonebook << p->phone_record->name << " " << p->phone_record->phonenum << endl;
		p = p->next;
	}
	phonebook.close();
}