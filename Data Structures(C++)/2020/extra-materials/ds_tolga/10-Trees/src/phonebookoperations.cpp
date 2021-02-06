#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <iomanip>

using namespace std;

#include "menu.h"
#include "phone_record.h"
#include "phone_tree.h"
#include "phonebookoperations.h"

void add_record(Phone_Tree &phonetree)
{
	Phone_Record newrecord;
	string name, number;
	cout << "Please enter contact information you want to add" << endl;
	cout << "Name : ";
	cin.ignore(1000, '\n');
	cin >> name;
	newrecord.name = new char[name.length() + 1];
	strcpy(newrecord.name, name.c_str());
	cout << "Phone number :";
	cin >> number;
	newrecord.phonenum = new char[number.length() + 1];
	strcpy(newrecord.phonenum, number.c_str());
	if(phonetree.insert(newrecord))
		cout << "Record added" << endl;
	delete[] newrecord.name;
	delete[] newrecord.phonenum;
	getchar(); //getchar --> stdio
}

void search_record(Phone_Tree &phonetree)
{
	string name;
	cout << "Please enter the name of the person you want to search for (press'*'for full list):" << endl;
	cin.ignore(1000, '\n');
	cin >> name;
	if (!phonetree.search(name.c_str()))
	{
		cout << "Could not find a record matching your search criteria" << endl;
	}
	getchar();
}

void update_record(Phone_Tree &phonetree)
{
	string name, newname, number;
	int personcount=2;
	name="*";
	while(name.compare("*")==0){
		cout << "Please enter the name of the person whose record you want to update (press'*'for full list):" << endl;
		cin.ignore(1000, '\n');
		cin >> name;
		if (!phonetree.search(name.c_str())){
			cout << "Could not find a record matching your search criteria" << endl;
			break;
		}
		else if(name.compare("*")!=0)
		{
			cout << "Record found." << endl;
			Phone_Record newrecord;
			cout << "Please enter current contact information" << endl;
			cout << "Name : ";
			cin.ignore(1000, '\n');
			cin >> newname;
			newrecord.name = new char[newname.length()+1];
			strcpy(newrecord.name, newname.c_str());
			cout << "Phone number :";
			cin >> number;
			newrecord.phonenum = new char[number.length()+1];
			strcpy(newrecord.phonenum, number.c_str());
			phonetree.update(name.c_str(), newrecord);
			cout << "Record successfully updated" << endl;
			delete newrecord.name;
			delete newrecord.phonenum;
		}
	}
	getchar();
}

void delete_record(Phone_Tree &phonetree)
{
	string name;
	int personcount = 2;
	name="*";
	while(personcount>1 || name.compare("*")==0){
		cout << "Please enter the name of the person whose record you want to delete (press'*'for full list):" << endl;
		cin.ignore(1000, '\n');
		cin >> name;
		if (!phonetree.search(name.c_str()))
			cout << " Could not find a record matching your search criteria " << endl;
		else{
			cout << "Record found." << endl;
			phonetree.remove(name.c_str());
			cout << "Record deleted" << endl;
		}
	}
	getchar();
}

void clear_records(Phone_Tree &phonetree)
{
	char choice;
	cout << "Are you sure you want to clear all the records? (Y/N):" << endl;
	cin >> choice;
	if (choice == 'Y' || choice == 'y'){
		phonetree.clear();
		cout << "All records cleared!!!";
	}
	else
	{
		cout << "Records kept. Returning back to menu.";
	}
	
	getchar();
}
