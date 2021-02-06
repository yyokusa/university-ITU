#include <iostream>
#include "queue.h"

using namespace std; 

void Queue::create(){
    front = NULL;
    back = NULL;
}

void Queue::close(){
    Node * del;
    while (front){
        del = front;
        front = front->next;
        delete del;
    }
}

void Queue::enqueue(QueueDataType newdata){
    Node * newnode = new Node;
    newnode->data = newdata;
    newnode->next = NULL;
    if(isempty()){
        front = back = newnode;
    }
    else{
        back->next = newnode;
        back = newnode;
    }
}

QueueDataType Queue::dequeue(){
    Node * topnode;
    topnode = front;
    front = front->next;

    QueueDataType retdata = topnode->data;
    delete topnode;
    return retdata;
}

bool Queue::isempty(){
    return front == NULL;
}

void Queue::echo(){
    Node *traverse =front;
    cout<<"QUEUE : ";
    for (;traverse;traverse=traverse->next)
        cout<<" "<<traverse->data;
    cout<<endl;
}