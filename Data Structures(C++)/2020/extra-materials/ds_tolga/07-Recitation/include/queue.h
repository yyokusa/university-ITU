#ifndef QUEUE_H
#define QUEUE_H
#include "node.h"

class Queue{
public:
    Node * front;
    Node * back;
    void create();
    void close();
    void enqueue(QueueDataType);
    QueueDataType dequeue();
    bool isempty();
	void echo();
};
#endif