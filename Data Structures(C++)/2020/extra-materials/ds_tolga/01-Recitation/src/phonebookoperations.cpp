#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>

using namespace std;

#include "menu.h"
#include "fileoperations.h"

void add_record(PhonebookFile bookfile)
{
	Phone_Record newrecord;
	cout << "Please enter contact information you want to add" << endl;
	cout << "Name : ";
	cin.ignore(1000, '\n');
	cin.getline(newrecord.name, NAME_LENGTH);
	cout << "Phone number :";
	cin >> setw(PHONENUM_LENGTH) >> newrecord.phonenum; //setw --> iomanip
	bookfile.add_to_file(&newrecord);
	cout << "Record added" << endl;
	getchar(); //getchar --> stdio
}

void search_record(PhonebookFile bookfile)
{
	char name[NAME_LENGTH];
	cout << "Please enter the name of the person you want to search for (press'*'for full list):" << endl;
	cin.ignore(1000, '\n');
	cin.getline(name, NAME_LENGTH);
	if (bookfile.search_file(name) == 0)
	{
		cout << "Could not find a record matching your search criteria" << endl;
	}
	getchar();
}

void update_record(PhonebookFile bookfile)
{
	char name[NAME_LENGTH];
	int choice;
	cout << "Please enter the name of the person whose record you want to update (press'*'for full list):" << endl;
	cin.ignore(1000, '\n');
	cin.getline(name, NAME_LENGTH);
	int personcount = bookfile.search_file(name);
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
		cin.getline(newrecord.name, NAME_LENGTH);
		cout << "Phone number :";
		cin >> setw(PHONENUM_LENGTH) >> newrecord.phonenum;
		bookfile.update_file(choice, &newrecord);
		cout << "Record successfully updated" << endl;
	}
	getchar();
}

void delete_record(PhonebookFile bookfile)
{
	char name[NAME_LENGTH];
	int choice;
	cout << "Please enter the name of the person whose record you want to delete (press'*'for full list):" << endl;
	cin.ignore(1000, '\n');
	cin.getline(name, NAME_LENGTH);
	int personcount = bookfile.search_file(name);
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
