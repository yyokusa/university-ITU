#include <iostream>
#include <stdlib.h>

#include "functions.h"
#include "tests.h"
#include "stack.h"
#include "directions.h"

using namespace std;

void test_factorial(int n){

	try{
		int fact = recursive_factorial(n);
		cout << "Factorial of "<< n <<" is: " << fact << endl;
	}
	catch(const char* message){
		cout << message << endl;
	}
}

void test_binary_sum(int len){
	int *arr = new int[len];

	for(int i=0;i<len;i++)
		arr[i] = i+1;

    binary_sum(arr, 0, len, 0);
    //cout << "Sum is: " << binary_sum(arr, 0, len ,0) << endl;
}

void test_permutations(int len){
    //iterative_permutation();
    char *arr = new char[len];

	for(int i=0;i<len;i++)
		arr[i] = 65+i;

    recursive_permutation(arr, 0, len-1);
}

void test_n_queens(int len){	
    int *arr = new int[len];

	for(int i=0;i<len;i++)
		arr[i] = i+1;

    n_queens(arr, 0, len-1, len);
}

void test_hanoi(int disks){
	int source = 0;
	int dest = 2;
	int temp = 1;

	Stack<char> pegs[3];

	for (int i = 0; i < 3; i++)
		pegs[i].create();

	for (int i = 0; i < disks; i++)
		pegs[0].push(64 + disks - i);

	hanoi_recursive(pegs, disks, source, dest, temp);

	for (int i = 0; i < 3; i++)
		pegs[i].close();
}

void test_recursive_maze(){
	/*
	char maze[MAZE_VER_SIZE][MAZE_HOR_SIZE] = {{'#','#',' ','#'},
				      						   {' ',' ',' ',' '},
										       {'#',' ','#','#'},
				    						   {'#','#','#','#'},
		};
	int enter_y=1;
	int enter_x=0;
	int exit_y=1;
	int exit_x=3;
	*/

	char maze[MAZE_VER_SIZE][MAZE_HOR_SIZE] = {{'#','#','#','#','#','#','#','#'},
				      						   {' ',' ','#','#','#',' ',' ',' '},
										       {'#',' ','#','#','#',' ','#','#'},
				    						   {'#',' ',' ',' ',' ',' ',' ','#'},
				       						   {'#',' ','#',' ','#','#',' ','#'},
				      						   {'#',' ','#','#',' ','#',' ','#'},
				     						   {'#',' ',' ','#',' ',' ',' ','#'},
				    						   {'#','#','#','#','#','#','#','#'}
		};
	int enter_y=1;
	int enter_x=0;
	int exit_y=1;
	int exit_x=7;

	if (find_path_recursive(maze, enter_y, enter_x, exit_y, exit_x, LEFT))
		cout << "!!!! PATH found !!!!" << endl << endl;

	print_maze(maze);

}