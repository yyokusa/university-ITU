#include <stdio.h>
#include <stdbool.h>

bool solve(int);
int main()
{
    int a_num;
    bool result;
    printf("Write a number for program to detect if it is a armstrong number or not:\n");
    scanf("%d",&a_num);
    result = solve(a_num);
    printf("%d\n",result);
    return 0;
}
bool solve(int a_num) {
    int temp = a_num;       // because we are changing the value of a_num we have to hold initial value at somewhere!!!!!!!!! 
    int res = 0;
    int flag = 1;
    int elements[6] = {0, 0, 0, 0, 0, 0};                   // int num[5] =  { };                // num = {0, 0, 0, 0, 0}
    int count = 0;                                          // int num[5] =  { 0 };             // num = {0, 0, 0, 0, 0}
    while (flag)
    {
        elements[count] = a_num % 10;
        a_num /= 10;
        if (0 == a_num)
        {
            flag = 0;
        }
        ++count;        
    }
    for (size_t i = 0; i < count; i++)
    {
        res += (elements[i] * elements[i] * elements[i]);
    }
    if(res == temp) {
        return true;
    }
    else {
        return false;
    }
}


/*
Designated Initializer: This initializer is used when we want to initialize
 a range with the same value. This is used only with GCC compilers.
[ first . . . last ] = value;

int num[5]={ [0 . . . 4 ] = 3 };               // num = { 3, 3, 3, 3, 3}

We may also ignore the size of array:

int num[  ]={ [0 . . . 4 ] = 3 };               // num = { 3, 3, 3, 3, 3}
*/

/* 
#include <stdio.h> 
#define INCREMENT(x) ++x 
int main() 
{
    char words[] = "GeeksQuiz";
	char* ptr = words; 
	int x = 10; 
	printf("%s ", INCREMENT(ptr));
	printf("%p ", ptr);                             //same adress as words + 1              words and ptr points to same memory adress
	printf("%p ", words + 1);
	printf("%d", INCREMENT(x)); 
	return 0; 
} 
*/