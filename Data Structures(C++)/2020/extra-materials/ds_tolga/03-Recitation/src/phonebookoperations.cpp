#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <iomanip>

using namespace std;

#include "menu.h"
#include "fileoperations.h"

void add_record(PhonebookFile& bookfile)
{
	Phone_Record newrecord;
	string name, number;
	cout << "Please enter contact information you want to add" << endl;
	cout << "Name : ";
	cin.ignore(1000, '\n');
	cin >> name;
	newrecord.name = new char[name.length()+1];
	strcpy(newrecord.name,name.c_str());
	cout << "Phone number :";
	cin >> number;
	newrecord.phonenum = new char[number.length()+1];
	strcpy(newrecord.phonenum, number.c_str());
	bookfile.add_to_file(&newrecord);
	cout << "Record added" << endl;
	delete[] newrecord.name;
	delete[] newrecord.phonenum;
	getchar(); //getchar --> stdio
}

void search_record(PhonebookFile& bookfile)
{
	string name;
	cout << "Please enter the name of the person you want to search for (press'*'for full list):" << endl;
	cin.ignore(1000, '\n');
	cin >> name;
	if (bookfile.search_file(name.c_str()) == 0)
	{
		cout << "Could not find a record matching your search criteria" << endl;
	}
	getchar();
}

void update_record(PhonebookFile& bookfile)
{
	string name, number;
	int choice;
	cout << "Please enter the name of the person whose record you want to update (press'*'for full list):" << endl;
	cin.ignore(1000, '\n');
	cin >> name;
	int personcount = bookfile.search_file(name.c_str());
	if (personcount == 0)
	{
		cout << "Could not find a record matching your search criteria" << endl;
	}
	else
	{
		if (personcount == 1)
		{
			cout << "Record found." << endl;
			cout << " If you want to update this record please enter its number (Enter -1 to exit without 				   performing any operations): ";
		}
		else
			cout << "Enter the number of the record you want to update (Enter -1 to exit without performing any operations): ";
		cin >> choice;
		if (choice == -1)
			return;
		Phone_Record newrecord;
		cout << "Please enter current contact information" << endl;
		cout << "Name : ";
		cin.ignore(1000, '\n');
		cin >> name;
		newrecord.name = new char[name.length()+1];
		strcpy(newrecord.name, name.c_str());
		cout << "Phone number :";
		cin >> number;
		newrecord.phonenum = new char[number.length()+1];
		strcpy(newrecord.phonenum, number.c_str());
		bookfile.update_file(choice, &newrecord);
		cout << "Record successfully updated" << endl;
		delete[] newrecord.name;
		delete[] newrecord.phonenum;
	}
	getchar();
}

void delete_record(PhonebookFile& bookfile)
{
	string name;
	int choice;
	cout << "Please enter the name of the person whose record you want to delete (press'*'for full list):" << endl;
	cin.ignore(1000, '\n');
	cin >> name;
	int personcount = bookfile.search_file(name.c_str());
	if (personcount == 0)
	{
		cout << " Could not find a record matching your search criteria " << endl;
	}
	else
	{
		if (personcount == 1)
		{
			cout << "Record found." << endl;
			cout << "If you want to delete this record please enter its number (Enter -1 to exit without performing any operations): ";
		}
		else
			cout << "Enter the number of the record you want to delete (Enter -1 to exit without performing any operations): ";
		cin >> choice;
		if (choice == -1)
			return;
		bookfile.remove_from_file(choice);
		cout << "Record deleted" << endl;
	}
	getchar();
}
