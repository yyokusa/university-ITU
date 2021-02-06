#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

float average(int *, int);
float new_average(int *, int, int, int);

int main()
{
	// &x        --> referencing x
	// *ptr      --> dereferencing ptr
	// type* var --> declaring pointer to var of type

	int grades2[3][10] = {{50,86,55,45,70,12,43,12,76,90}, 			
                          {55,13,45,45,65,13,45,30,55,95},
                          {45,60,75,10,76,10,80,35,65,98}};

	float sum = 0, grandsum = 0;

	/*
    for (int i = 0; i < 3; i++){	      // for each exam of the three exams
		sum = 0;
		for (int j = 0; j < 10; j++)  // sum over 10 students for an exam
			sum += grades2[i][j];
		cout << i + 1 <<". exam average=" << sum/10 << endl;		
	}*/
	/*
    for (int i = 0; i < 3;i++)		
		cout << i + 1 <<". exam average=" 		     
          << average(grades2[i], 10) <<endl;
    */
	/*
    for (int i = 0; i < 3; i++){		
        cout << i + 1 << ". exam average="
                << new_average(&grades2[0][0], i*10, 10, 1)
                << endl;
        sum += new_average(&grades2[0][0], i*10, 10, 1);
    }
*/
	/*
	for (int i = 0; i < 10; i++){    // for each of the 10 students
		sum = 0;
		for (int j = 0; j < 3; j++)  // sum over the 3 exams for a student
			sum += grades2[j][i];
		cout << i + 1 <<". student average=" << sum/3 << endl;		
		grandsum += (sum/3);       // add the averages of all 10 students
	}
    cout << "Class average=" << (grandsum/10) <<endl;
*/
	/*
    for (int i = 0; i < 10; i++)
        cout << i + 1 << ". student's average=" << new_average(&grades2[0][0], i, 3, 10) << endl;


    cout << "Class Average=" << (sum/3) << endl; 
*/

	getchar();
	return EXIT_SUCCESS; //-->stdlib.h
}

float average(int *aPtr, int size)
{
	int sum = 0;
	for (int i = 0; i < size; i++)
	{
		sum += aPtr[i];
	}
	return (float)sum / (float)size;
}

float new_average(int *aPtr, int start, int size, int offset)
{
	int sum = 0;
	for (int i = 0; i < size; i++)
	{
		sum += *(aPtr + start + i * offset);
	}
	return (float)sum / (float)size;
}
