#include <iostream>
#include <fstream>
#include <string>
#include <string.h>				   
#include <queue>
using namespace std;
/*Assuming that you are given two sorted singly linked list, whose data structures and creation methods are provided below, you are asked to 
write a mergeList function which will create a new sorted linked list from the input lists' elements.
mergeList takes 3 arguments (adresses of Linked List structures), where the first 2 are the input linked lists and the 3rd one is the 
output linked list. Your program shouldn't take any new memory but rather use the nodes of the input lists and link them to each other.
After the operation, the original lists' will be empty.
The signature of the method and the main function are provided. 
You are NOT allowed to change the main function. Please only fill in
the body part of the mergeList method. Writing extra methods to existing structures is allowed but they could  only be invoked by the mergeList function.
A sample input file (input.txt with an empty line between the two linked lists' elements) and a sample output message are provided. Your code will be tested with similar inputs.
Attention: if the same number appears in both of the input list, it should appear only ONCE in the last list. In such a case, Don't forget to delete the unnecessary (extra) node.
The given input file should produce the following output:*/
struct Node{
	int data;
	Node *next;
};
struct LinkedList{
	Node *head, *tail;
	void add(int);
	
	void create();
	void print();
};
void LinkedList::create(){
	head = NULL; tail = NULL;
}
void LinkedList::print(){
	Node *t = head;
	while (t){
		cout << t->data << " ";
		t = t->next;
	}
}
void LinkedList::add(int indata){
	Node *newnode = new Node;
	newnode->data = indata;
	newnode->next = NULL;
	if (head == NULL){
		head = newnode;
		tail = newnode;
		return;
	}
	tail->next = newnode;
	tail = newnode;
}

void mergeList(LinkedList *l1, LinkedList *l2, LinkedList *l3){
	Node* ptr1 = l1->head;
	Node* ptr2 = l2->head;
	Node* ptr3 = l3->head;
	if (ptr3 == NULL && ptr1 != NULL && ptr2 != NULL) {   // l3->head is NULL at first
		if (ptr1->data < ptr2->data) {
			ptr3 = ptr1;
			ptr1 = ptr1->next;
		} else if (ptr1->data > ptr2->data) {
			ptr3 = ptr2;
			ptr2 = ptr2->next;
		} else {
			ptr3 = ptr1;
			Node* temp = ptr2->next;
			delete ptr2;                               // delete other w/ same data
			ptr2 = temp;                               // update ptr2
			ptr1 = ptr1->next;
		}
	}
	l3->head = ptr3;
	while (ptr1 != NULL && ptr2 != NULL) {      // go as long as small list (ASSUMING nodes added with LL:add method so [l2 or l1]->tail->next is NULL)
		if (ptr1->data < ptr2->data) {                  // list 1 element is smaller
			ptr3->next = ptr1;                                // list 3 traverse pointer points new element
			ptr1 = ptr1->next;                          // update
		} else if (ptr1->data > ptr2->data) {           // list 2 element is smaller
			ptr3->next = ptr2;
			ptr2 = ptr2->next;                         // update
		} else {                                       // elements are equal
			ptr3->next = ptr1;                               // take anyone you want
			Node* temp = ptr2->next;
			delete ptr2;                               // delete other w/ same data
			ptr2 = temp;                               // update ptr2
			ptr1 = ptr1->next;
		}
		ptr3 = ptr3->next;                             // update ptr3
	}
	// non equal lengths case 1
	while (ptr1 != NULL) {                            // (ASSUMING nodes added with LL:add method so [l2 or l1]->tail->next is NULL)
		ptr3->next = ptr1;
		ptr1 = ptr1->next;
		ptr3 = ptr3->next;                             // update ptr3
	}
	// non equal lengths case 2
	while (ptr2 != NULL) {                            // (ASSUMING nodes added with LL:add method so [l2 or l1]->tail->next is NULL)
		ptr3->next = ptr2;
		ptr2 = ptr2->next;
		ptr3 = ptr3->next;                             // update ptr3
	}
	l1->head = NULL;
	l2->head = NULL;
}
int main(int argc, char* argv[]){
	LinkedList myl1, myl2, myl3;
	myl1.create(); myl2.create(); myl3.create();
	string line;
	string filepath="inputQ2.txt";
	if (argc>1)
	{
	filepath=argv[1];
	}
	ifstream myfile(filepath);
	if (myfile.is_open())
	{
		while (getline(myfile, line) && line!="" && line!="\r")
		{
			myl1.add(stoi(line));
		}
		while (getline(myfile, line) && line!="" && line!="\r")
		{
			myl2.add(stoi(line));
		}
		myfile.close();
	}
	else cout << "Unable to open file";

	myl1.print();
	cout << endl << "####" << endl;
	myl2.print();
	cout << endl << "####" << endl;

	mergeList(&myl1,&myl2,&myl3);

	myl1.print();
	cout << endl << "####" << endl;
	myl2.print();
	cout << endl << "####" << endl;
	myl3.print();
	getchar();
	return 0;		
}
