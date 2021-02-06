#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

#include "menu.h"
#include "phone_record.h"
#include "phone_list.h"
#include "number_record.h"
#include "number_list.h"
#include "phonebookoperations.h"


void add_record(Phone_List &phonelist)
{
	Phone_Record newrecord;
	string name,entry;
	cout << "Please enter contact information you want to add" << endl;
	cout << "Name : ";
	cin.ignore(1000, '\n');
	cin >> name;
	newrecord.name = new char[strlen(name.c_str()) + 1];
	strcpy(newrecord.name, name.c_str());
	cout<< "Phone numbers, seperated with spaces : ";
	cin.ignore(1000, '\n');
	getline(cin, entry);
	newrecord.numbers = new Number_List;
	newrecord.numbers->create();
	add_numbers(entry, newrecord.numbers);
	phonelist.insert(newrecord);
	cout << "Record added" << endl;
	delete[] newrecord.name;
	getchar(); //getchar --> stdio
}

void search_record(Phone_List &phonelist)
{
	string name;
	cout << "Please enter the name of the person you want to search for (press'*'for full list):" << endl;
	cin.ignore(1000, '\n');
	cin >> name;
	if (phonelist.search(name.c_str()) == 0)
	{
		cout << "Could not find a record matching your search criteria" << endl;
	}
	getchar();
}

void update_record(Phone_List &phonelist)
{
	string name,entry;
	int choice;
	cout << "Please enter the name of the person whose record you want to update (press'*'for full list):" << endl;
	cin.ignore(1000, '\n');
	cin >> name;
	int personcount = phonelist.search(name.c_str());
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
		newrecord.name = new char[strlen(name.c_str())+1];
		strcpy(newrecord.name, name.c_str());
		cout << "Phone numbers, seperated with spaces : ";
		cin.ignore(1000, '\n');
		getline(cin, entry);
		newrecord.numbers = new Number_List;
		newrecord.numbers->create();
		add_numbers(entry, newrecord.numbers);
		phonelist.update(choice, newrecord);
		delete[] newrecord.name;
		cout << "Record successfully updated" << endl;
	}
	getchar();
}

void delete_record(Phone_List &phonelist)
{
	string name;
	int choice;
	cout << "Please enter the name of the person whose record you want to delete (press'*'for full list):" << endl;
	cin.ignore(1000, '\n');
	cin >> name;
	int personcount = phonelist.search(name.c_str());
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
		phonelist.remove(choice);
		cout << "Record deleted" << endl;
	}
	getchar();
}

void clear_records(Phone_List &phonelist)
{
	char choice;
	cout << "Are you sure you want to clear all the records? (Y/N):" << endl;
	cin >> choice;
	if (choice == 'Y' || choice == 'y'){
		phonelist.clear();
		cout << "All records cleared!!!";
	}
	else
	{
		cout << "Records kept. Returning back to menu.";
	}
	
	getchar();
}

void add_numbers(string entry, Number_List *number_list)
{
	string area, number;
	int dashind=0, spaceind=0;
	Number_Record newrecord;
	while (true)
	{
		dashind = entry.find("-");
		spaceind = entry.find(" ");
		if(dashind<0)
			break;
		area = entry.substr(0, dashind);

		if(spaceind > 0)
			number = entry.substr(dashind+1,(spaceind-dashind));
		else
			number = entry.substr(dashind+1, entry.length());
		
		newrecord.area_code = atoi(area.c_str());
		newrecord.num = atoi(number.c_str());
		number_list->insert(newrecord);

		if (spaceind > 0)
			entry = entry.substr(spaceind+1, entry.length() - spaceind);
		else
			return;
	}
}