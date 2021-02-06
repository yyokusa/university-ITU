#include <iostream>
#include <stdlib.h>
#include "queue.h"

using namespace std;

int main()
{
	Queue<int> a_queue;
	a_queue.create();

	a_queue.enqueue('A');
	a_queue.enqueue('B');
	a_queue.print_queue();

	a_queue.dequeue();
	a_queue.dequeue();
	a_queue.enqueue('C');
	a_queue.print_queue();

	a_queue.close();
	getchar();
	return EXIT_SUCCESS; 
}
