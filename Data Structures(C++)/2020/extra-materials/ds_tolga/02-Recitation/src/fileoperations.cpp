#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

using namespace std;

#include "fileoperations.h"

void PhonebookFile::create_file(const char *fname)
{
	filename=fname;
	phonebook = fopen( filename, "r+" );
	if(!phonebook){
		if(!(phonebook=fopen(filename,"w+"))){
		    cerr << "Cannot open file" << endl;
		    exit(1);   //--> stdlib.h 
		}
	}
	else // we are adding this part to make it using array
	{
		Phone_Record k;
		int counter = 0;

		fseek(phonebook, 0, SEEK_SET);
		while (!feof(phonebook))
		{
			fread(&k, sizeof(Phone_Record), 1, phonebook);
			if (feof(phonebook))
				break;
			if (strcpy(records[counter].name, k.name) && strcpy(records[counter].phonenum, k.phonenum))
				counter++;
		}
		records_count = counter;
	}
	fclose(phonebook);
}

void PhonebookFile::close_file(){
	if (!(phonebook = fopen(filename, "w")))
	{
		cerr << "Cannot open file" << endl;
		exit(1);
	}
	for (int i = 0; i < records_count; i++)
		fwrite(&records[i], sizeof(Phone_Record), 1, phonebook);

	fclose(phonebook);
}

void PhonebookFile::add_to_file(Phone_Record *nrptr){
	strcpy(records[records_count].name, nrptr->name);
	strcpy(records[records_count].phonenum, nrptr->phonenum);
	records_count++;
}

int PhonebookFile::search_file(char *desired){
	int index=0;
	bool all=false;
	int found=0;
	if(strcmp(desired,"*")==0)  //strcmp --> string.h
		all=true;

	for (int i = 0; i < records_count; i++)
	{
		if (all || strncasecmp(records[i].name, desired, strlen(desired)) == 0){
			cout << i << "." << records[i].name << " " << records[i].phonenum << endl;
			found++;
		}
	}

	return found;
}

void PhonebookFile::update_file(int recordnum,Phone_Record *nrptr){
	strcpy(records[recordnum].name, nrptr->name);
	strcpy(records[recordnum].phonenum, nrptr->phonenum);
}

void PhonebookFile::remove_from_file(int recordnum){
	for (; recordnum < records_count; recordnum++)
	{
		if (recordnum + 1 < ARRAY_SIZE)
			records[recordnum] = records[recordnum + 1];
	}
	records_count--;
}
