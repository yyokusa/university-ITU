// 2D array average example 
/*
for (int i = 0; i < 10; i++)
    cout << i + 1 << ". student's average=" << new_average(&grades2[0][0], i, 3, 10) << endl;
cout << "Class Average=" << (sum/3) << endl; 

float new_average(int *aPtr, int start, int size, int offset)
{
	int sum = 0;
	for (int i = 0; i < size; i++)
	{
		sum += *(aPtr + start + i * offset);
	}
	return (float)sum / (float)size;
}





SIMILAR

f(&grades[0][0], 0, 10, 3); // return student avg. grades  and whole avg. grade for students
cout << "\n\n\n" << endl;
f(&grades[0][0], 0, 3, 10); // return exam avg. grades  and whole avg. grade for students



void f(int* arr, int start, int size, int offset) {
	for (int j = 0; j < size; j++)
	{
		cout << *(arr + start + j*offset) << " ";
		// sum += **(arr + j + i*dim1);
	}
}
*/



































/* 


#include <cstring> // (string.h) --> strcat, strcmp, strlen
#include <cctype>  // <cctype> --> isalnum, isalpha, isdigit, tolower, toupper

#include <stdio.h>      // printf, scanf, puts, NULL
#include <stdlib.h>     // srand, rand 
#include <time.h>       // time 

#include <iomanip>  // cin.ignore(), setw

#include <strings.h> // strncasecmp -->  compare two strings ignoring case, NOT STANDARD , similar function strnicmp() also not standard







// DONT FORGET TO CLOSE THE FILE POINTER
    fclose(file_ptr);

// dynamic 2D array allocation!!!!!!!
    char** array = new char*[2];
    for (int i = 0; i < 2; i++)
    {
        array[i] = new char[3];
    }
    // deallocation
    for(int i = 0; i < sizeY; ++i) {
        delete [] ary[i];
    }
    delete [] ary;
    // more lightweight
    int *ary = new int[sizeX*sizeY];
    ary[i*sizeY+j] // ary[i][j] is then rewritten as



// also
char* array = new char[10];
strcpy(array, "helloworld");

// case insensitive switch case
switch (choice) { 
		case 'A' : case 'a' :
			search_book_by_author();
			break;
		default :
			break;
}


// take input using cin getline
cout<< "Name: ";
cin.ignore(1000,'\n');
cin.getline(var.authorName,NAME_LENGTH);

    
// it is not suggested to use feof but keep in mind
while(!(feof(ptr))){
    fwrite(&temp,sizeof(book_record),1,file.book);
    fread(&temp,sizeof(book_record),1,ptr);
} */

// using cin.getline to get input
/* If you're using getline() after cin >> something, you need to flush the newline character out of the buffer in between.
You can do it by using cin.ignore().
    string messageVar;
    cout << "Type your message: ";
    cin.ignore(); 
    getline(cin, messageVar);
This happens because the >> operator leaves a newline  character in the input buffer. 
This may become a problem when you do unformatted input, like getline(), which reads input until a newline character is found. 
This happening, it will stop reading immediately, because of that  that was left hanging there in your previous operation. */




