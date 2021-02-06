#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <time.h> /* time */
#include <iomanip>

using namespace std;

#include "menu.h"
#include "phone_list.h"
#include "fileoperations.h"
#include "phonebooktests.h"

int main()
{
	
	Phone_List phonelist;
	phonelist.create();
	read_fromfile(phonelist, "multilist_phonebook.dat");

	bool end = false;
	char choice;

	while (!end)
	{
		print_menu();
		cin >> choice;
		end = perform_operation(choice, phonelist);
	}

	write_tofile(phonelist, "multilist_phonebook.dat");
	phonelist.clear();

	//testphonebook();
	return EXIT_SUCCESS; //-->stdlib.h
}
