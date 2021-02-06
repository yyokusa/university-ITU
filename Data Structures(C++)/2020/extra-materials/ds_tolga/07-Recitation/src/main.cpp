#include <iostream> // C++ giri�/��k�� fonksiyonlar� i�in
#include <stdlib.h> // system("cls") fonksiyonu i�in
#include <iomanip>  // cin.ignore(), setw, vb. kullan�mlar i�in
#include <cstring>


#include "queue.h" // Kapsül tanımları

using namespace std; 

Queue queue;

struct Customer{
    int arrival_time;
    int service_duration;
    int waiting_time;
    int leaving_time;
};

// Fonksiyon prototip tan�mlar�:
void print_menu();
bool perform_operation(char);
void initialize(Customer,int);
void print_results(Customer [], int);
void queue_simulation(Queue, Customer [], int);
void system_performance(Customer[], int);

int main()
{    
	bool end = false; 
	char choice; 	
	while (!end) { 
		print_menu(); 
		cin >> choice;
		end = perform_operation(choice); 
		} 
	return EXIT_SUCCESS;
}

// initialization of customer arrival times and service durations
void initialize(Customer customers[], int c_count){
    int arrival_time = 0;
	int max_time_between_two_customers=3;
	int max_service_duration=5;
    srand(time(NULL));
    for (int i=0; i < c_count; i++){
        customers[i].arrival_time = arrival_time + int(rand()%max_time_between_two_customers); // between 0-3 mins after previous customer
        customers[i].service_duration = int (1 + rand()%max_service_duration); // between 1-5 mins service duration
        arrival_time = customers[i].arrival_time;
    }
	print_results(customers,c_count);
}

void print_results(Customer customers[], int c_count){
    cout << "Customer num:\tArrival time:\tWaiting time\tService dur.\tLeaving time\n";
    cout << "--------------\t--------------\t--------------\t--------------\t--------------\n";
    for(int i=0; i < c_count; i++){
        cout << i << "\t\t"
            << customers[i].arrival_time << "\t\t"
            << customers[i].waiting_time << "\t\t"
            << customers[i].service_duration << "\t\t"
            << customers[i].leaving_time << endl;
    }
}

void run(){
	
	int c_count;
	cout << "Please enter the costumer count that will be simulated:" ;
	cin >> c_count;

    struct Customer * customers = new Customer[c_count];
    initialize(customers, c_count);

    Queue queue;
    queue.create();

    queue_simulation(queue, customers, c_count);
    print_results(customers, c_count);
    system_performance(customers, c_count);

    delete [] customers;
	queue.close();

    cout << "\nThe End!" << endl;
}

void queue_simulation(Queue q, Customer customers[], int c_count){
	int system_time = 0, leaving_index = 0, coming_index = 0;
	int next_idle_time = 1000;
	bool system_idle=true;
	int current_customer_id;
    while(leaving_index!=c_count-1)
	{
		while(system_time == customers[coming_index].arrival_time)
		{
			q.enqueue(coming_index++);
		}
		if(!q.isempty() && system_time == next_idle_time)
		{
			leaving_index = q.dequeue();
			system_idle = true;
			customers[leaving_index].leaving_time = system_time;
			customers[leaving_index].waiting_time = customers[leaving_index].leaving_time - customers[leaving_index].arrival_time -
															customers[leaving_index].service_duration;
		}

		if(!q.isempty()&& system_idle)
		{
			system_idle = false;
			current_customer_id = q.front->data;
			next_idle_time = (customers[current_customer_id].arrival_time < system_time) ? system_time: customers[current_customer_id].arrival_time;
			next_idle_time += customers[current_customer_id].service_duration;
		}
		cout << "at the end of" << system_time << " min, ";
		q.echo();
		system_time++;
	}
}

void system_performance(Customer customers[], int c_count){
    int total_idle_time = 0;
    int total_waiting_time = 0;
    int previous_costumer_leaving_time = 0;
    int i = 0;
    while (i < c_count){
        if(customers[i].arrival_time > previous_costumer_leaving_time){
            total_idle_time += customers[i].arrival_time - previous_costumer_leaving_time;
        }
        total_waiting_time += customers[i].waiting_time;
        previous_costumer_leaving_time = customers[i].leaving_time;
        i++;
    }
    cout << "Total idle time of the system: " << total_idle_time << " mins. "<<endl;
    cout << "Total waiting time: " << total_waiting_time << " mins. "<<endl;
	cout << "Average waiting time: "<< float(total_waiting_time)/c_count <<" mins. "<< endl;
}

void print_menu(){
	//system("clear"); 
	cout << endl << endl;
	cout << "QUEUE SIMULATION APP" << endl;
	cout << "Choose an operation" << endl;
	cout << "S: Simulate New Senerio" << endl;
	cout << "E: Exit" << endl;	
	cout << endl;
	cout << "Enter a choice {S,E}: ";
}

bool perform_operation(char choice){
	bool terminate=false;
	switch (choice) { 
		case 'S': case 's': 
				run();
				break; 
		case 'E': case 'e': 
			cout << "Are you sure you want to exit the program? (Y/N):";
			cin >> choice;
			if(choice=='Y' || choice=='y')
			{
				terminate=true; 
				break; 
			}
		default: 
			cout << "Error: You have entered an invalid choice" << endl; 
			cout << "Please try again {S, E}  :" ;
			cin >> choice;
			terminate = perform_operation(choice);
			break; 
	}
	return terminate;
}