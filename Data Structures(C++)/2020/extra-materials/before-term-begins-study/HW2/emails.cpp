// struct studentInfo (contains name, surname and email information and related pointers).
#include "emails.h"
#include "utils.h"

#include <iostream> // cin cout
#include <cstdio> // file operations
#include <cstring> // strcmp, strcat
#include <cstdlib> // EXIT_FAILURE, exit()

using namespace std;


// Emails
void Emails::create() {
    head = NULL;
    tail = NULL;
    size = 0;
};

void Emails::addStudent(StudentInfo* newStudent) {
    StudentInfo* ptr = head;
    
    StudentInfo* student = new StudentInfo; // ???????? DELETE NEW
    *student = *newStudent;
    student->next = NULL;
    student->previous = NULL;

    // insert to empty list
    if (head == NULL) {
        strcat(student->email, student->surname);
        strcat(student->email, "@itu.edu.tr");
        student->same_name_number = 1;  // NEW
        head = student;
        tail = head;
        size++; // increase size by 1
        // NEW
        cout << "Email: " << student->email << endl;
        // NEW
        return;
    }
    //
    char newUserConcat[MAX_USER_NAME_AND_SURNAME] = "\0";
    strcat(newUserConcat, student->surname);
    strcat(newUserConcat, student->name);

    while (ptr != NULL && (strcmp(ptr->email, newUserConcat) < 0)) {
        ptr = ptr->next;
    }
    
    // insert to end
    if (ptr == NULL) {
        getNewEmail(tail,  student, newUserConcat);
        student->same_name_number = 1;  // NEW
        tail->next = student;
        student->previous = tail;
        tail = student;
    } else {
        
        // NEW START
        int at_index = findDelimIndex(ptr->email, DELIM); 
        char email_before_at[MAX_USER_NAME_AND_SURNAME];
        findSubString(ptr->email, 0, at_index, email_before_at);
        // akali@email, ++ another person named ali ak
        if (strcmp(email_before_at, newUserConcat) == 0) {
            ptr->same_name_number += 1;
            char s_num[10];
            sprintf(s_num, "%d", ptr->same_name_number);
            ptr->same_name_number += 1; // NEW
            strcat(newUserConcat, s_num);

            getNewEmail(ptr,  student, newUserConcat);
            student->previous = ptr->previous;
            student->next = ptr;
            ptr->previous->next = student;
            ptr->previous = student;


        } // NEW END


        else {
            // insert in btw
            getNewEmail(ptr,  student, newUserConcat);
            student->previous = ptr->previous;
            student->next = ptr;
            student->same_name_number = 1; // NEW
            ptr->previous->next = student;
            ptr->previous = student;
        }
    }
    size++; // increase size by 1
    // NEW
    cout << "Email: " << student->email << endl;
    // NEW
    return;
}

void Emails::makeEmpty() {
    StudentInfo* ptr;
    while (head) {
        ptr = head;
        cout << ptr->email << endl;
        head = head->next;
        delete ptr;
    }
    size = 0;
}

void Emails::deleteStudent(StudentInfo* student) {
    if (head == NULL || size == 0){cout<<"no element"<<endl;return;}
    if (head->next == NULL && (strcmp(head->name, student->name) == 0)) {this->create(); delete head;return;}
    StudentInfo* ptr = head;
    while (ptr != NULL && !(strcmp(ptr->name, student->name) == 0)) {ptr = ptr->next;}
    
    if (ptr == NULL) {
        cout << "Record does not exist!!!";
    }
    else if (ptr->previous == NULL) {
        head = ptr->next;
        delete ptr;
        size--;
    }
    else {
        ptr->previous->next = ptr->next;
        delete ptr;
        ptr = NULL;
        size--;
    }
}



// int main() {
//     char name1[] = "yasin";
//     char surname1[] = "yokus";
//     char name2[] = "kadir";
//     char surname2[] = "yokus";
//     char name3[] = "abdul";
//     char surname3[] = "yokus";
//     char name4[] = "abdul";
//     char surname4[] = "yokus";
    
//     char name5[] = "yasin";
//     char surname5[] = "tokus";
//     char name6[] = "kadir";
//     char surname6[] = "tokus";
//     char name7[] = "abdul";
//     char surname7[] = "tokus";
//     char name8[] = "cezmi";
//     char surname8[] = "tokus";
    
//     char name9[] = "yasin";
//     char surname9[] = "zokus";
//     char name10[] = "kadir";
//     char surname10[] = "zokus";
//     char name11[] = "abdul";
//     char surname11[] = "zokus";
//     char name12[] = "cezmi";
//     char surname12[] = "zokus";

//     StudentInfo* student1 = createStudent(name1, surname1);
//     StudentInfo* student2 = createStudent(name2, surname2);
//     StudentInfo* student3 = createStudent(name3, surname3);
//     StudentInfo* student4 = createStudent(name4, surname4);
    
//     StudentInfo* student5 = createStudent(name5, surname5);
//     StudentInfo* student6 = createStudent(name6, surname6);
//     StudentInfo* student7 = createStudent(name7, surname7);
//     StudentInfo* student8 = createStudent(name8, surname8);
    
//     StudentInfo* student9 = createStudent(name9, surname9);
//     StudentInfo* student10 = createStudent(name10, surname10);
//     StudentInfo* student11 = createStudent(name11, surname11);
//     StudentInfo* student12 = createStudent(name12, surname12);
    
//     Emails emailsList;
//     Emails emailsList2;
//     Emails emailsList3;
    
//     emailsList.create();
//     emailsList.addStudent(student1);
//     emailsList.addStudent(student2);
//     emailsList.addStudent(student3);
//     emailsList.addStudent(student4);
//     emailsList.makeEmpty();
    
//     emailsList2.create();
//     emailsList2.addStudent(student9);
//     emailsList2.addStudent(student10);
//     emailsList2.addStudent(student11);
//     emailsList2.addStudent(student12);
//     emailsList2.makeEmpty();
    
//     emailsList3.create();
//     emailsList3.addStudent(student5);
//     emailsList3.addStudent(student6);
//     emailsList3.addStudent(student7);
//     emailsList3.addStudent(student8);
//     emailsList3.makeEmpty();

//     freedom(student1);
//     freedom(student2);
//     freedom(student3);
//     freedom(student5);
//     freedom(student6);
//     freedom(student7);
//     freedom(student8);
//     freedom(student9);
//     freedom(student10);
//     freedom(student11);
//     freedom(student12);



//     return 0;   

// }