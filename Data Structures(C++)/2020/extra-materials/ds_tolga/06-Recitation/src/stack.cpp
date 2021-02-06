#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

using namespace std;

void Stack::initiate(){
    top = NULL;
    node_count=0;
}

void Stack::push(char input){
    Node *nn=new Node;
    nn->character=input;
    nn->next=NULL;

    if (top==NULL) // there is no node in stack
        top=nn;
    else  // n t
    {
        nn->next=top;
        top=nn;
    }
    node_count++;    
}

char Stack::pop(){
    if(node_count>0){
        Node *tmp=top;
        char c=tmp->character;
        top=top->next; // b c
        node_count--;
        delete tmp;
        return c;
    }
    else
    {
        return ' ';
    }
    
}

char Stack::peek(){
    return top->character;
}

bool Stack::isEmpty(){
    return top==NULL?true:false;
}

void Stack::close(){
    while (top)
    {
        pop();
    }
}

void Stack::printStack(){
    Node *traverse =top;
    cout<<endl<<"CURRENT VERSION OF STACK: ";
    for (;traverse;traverse=traverse->next)
        cout<<" "<<traverse->character;
    cout<<endl;
}
