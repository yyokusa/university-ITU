#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <fstream>

using namespace std;

#include "fileoperations.h"
#include "phone_record.h"

void read_fromfile(Phone_Tree& atree, const char *filename)
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
		Phone_Record newrecord;

		phonebook >> temp_name >> temp_phonenum;
		while (!phonebook.eof())
		{
			newrecord.name = new char[temp_name.length() + 1];
			newrecord.phonenum = new char[temp_phonenum.length() + 1];
			strcpy(newrecord.name, temp_name.c_str());
			strcpy(newrecord.phonenum, temp_phonenum.c_str());
			atree.insert(newrecord);
			phonebook >> temp_name >> temp_phonenum;
			delete[] newrecord.name;
			delete[] newrecord.phonenum;
		}
	}
	phonebook.close();
}


void write_preorder(fstream& phonebook, Phone_Node* p){
	if(p){
		phonebook << p->phone_record->name << " " << p->phone_record->phonenum << endl;
		write_preorder(phonebook, p->left);
		write_preorder(phonebook, p->right);
	}

}

void write_tofile(Phone_Tree& atree, const char *filename)
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
	write_preorder(phonebook, atree.root);
	phonebook.close();
}
