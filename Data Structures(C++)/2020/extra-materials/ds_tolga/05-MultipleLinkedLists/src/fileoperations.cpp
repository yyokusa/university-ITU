#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <fstream>
#include <ctype.h>

using namespace std;

#include "fileoperations.h"
#include "phone_record.h"
#include "number_list.h"
#include "number_record.h"
#include "number_node.h"

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
		string temp;
		Phone_Record newphonerecord;
		Number_Record newnumberrecord;

		phonebook >> temp;
		while (!phonebook.eof())
		{
			int dashind;
			string area,number;
			newphonerecord.name = new char[strlen(temp.c_str()) + 1];
			strcpy(newphonerecord.name, temp.c_str());
			newphonerecord.numbers = new Number_List;
			newphonerecord.numbers->create();

			while (!phonebook.eof())
			{
				phonebook >> temp;
				dashind = temp.find("-");
				if (!(isdigit(temp.c_str()[0]) && dashind > 0))
					break;
				area = temp.substr(0, dashind);
				number = temp.substr(dashind + 1, strlen(temp.c_str()));
				newnumberrecord.area_code = atoi(area.c_str());
				newnumberrecord.num = atoi(number.c_str());
				newphonerecord.numbers->insert(newnumberrecord);
			}
			alist.insert(newphonerecord);
			delete[] newphonerecord.name;
		}
	}
	phonebook.close();
}

void write_tofile(Phone_List& alist, const char *filename)
{
	fstream phonebook;

	Phone_Record record;
	Phone_Node *p;
	Number_Node *n;
	phonebook.open(filename, fstream::out | fstream::binary);
	if (!phonebook.is_open())
	{
		cerr << "File could not be opened" << endl;
		exit(1);
	}
	p = alist.head;
	while (p)
	{
		phonebook << p->phone_record->name << " ";
		if (p->phone_record->numbers && p->phone_record->numbers->nodecount > 0)
		{
			n = p->phone_record->numbers->head;
			while(n){
				phonebook << n->number_record->area_code << "-" << n->number_record->num;
				if(n->next)
					phonebook << " ";
				n = n->next;
			}
		}
		if(p->next)
			phonebook << endl;
		p = p->next;
	}
	phonebook.close();
}