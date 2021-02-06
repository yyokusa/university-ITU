#include <iostream> 
#include <stdlib.h> 
#include <iomanip>  
#include <cstring>


#include "stack.h" 

using namespace std; 

Stack stack;

void print_menu();
bool perform_operation(char);
void convert();
int get_precedence(char);

int main(){
	bool end = false; 
	char choice; 	
	while (!end) { 
		print_menu(); 
		cin >> choice;
		end = perform_operation(choice); 
		} 
	return EXIT_SUCCESS;
}

void print_menu(){
	//system("clear"); 
	cout << endl << endl;
	cout << "INFIX POSTFIX CONVERTER APP" << endl;
	cout << "Choose an operation" << endl;
	cout << "C: Convert New Input" << endl;
	cout << "E: Exit" << endl;	
	cout << endl;
	cout << "Enter a choice {C,E}: ";
}

bool perform_operation(char choice){
	bool terminate=false;
	switch (choice) { 
		case 'C': case 'c': 
				convert();
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
			cout << "Please try again {C, E}  :" ;
			cin >> choice;
			terminate = perform_operation(choice);
			break; 
	}
	return terminate;
}

int get_precedence(char c)
{
	if(c == '^') 
    	return 3; 
    else if(c == '*' || c == '/') 
    	return 2; 
    else if(c == '+' || c == '-') 
    	return 1; 
    else
    	return -1; 
}

void convert()
{
	int max_input_size=50;
	char input[max_input_size];
	cout<<" Please enter the input that you want to convert infix version to postfix version:"<<endl;
	cin.ignore(1000,'\n');
	cin.getline(input,max_input_size);

	stack.initiate();
	int input_size=strlen(input);
	char *output = new char[input_size+1];
	int j=0;
	for(int i=0;i<input_size;i++){
		if ((input[i]>='a' && input[i]<='z') || (input[i]>='A' && input[i]<='Z'))
			output[j++]=input[i];
		else if (input[i]=='(')
		{
			stack.push(input[i]);
		}
		else if (input[i]==')')
		{
			while(!stack.isEmpty() && stack.peek()!='(')
				output[j++]=stack.pop();
			if(!stack.isEmpty() && stack.peek()=='(')
				stack.pop();
		}
		else
		{
			while(!stack.isEmpty() && get_precedence(stack.peek())>=get_precedence(input[i]))
				output[j++]=stack.pop();
			stack.push(input[i]);			
		}		
	}
	while (!stack.isEmpty())
	{
		output[j++]=stack.pop();
	}
	stack.close();
	output[j] = '\0';
	cout<<output<<endl;
	delete [] output;
}
