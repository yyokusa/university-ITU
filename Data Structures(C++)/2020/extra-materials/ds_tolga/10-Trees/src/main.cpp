#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <time.h> /* time */
#include <iomanip>

using namespace std;

#include "menu.h"
#include "phone_tree.h"
#include "fileoperations.h"
#include "phonebooktests.h"

int main()
{

	Phone_Tree phonetree;
	phonetree.create();
	read_fromfile(phonetree, "phonebook.dat");

	bool end = false;
	char choice;

	while (!end)
	{
		print_menu();
		cin >> choice;
		end = perform_operation(choice, phonetree);
	}

	write_tofile(phonetree, "phonebook.dat");
	phonetree.clear();

	//testphonebook();
	return EXIT_SUCCESS; //-->stdlib.h
}
