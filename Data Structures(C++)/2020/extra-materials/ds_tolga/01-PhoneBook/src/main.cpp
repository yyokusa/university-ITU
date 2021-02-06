#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

#include "menu.h"
#include "fileoperations.h"

int main()
{
	PhonebookFile bookfile;
	bookfile.create();

	bool end = false;
	char choice;

	while (!end)
	{
		print_menu();
		cin >> choice;
		end = perform_operation(choice, bookfile);
	}

	bookfile.close();

	return EXIT_SUCCESS; //-->stdlib.h
}