#pragma once
#include <iostream>
#include <stdlib.h>
using namespace std;

template <typename QNT>
struct Node{               
	QNT data;
	Node<QNT> *next;
};

template <typename QDT>
struct Queue {
	Node<QDT> *front;
	Node<QDT> *back;	
	void create();
	void close();
	void print_queue();
	void enqueue(QDT);
	QDT dequeue();
	bool isempty();
};

template <typename QDT>
void Queue<QDT>::create(){
	front = NULL; 
	back = NULL;
}

template <typename QDT>
void Queue<QDT>::close(){
	Node<QDT> *p;
	while (front) {
		p = front;
		front = front->next;
		delete p;
	}
}

template <typename QDT>
void Queue<QDT>::enqueue(QDT newdata){
	Node<QDT> *newnode = new Node<QDT>;
	newnode->data = newdata;
	newnode->next = NULL;
	if ( isempty() ) {    // first element?
		back = newnode;
		front = back;
	}
	else {
		back->next = newnode;
		back = newnode;
	}

}

template <typename QDT>
QDT Queue<QDT>::dequeue() {
	Node<QDT> *topnode;
	QDT temp;
	topnode = front;
	front = front->next;
	if(front == NULL)
		back = NULL;

	temp = topnode->data;	
	delete topnode;
	return temp;
}

template <typename QDT>
bool Queue<QDT>::isempty() {
	return front == NULL;
}

template <typename QDT>
void Queue<QDT>::print_queue(){
	Node<QDT> *p=front;
	cout << "[ ";
	while (p) {
		cout << p->data << " ";
		p = p->next;
	}
	
	cout << "]" << endl;
}
