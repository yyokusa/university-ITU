#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

using namespace std;

#include "fileoperations.h"

void PhonebookFile::create(){	
	filename="phonebook.dat";
	phonebook = fopen( filename, "r+" );
	if(!phonebook){
		if(!(phonebook=fopen(filename,"w+"))){
		    cerr << "Cannot open file" << endl;
		    exit(1);   //--> stdlib.h 
		}
	}
}

void PhonebookFile::close(){
	fclose(phonebook);
}

void PhonebookFile::add(Phone_Record *nrptr){
	fseek(phonebook, 0, SEEK_END);
	fwrite(nrptr, sizeof(Phone_Record), 1, phonebook);
}

int PhonebookFile::search(char *desired){
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

void PhonebookFile::update(int recordnum,Phone_Record *nrptr){
	if(fseek(phonebook, sizeof(Phone_Record)*(recordnum-1), SEEK_SET) == 0)
		fwrite(nrptr, sizeof(Phone_Record), 1, phonebook);
}

void PhonebookFile::remove(int recordnum){
	Phone_Record emptyrecord={"",""};
	if(fseek(phonebook, sizeof(Phone_Record)*(recordnum-1), SEEK_SET) == 0)
		fwrite(&emptyrecord,sizeof(Phone_Record), 1,phonebook);
}
