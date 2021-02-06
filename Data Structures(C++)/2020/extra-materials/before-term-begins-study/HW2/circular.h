#ifndef CIRCULAR_H
#define CIRCULAR_H


#include <iostream> // cin cout
#include <cstdio> // file operations
#include <cstring> // file operations


#include "emails.h" // StudentInfo

struct SurnameNode
{
    char surname[MAX_USER_SURNAME];
    SurnameNode* next;
    Emails* studentsAndEmailsList;
};


// Circular student surnames list
struct SurnameMap {
    SurnameNode* head;
    SurnameNode* tail;
    int size;
    void insertNewRecord(StudentInfo* student); // OK
    void createList(); // OK
	void makeEmpty(); // OK
    void deleteSurnameNode(char* surname); // OK
    void deleteStudent(StudentInfo* student); // OK
    void updateList(StudentInfo* oldStudent, StudentInfo* newStudent); // OK
    
    void insertAll(); // Inserts all records and information from any file to the lists.
    void writeToFile();
    
};

#endif