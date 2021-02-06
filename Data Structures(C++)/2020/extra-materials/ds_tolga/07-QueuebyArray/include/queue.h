#pragma once
#define QUEUECAPACITY 5

typedef char QueueDataType;
struct Queue {
	QueueDataType element[QUEUECAPACITY];
	int front;
	int back;
	int num_of_elements;
	void create();
	void clear();
    void print_queue();
	bool enqueue(QueueDataType);
	QueueDataType dequeue();
	bool isempty();
	bool isfull();
};
