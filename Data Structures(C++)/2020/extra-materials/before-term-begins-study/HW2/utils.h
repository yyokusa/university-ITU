#ifndef UTILS_H
#define UTILS_H

#include <iostream> // cin cout
#include <cstdio> // file operations
#include <cstring> // string

#include "emails.h"
#include "circular.h"


#define DELIM '@'


int findDiffIndex(const char*, const char*);
int findDelimIndex(const char*, char);
void subString(const char*, const int, const int, char*);
void getNewEmail(StudentInfo*, StudentInfo*, char*);
// Emails* findStudentsListForGivenSurname(SurnameNode* head, StudentInfo* student);
Emails* isThereSuchSurname(SurnameNode* &head, SurnameNode* &tail, StudentInfo* student);
void addWithNewSurname(SurnameNode* &head, SurnameNode* &tail, StudentInfo* student);
StudentInfo* createStudent(char* name, char* surname);
void findSubString(const char* str, const int start, const int end, char* res);
void freedom(StudentInfo* student);


#endif