#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <time.h> /* time */
#include <iomanip>

using namespace std;

#include "menu.h"
#include "fileoperations.h"
#include "phonebooktests.h"

int main()
{

	PhonebookFile bookfile;
	bookfile.create_file("phonebook.dat");

	bool end = false;
	char choice;

	while (!end)
	{
		print_menu();
		cin >> choice;
		end = perform_operation(choice, bookfile);
	}

	bookfile.close_file();

	//testphonebook();
	return EXIT_SUCCESS; //-->stdlib.h
}
