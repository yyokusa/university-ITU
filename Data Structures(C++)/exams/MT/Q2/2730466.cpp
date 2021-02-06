/*Question#2-A palindrome is a word, number, phrase, or other sequence of characters 
which reads the same backward as forward, such as madam, racecar. Write a function
"char* question2answer(char *instring)" which
takes an argument string and turns it into a palindrome-like string but with a single 
difference from the classical definition. The string will consist of numerical values and 
the first half of the produced string will consist of numbers smaller (-2) than the second
half numbers such as in input=1234 output=2101234 instead of "4321234".  
If you find a negative number during subtraction put 0 instead such as in input=2002 output=0002002
You are not allowed to use c++ strings in your answer. 
Use either character arrays or pointers.
The only function that you may use from string class
is the "strlen" function*/
#include <iostream>
#include <string>
using namespace std;
//15pts
char* question2answer(char *instring){
	int inlen = strlen(instring);
	char *outstring = new char[2 * inlen - 1];
	int k = 0;
	for (int i = inlen - 1; i > 0; i--)
	{
		int num = instring[i];
		num -= 2;
        if (num < 48) {
            outstring[k++] = '0';
            continue;
        }
        outstring[k++] = num;
	}
	k = inlen - 1;
	for (int i = 0; i < inlen; i++)
	{
		outstring[k++] = instring[i];
	}
	return outstring;
}

int main() {
    char a[15];
    cout << "Enter num ";
    cin >> a;
    cout << question2answer(a) << endl;
    return 0;
}

