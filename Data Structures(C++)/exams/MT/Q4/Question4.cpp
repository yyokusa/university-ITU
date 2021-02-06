/* @Author
Student Name:YASIN ABDULKADIR YOKUS
Student ID :150190739
Date:09/12/2020
*/

//25 pts
/*Write the multilist struct where the node structure is given. 
Each node should have two pointers (next and root).
Each node's next pointer will point to the
next integer in the list as usual.
The list should be sorted in ascending order.
If a number has an integer root (e.g. 9's root is 3 which is an integer)
its node's root pointer should point to its root's node  otherwise it should be NULL.
write the methods returnadressof and add.
The add method should add n numbers from 1 to n (the function input argument) to the multilist.
e.g. when the argument is 100 it will add 100 numbers with a single function call.
You may assume that the multilist will always be empty when the add method is called.
The root pointer of the node carrying "1" should always be  NULL.
hint you may use the sqrt and floor methods from <math.h>.
*/
#include "Question4.h"
#ifndef HEADERFILE_H
#define HEADERFILE_H
#include <iostream>
#include <string>
#include <math.h>
#endif
using namespace std;


void question4(){
	Multilist l;
	l.create();
	l.add(10000);
	l.printroots(l.returnadressof(6561));//will print "6561 81 9 3 \n" accordingly
	l.printroots(l.returnadressof(16));//will print "6561 81 9 3 \n" accordingly
	l.printroots(l.returnadressof(3));//will print "6561 81 9 3 \n" accordingly
	l.printroots(l.returnadressof(8));//will print "6561 81 9 3 \n" accordingly
	l.printroots(l.returnadressof(17));//will print "6561 81 9 3 \n" accordingly
	l.printroots(l.returnadressof(31));//will print "6561 81 9 3 \n" accordingly
	l.printroots(l.returnadressof(41));//will print "6561 81 9 3 \n" accordingly
}



void Multilist::add(int number){
	mnode* ptr = headptr;
	mnode* new_node = headptr;
	for (int i = 1; i <= number; i++)
	{
		new_node = new mnode;
		new_node->data = i;
		if (new_node->data == 1 && headptr == NULL) {
			new_node->root = NULL;
			headptr = new_node;
			ptr = headptr;
			continue;
		}
		else if (sqrt(new_node->data) == floor(sqrt(new_node->data))) { // root ptr
			new_node->root = returnadressof((int)sqrt(new_node->data)); // returns root address
			// cout << "Called  value " << new_node->data << endl;
			// cout << "Reeturned address is " << new_node->root->data << endl;
		} else {
			new_node->root = NULL;
		}
		// update traverse
		ptr->next = new_node;
		ptr = new_node;
	}
}

void Multilist::printroots(mnode *start){
	while (start != NULL){
		cout << start->data << " ";
		start = start->root;
	}
	cout << endl;
}

void Multilist::create(){
	headptr = NULL;
}

mnode* Multilist::returnadressof(int value){
	mnode* ptr = headptr;
	int counter = 1;
	while (counter < value) {
		ptr = ptr->next;
		counter++;
	}
	return ptr;
}



