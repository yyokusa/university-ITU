#include "utils.h"
using namespace std;


int findDiffIndex(const char* str1, const char* str2) {
    int index = 0;
    char a;
    char b;
    while ((a = str1[index]) != '\0' && (b = str2[index]) != '\0') {
        if (a == b)
            index++;    
        else
            break;
    }
    return index;
}

int findDelimIndex(const char* str1, char delim) {
    int index = 0;
    char a;
    while (str1[index] != '\0') {
        if (str1[index] == delim)
            return index;
        index++;
    }
    return 0;
}
// send return value of findDelimIndex to this as end, end is not inclusive
void findSubString(const char* str, const int start, const int end, char* res) {
    int index = 0;
    while (index < end && str[index] != '\0') {
        res[index] = str[index];
        index++;
    }
    res[index] = '\0';
}

void getNewEmail(
    StudentInfo* ptr,
    StudentInfo* student,
    char* newUserConcat)
{
    char subString[MAX_USER_NAME_AND_SURNAME] = "\0";
    int delimIndex = findDelimIndex(ptr->email, DELIM);
    findSubString(ptr->email, 0, delimIndex, subString); // subString: email prefix
    int diffIndex = findDiffIndex(newUserConcat, subString);
    findSubString(newUserConcat, 0, diffIndex + 1, subString);
    diffIndex = findDiffIndex(newUserConcat, subString);
    strcat(subString, "@itu.edu.tr");
    strcpy(student->email, subString);
}

// for circular.cpp
Emails* isThereSuchSurname(SurnameNode* &head, SurnameNode* &tail, StudentInfo* student) {
    SurnameNode* ptr = head;
    
    // cout << "Checkin if surname: " << student->surname << " exists." << endl;
    while (ptr != tail && (strcmp(ptr->surname, student->surname) != 0)) {
        ptr = ptr->next;
    }
    if (strcmp(ptr->surname, student->surname) == 0) {
        return ptr->studentsAndEmailsList; // return the students list;
    }
    // cout << "No such surname!!!" << endl;
    return NULL;
}

// line 74: & operator is important
// create a SurnameNode, create a Emails (dll) node and add student to Emails
void addWithNewSurname(SurnameNode* &head, SurnameNode* &tail, StudentInfo* student) {
    // list is empty or there is no such surname
    if (head == NULL) {
        head = new SurnameNode;
        strcpy(head->surname, student->surname);
        head->studentsAndEmailsList = new Emails;
        head->studentsAndEmailsList->create();
        head->studentsAndEmailsList->addStudent(student);
        tail = head;
        tail->next = head; // create cycle
        head->next = tail;
        // cout << "first one added and value is " << head->surname << endl;
        return;
    }

    // there are surname lists but none with the specified surname
    SurnameNode* ptr = head;
    SurnameNode* prev = NULL;

    // insert as the head
    if (strcmp(head->surname, student->surname) > 0) {
        SurnameNode* newNode = NULL;
        newNode = new SurnameNode; // newNode as temp ptr // insert after head
        strcpy(newNode->surname, student->surname);
        newNode->studentsAndEmailsList = new Emails;
        newNode->studentsAndEmailsList->create();
        newNode->studentsAndEmailsList->addStudent(student);
        newNode->next = head;
        head = newNode;
        // cout << "aaskdas???     " << student->surname<< endl;
        // cout << "another one added and value is " << head->surname << endl;
        return;
    }

    while (ptr != tail && (strcmp(ptr->surname, student->surname) < 0)) {
        prev = ptr;
        ptr = ptr->next;
    }
    // insert at the end
    if (ptr == tail) {
        tail->next = new SurnameNode; // break the cycle
        strcpy(tail->next->surname, student->surname);
        tail = tail->next; // set new tail ptr
        tail->studentsAndEmailsList = new Emails; // Doubly ll created dynamically
        tail->studentsAndEmailsList->create();
        tail->studentsAndEmailsList->addStudent(student);
        tail->next = head; // restore the cycle
        // cout << "another one added and value is " << tail->surname << endl;
    } else {
        // insert before
        // cout << "akin comes here???     " << student->surname<< endl;
        prev->next = new SurnameNode;
        strcpy(prev->next->surname, student->surname);
        prev->next->studentsAndEmailsList = new Emails;
        prev->next->studentsAndEmailsList->create();
        prev->next->studentsAndEmailsList->addStudent(student);
        prev->next->next = ptr;
        // cout << "another one added and value is " << prev->next->surname << endl;
    }
    return;
}

StudentInfo* createStudent(char* name, char* surname) {
    StudentInfo* student = new StudentInfo;
    strcpy(student->name, name);
    strcpy(student->surname, surname);
    strcpy(student->email, "");
    student->next = NULL;
    student->previous = NULL;
    return student;
}

void freedom(StudentInfo* student) {
    free(student);
}