#include <iostream>
#include <stdlib.h>
#include "queue.h"

using namespace std;

int main()
{

	Queue q;

	q.create();
	q.enqueue('A');
	q.enqueue('B');

	q.print_queue();
	
	cout << q.dequeue() << endl;
	q.enqueue('C');
	q.enqueue('D');
	if(!q.enqueue('E'))
		cout<<"Unable to enqueue!!" << endl;

	cout << q.dequeue() << endl;
	cout << q.dequeue() << endl;
	q.print_queue();

	if(!q.enqueue('F'))
		cout<<"Unable to enqueue!!" << endl;

	q.clear();
	q.print_queue();
	q.enqueue('F');
	if(!q.enqueue('G'))
		cout<<"Unable to enqueue!!" << endl;

	q.print_queue();

	getchar();
	return EXIT_SUCCESS; 
}
