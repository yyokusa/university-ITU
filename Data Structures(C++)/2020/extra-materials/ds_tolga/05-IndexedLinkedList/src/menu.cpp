#include <iostream>

using namespace std;

#include "menu.h" 
#include "phone_list.h"
#include "phonebookoperations.h"

void print_menu()
{
	cout << endl << endl;
	cout << "Phone Book Application" << endl;
	cout << "Choose an operation" << endl;
	cout << "S: Record Search" << endl;
	cout << "A: Record Add" << endl;
	cout << "U: Record Update" << endl;
	cout << "D: Record Delete" << endl;
	cout << "C: Delete All" << endl;
	cout << "E: Exit" << endl;
	cout << endl;
	cout << "Enter a choice {S,A,U,D,C,E}: ";
}

bool perform_operation(char choice, Phone_List& phonelist)
{
	bool terminate = false;
	switch (choice)
	{
	case 'S':
	case 's':
		search_record(phonelist);
		break;
	case 'A':
	case 'a':
		add_record(phonelist);
		break;
	case 'U':
	case 'u':
		update_record(phonelist);
		break;
	case 'D':
	case 'd':
		delete_record(phonelist);
		break;
	case 'C':
	case 'c':
		clear_records(phonelist);
		break;
	case 'E':
	case 'e':
		cout << "Are you sure you want to exit the program? (Y/N):";
		cin >> choice;
		if (choice == 'Y' || choice == 'y')
			terminate = true;
		break;
	default:
		cout << "Error: You have entered an invalid choice" << endl;
		cout << "Please try again {S, A, U, D, E} :";
		cin >> choice;
		terminate = perform_operation(choice, phonelist);
		break;
	}
	return terminate;
}