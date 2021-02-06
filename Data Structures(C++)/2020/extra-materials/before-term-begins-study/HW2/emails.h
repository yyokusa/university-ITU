#ifndef EMAILS_H
#define EMAILS_H

#include <iostream> // cin cout
#include <cstdio> // file operations
#include <cstring>
 


#define MAX_USER_SURNAME 60
#define MAX_USER_NAME 60
#define MAX_USER_EMAIL 200
#define MAX_USER_NAME_AND_SURNAME 120


// StudentInfo:
// node blueprint for Doubly Linked List
struct StudentInfo {
    char name[MAX_USER_NAME];
    char surname[MAX_USER_SURNAME];
    char email[MAX_USER_EMAIL];
    StudentInfo* next;
    StudentInfo* previous;
    int same_name_number;
};

// double linked list of emails
struct Emails {
    StudentInfo* head;
    StudentInfo* tail;
    int size;
    void create(); // create list
    void makeEmpty(); // empty list
    void addStudent(StudentInfo*); // add student record
    void deleteStudent(StudentInfo*); // delete student record
};

#endif