/* @Author
Student Name:YASIN ABDULKADIR YOKUS
Student ID :150190739
Date:09/12/2020
*/

#include "2730645.h"
#ifndef HEADERFILE_H
#define HEADERFILE_H
#include <iostream>
#include <string>
#endif
using namespace std;
/*Write the necessary C++ data structures and methods in order to execute question3.
Please  also keep in mind that your code must have no memory leaks.
So please also provide extra methods which are necessary to escape memory leaks
although not invoked within the below function.
*/
void Linkedlist::create() {
    head = NULL;
}

void Linkedlist::clear() {
    Node* ptr = head;
    Node* temp = ptr;
    while(ptr != NULL) {
        temp = ptr;
        ptr = ptr->next;
        cout << "Deleting the value " << temp->value << endl;
        delete ptr;
    }
	head = NULL;
}

void Linkedlist::add2beginning(int i) {
    Node* new_node = new Node;
    new_node->next = NULL;
    new_node->value = i;
    if (head == NULL) {
        head = new_node;
        cout << "added the value " << new_node->value << " as head " << endl;
    }
    else {
        new_node->next = head;
        head = new_node;
        cout << "added the value " << new_node->value << endl;
    }
}
void question3(){
	Linkedlist l;
	l.create();
	for (int i = 0; i < 4; i++)
		l.add2beginning(i); 
	l.clear();
}
