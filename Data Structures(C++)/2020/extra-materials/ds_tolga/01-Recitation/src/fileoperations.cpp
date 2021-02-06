#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

using namespace std;

#include "fileoperations.h"

void PhonebookFile::create_file(const char* fname)
{
	filename=fname;
	phonebook = fopen( filename, "r+" );
	if(!phonebook){
		if(!(phonebook=fopen(filename,"w+"))){
		    cerr << "Cannot open file" << endl;
		    exit(1);   //--> stdlib.h 
		}
	}
}

void PhonebookFile::close_file(){
	fclose(phonebook);
}

void PhonebookFile::add_to_file(Phone_Record *nrptr){
	fseek(phonebook, 0, SEEK_END);
	fwrite(nrptr, sizeof(Phone_Record), 1, phonebook);
}

int PhonebookFile::search_file(char *desired){
	Phone_Record k;
	int index=0;
	bool all=false;
	int found=0;
	if(strcmp(desired,"*")==0)  //strcmp --> string.h
		all=true;
	fseek(phonebook, 0, SEEK_SET);
	while(!feof(phonebook)){		
		index++;
		fread( &k, sizeof (Phone_Record), 1, phonebook);		
		if(feof(phonebook)) break;
		if(all || strncasecmp(k.name, desired, strlen(desired)) == 0){  //strnicmp is not ANSI, --> strings.h
			cout << index <<"."<< k.name << " "<< k.phonenum << endl;
 			found++;
		}
	}	
	return found;
}

void PhonebookFile::update_file(int recordnum,Phone_Record *nrptr){
	if(fseek(phonebook, sizeof(Phone_Record)*(recordnum-1), SEEK_SET) == 0)
		fwrite(nrptr, sizeof(Phone_Record), 1, phonebook);
}

void PhonebookFile::remove_from_file(int recordnum){
	Phone_Record k;

	fseek(phonebook, 0, SEEK_SET);
	FILE *new_phonebook;
	new_phonebook = fopen("tmp.dat", "w+");
	int i = 1;
	while (!feof(phonebook))
	{
		fread(&k, sizeof(Phone_Record), 1, phonebook);
		if (!feof(phonebook) && i != recordnum)
			fwrite(&k, sizeof(Phone_Record), 1, new_phonebook);
		i++;
	}
	fclose(phonebook);
	fclose(new_phonebook);
	remove(filename);
	rename("tmp.dat", filename);
	create_file(filename);
}
