/*
Solve the following problem by filling the required places in the skeleton code. 

We want to check whether given input has proper matching parenthesis or not?  For example ( ) [ ] and [ ( ) ] has proper matching parenthesis but
 )( or ( [ ) ]  not. Let 0,1, 2, 3, 4 denote different types of left parenthesis such as (, [, ..  and 5, 6, 7, 8, 9 denote corresponding right 
 parenthesis such as ), ], ... Therefore 0-5,1-6, 2-7, 3-8, 4-9 are the parenthesis pairs that need to match. For example 1649 or 1496 has proper 
 matching parenthesis but 61 or 1946 not. We will provide you ten digit sequences such as 2334345666 and ask you to output TRUE if it is a proper 
 matching and FALSE if it is not. For example  1111166666, 2740591638 and 1327272786 should return TRUE; 3654112344 and 0000005555 should return FALSE.

You can use any library that you want. Also, you can ignore to check whether the user input contains numerical or alphabetical values.

*/


#include <iostream>
#include <stack> // new

#define INPUT_LENGTH 10
using namespace std;

bool check(char input[INPUT_LENGTH])
{
	//THIS FUNCTION RETURNS TRUE OR FALSE 
	stack<char> new_stack; // empty new_stack
    for(int i = 0; i < INPUT_LENGTH ; i++) {
        char curr = input[i];
        if (curr >= '0' && curr <= '4') { // if curr is a left_symbol, push onto stack
            new_stack.push(curr);
        }
        else { // if curr is right_symbol
            if (new_stack.empty()) {
				// cout << "left symbol is missing" << endl ;
				return false;
			}
            else { // pop an s symbol from the stack
                char value = new_stack.top();
				new_stack.pop();
				if ((int)value != (curr - 5)) {
					// cout << "Ordering not appropriate" << endl;
					return false;
				}
            }
        }
    }
    if (!(new_stack.empty())) {
		// cout << "missing right symbol" << endl;
		return false;
	}
    return true;
}





int main()
{	
	char input[11];
	cout<<"Enter the input:"<<endl;
	cin.getline(input,INPUT_LENGTH+1);
	if(check(input))
		cout<<"TRUE"<<endl;
	else
		cout<<"FALSE"<<endl;
	return 0;
}
