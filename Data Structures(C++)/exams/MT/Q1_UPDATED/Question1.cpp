/* @Author
Student Name:YASIN ABDULKADIR YOKUS
Student ID :150190739
Date:09/12/2020
*/

/*Question#1-The following function do not produce expected results since it is storing only the final entry to the array.
Please provide a solution using dynamic memory allocation techniques.
You are not allowed to use c++ strings in your answer.
Use either character arrays or pointers. You are not allowed to use any outside functions (such as STL methods)
*/
#ifndef HEADERFILE_H
#define HEADERFILE_H
	#include <iostream>
	#include <string>
#endif

using namespace std;
//15 pts
void question1(){
	char* names[5]; // 2D array
	for (int i = 0; i < 5; i++){
		cout << "Please enter " << i+1 << ". student name: ";
		char* new_name = new char[15];
		cin >> new_name;
		names[i] = new_name;
	}
	cout << "Printing the array members:" << endl;
	for (int i = 0; i < 5; i++){
		cout << names[i]<< endl;
		delete [] names[i];
	}
}