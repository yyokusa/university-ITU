// HEADER FILE EXAMPLE
#ifndef FILEOPERATIONS_H
#define FILEOPERATIONS_H
// #include <stdio.h>
// #include "record.h"

#define NAME_LENGTH 30
#define PHONENUM_LENGTH 15

struct Phone_Record{
	char name[NAME_LENGTH];	
	char phonenum[PHONENUM_LENGTH];	
};
#endif
// HEADER FILE EXAMPLE END


// FILE READING
if (argc != 3)
{
    puts("enter 3 command line arguments!");
    return EXIT_FAILURE;
}

FILE *fileptr = NULL;
if ((fileptr = fopen(argv[1], "r")) == NULL)
{
    cout << "Could not open file" << endl;
    return EXIT_FAILURE; // expands to 1
}
else
{
    // DO STUFF WITH fileptr
    fclose(fileptr);
}
// FILE READING END


// C Array initialization
    char sentence[CHARS] = {'\0'};
// C Array initialization END

// C++ Array initialization
    int baz [5] = { }; // This creates an array of five int values, each initialized with a value of zero
    // Finally, the evolution of C++ has led to the adoption of universal initialization also for arrays. 
    // Therefore, there is no longer need for the equal sign between the declaration and the initializer. 
    // Both these statements are equivalent:
    int foo[] = { 10, 20, 30 };
    int foo[] { 10, 20, 30 }; 
// C++ Array initialization END

//  sizeof() func




















//!!!!!!!!!!!!!!!!!! GOOD file search and update code !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!¡!!!


/* #include "fileoperations.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>

void File::add(Phone_Record *nrptr){
	fseek(phonebook, 0, SEEK_END); // sets the file pos to EOF
	fwrite(nrptr, sizeof(Phone_Record), 1, phonebook);
}

void File::create(){	
	filename="phonebook.txt";
	phonebook = fopen( filename, "r+" );
	if(!phonebook){ // if the file does not exist yet
		if(!(phonebook = fopen( filename, "w+" ))){ // create file (using 'w')
			cerr << "Cannot open file" << endl;
			exit(1); // EXIT_FAILURE
		}
	}
}

void File::close(){
	fclose(phonebook);
}

int File::search(char *desired){
	Phone_Record k;
	int index=0;
	bool all=false;
	int found=0;
	if(strcmp(desired,"*")==0)
		all=true;
	fseek(phonebook, 0, SEEK_SET);
	while(!feof(phonebook)){		
		index++;
		fread( &k, sizeof (Phone_Record), 1, phonebook);		
		if(feof(phonebook)) break;
		// The strnicmp() function compares, at most,
		// the first n characters of string1 and string2 without sensitivity to case.
		if(all || strnicmp(k.name, desired, strlen(desired))==0){
			cout << index << "." << k.name << " " << k.phonenum << endl;
			found++;
		}
	}	
	return found;
}

void File::update(int recordnum, Phone_Record *nrptr){
	if(fseek(phonebook, sizeof(Phone_Record)*(recordnum-1), SEEK_SET)==0)
		fwrite(nrptr, sizeof(Phone_Record), 1, phonebook);
}

void File::remove(int recordnum){
	Phone_Record emptyrecord={"",""};	
	if(fseek(phonebook, sizeof(Phone_Record)*(recordnum-1), SEEK_SET)==0)
		fwrite(&emptyrecord, sizeof(Phone_Record), 1, phonebook);
}
 */