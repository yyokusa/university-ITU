#include <iostream>
#include "queue.h"

using namespace std;

void Queue::create() {
    front = 0;
    back = -1;
    num_of_elements=0;
}

void Queue::clear() {
    front = 0;
    back = -1;
    num_of_elements=0;
}

void Queue::print_queue(){
    cout << "[ ";
    for(int i=front, j=0;j<num_of_elements;j++,i=(i+1)%QUEUECAPACITY)
        cout << element[i] << " ";
    
    cout << "] F:" << front << " B:" << back <<endl;
} 

bool Queue::enqueue(QueueDataType newdata) {
    if(!isfull()){   
        back = (back+1) % QUEUECAPACITY;
        num_of_elements++;
        element[back] = newdata;
        return true;
    }
    return false;
}

QueueDataType Queue::dequeue() {
    QueueDataType data = element[front];
    front = (front+1) % QUEUECAPACITY;
    num_of_elements--;
    return data;
}

bool Queue::isfull(){
    return num_of_elements == QUEUECAPACITY;
}

bool Queue::isempty(){
    return num_of_elements == 0;
}
