#include <iostream> // cin cout
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream> // file operations


#include "circular.h"
#include "utils.h"

using namespace std;



void SurnameMap::createList() {
    head = NULL;
    tail = NULL;
    size = 0;
}

void SurnameMap::insertNewRecord(StudentInfo* student) {
    // list is empty
    Emails* targetSurnameList = NULL;
    if (head == NULL) {
        addWithNewSurname(head, tail, student);
    } 
    else if (!(targetSurnameList = isThereSuchSurname(head, tail, student))) {
        addWithNewSurname(head, tail, student);
    }
    else // surname exists
    {
        if (!targetSurnameList) {cout<<"error line30" << endl;exit(1);}
        // insert to existing doubly ll
        // cout << "Inserting to existing Surname List line32" << endl;
        targetSurnameList->addStudent(student);
    }
    return;
}


void SurnameMap::deleteSurnameNode(char* surname) {
    if (head == NULL) {cout << "no element line40"<< endl;return;}
    SurnameNode* ptr = head;
    SurnameNode* prev = NULL;
    while (ptr != tail && strcmp(ptr->surname, surname) != 0) {
        prev = ptr;
        ptr = ptr->next;
    }
    if (strcmp(ptr->surname, surname) == 0) {
        ptr->studentsAndEmailsList->makeEmpty();
        prev->next = ptr->next;
        delete ptr->studentsAndEmailsList;
        delete ptr;
    }
    else if (ptr == tail) {
        cout << "No such surname!! line54" << endl;
    }
    return;
}

void SurnameMap::deleteStudent(StudentInfo* student) {
    if (head == NULL) {cout << "no element"<< endl;return;}
    SurnameNode* ptr = head;
    SurnameNode* prev = NULL;
    while (ptr != tail && strcmp(ptr->surname, student->surname) != 0) {
        prev = ptr;
        ptr = ptr->next;
    }
    if (strcmp(ptr->surname, student->surname) == 0) {
        ptr->studentsAndEmailsList->deleteStudent(student);
        // if (ptr->studentsAndEmailsList->size == 0) {this->deleteSurnameNode(ptr->surname);}
    }
    else if (ptr == tail) {
        cout << "No such surname!!" << endl;
    }
    return;
}

void SurnameMap::makeEmpty() {
    if (head == NULL) {cout << "no element"<< endl;return;}
    if (head == tail) {delete head;cout<<"Only element deleted"<<endl;return;}
    while (head != tail) {
        SurnameNode* _next = head->next;
        head->studentsAndEmailsList->makeEmpty();
        delete head->studentsAndEmailsList;// Doubly ll deleted
        delete head;
        head = _next;
    }
    tail->studentsAndEmailsList->makeEmpty();
    delete tail->studentsAndEmailsList;
    delete tail;
    return;
}

void SurnameMap::updateList(StudentInfo* oldStudent, StudentInfo* newStudent) {
    if (head == NULL) {cout << "no element"<< endl;return;}
    this->deleteStudent(oldStudent);
    this->insertNewRecord(newStudent);
    return;
}


void SurnameMap::insertAll() {
    char name[MAX_USER_NAME];
    char surname[MAX_USER_SURNAME];
    // ifstream studentsFile ("newStudentsList.txt");
    ifstream studentsFile ("sss.txt");
    if (studentsFile.is_open())
    {
        while (bool(studentsFile >> name >> surname) == true)
        {
            StudentInfo* student = createStudent(name, surname);
            cout << student->name << " " << student->surname << '\n';
            this->insertNewRecord(student);
            free(student);
            // check for EOF
            if (studentsFile.eof()) {
                cout << "[EoF reached]\n";
                break;
            }
        }
        studentsFile.close();
    }
    else cout << "Unable to open file"; 
}


void SurnameMap::writeToFile() {
    char name[MAX_USER_NAME];
    char surname[MAX_USER_SURNAME];
    char email[MAX_USER_EMAIL];

    ofstream emailsFile ("studentsWithEmails.txt");
    if (emailsFile.is_open())
    {   
        SurnameNode* ptr = head;
        while (ptr != tail) {
            emailsFile << "*************" << ptr->surname << "**********" << "\n";
            Emails* currEmails = ptr->studentsAndEmailsList;
            StudentInfo* studentPtr = currEmails->head;
            while (studentPtr != NULL) {
                strcpy(name, studentPtr->name);
                strcpy(surname, studentPtr->surname);
                strcpy(email, studentPtr->email);
                cout << "    " << name << "  " << surname << "  " << email << "\n";
                emailsFile << "    " << name << "  " << surname << "  " << email << "\n";
                studentPtr = studentPtr->next;
            }
            ptr = ptr->next;
        }
        emailsFile << "*************" << ptr->surname << "**********" << "\n";
        Emails* currEmails = ptr->studentsAndEmailsList;
        StudentInfo* studentPtr = currEmails->head;
        while (studentPtr != NULL) {
            strcpy(name, studentPtr->name);
            strcpy(surname, studentPtr->surname);
            strcpy(email, studentPtr->email);
            emailsFile << "    " << name << "  " << surname << "  " << email << "\n";
            studentPtr = studentPtr->next;
        }
        emailsFile.close();
    }
    else cout << "Unable to open file";
}



int main() {
    SurnameMap* SurnamesAndStudents = new SurnameMap;
    SurnamesAndStudents->insertAll();
    SurnamesAndStudents->writeToFile();
    free(SurnamesAndStudents);
/* 
    char name1[] = "yasin";
    char surname1[] = "yokus";
    char name2[] = "kadir";
    char surname2[] = "yokus";
    
    char name5[] = "yasin";
    char surname5[] = "tokus";
    char name6[] = "kadir";
    char surname6[] = "tokus";
    
    char name9[] = "yasin";
    char surname9[] = "zokus";
    char name10[] = "kadir";
    char surname10[] = "zokus";
    
    char name11[] = "tarik";
    char surname11[] = "akin";
    
    StudentInfo* student1 = createStudent(name1, surname1);
    StudentInfo* student2 = createStudent(name2, surname2);
    
    StudentInfo* student5 = createStudent(name5, surname5);
    StudentInfo* student6 = createStudent(name6, surname6);
    
    StudentInfo* student9 = createStudent(name9, surname9);
    StudentInfo* student10 = createStudent(name10, surname10);
    
    
    
    SurnameMap surnamesList;
    surnamesList.createList();
    surnamesList.insertNewRecord(student1);
    surnamesList.insertNewRecord(student2);
    
    surnamesList.insertNewRecord(student5);
    surnamesList.insertNewRecord(student6);
    
    surnamesList.insertNewRecord(student9);
    surnamesList.insertNewRecord(student10);
    
    // surnamesList.deleteStudent(student5);
    // surnamesList.deleteStudent(student6);


    // StudentInfo* student11 = createStudent(name11, surname11);
    // surnamesList.updateList(student10, student11);

    surnamesList.makeEmpty();

    freedom(student1);
    freedom(student2);
    freedom(student5);
    freedom(student6);
    freedom(student9);
    freedom(student10); */
    return 0;   
}


/*
    TODOS
    * Implement UTF - 8 (Turkish Characters) // OK 
    * Implement MIDDLE NAME
    * Implement case insensitivity
*/