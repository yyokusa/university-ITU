#include <math.h>
#include <iostream>
#include "functions.h"

using namespace std;

int recursive_factorial(int n){
	int m;

	if(n<0)
		throw "Factorial undefined for negative numbers!";
	else if(n==0)
		return 1;
	else
		return n * recursive_factorial(n-1);
}

int iterative_factorial(int n){
	int i,p;
	
	if(n<0)
		throw "Factorial undefined for negative numbers!";
	
	p=1;
	for(i=2; i<=n; i++)
		p *= i;

	return p;
}

int binary_sum(const int* arr, int start, int end, int level){
	if(end-start==1){
        for(int i=0;i<level;i++)
            cout <<"...";
        cout <<start<<"-"<<end<<"-"<< arr[start] << endl;
        return arr[start];
    }
    else{
        int mid = (start+end)/2;
        int sum = binary_sum(arr,start,mid,level+1)+binary_sum(arr,mid,end,level+1);
        
        for(int i=0;i<level;i++)
            cout <<"...";
        cout <<start<<"-"<<end<<"-"<< sum << endl;
        return sum;
    }
}

void iterative_permutation(){
    for (int i1 = 1; i1 <= 3; i1++) {
        for (int i2 = 1; i2 <= 3; i2++) {
            if (i2 != i1) {
                for (int i3 = 1; i3 <= 3; i3++) {
	                if ( (i3 != i1) && (i3 != i2) ) {
		                cout << (char)(64+i1) << " "<< (char)(64+i2) << " "<< (char)(64+i3) << endl;
	                }
	            }
            }
        }
    }
}

void recursive_permutation(char* arr, int start, int end){
    int i;
    if (start == end) { 
  	    for (i = 0; i <= end; i++) 
       	    cout << arr[i] << " ";
     	cout << endl;
    }
    else { 
        for (i = start; i <= end; i++){
  	 	    std::swap(arr[start], arr[i]);
  	 	    recursive_permutation(arr, start + 1, end);
  	 	    std::swap(arr[start], arr[i]);
        }
  	}	
}

bool test_queens(int* arr,int len){
    bool hit = false;
    for(int i=0;i<len;i++){
        for(int j=1;j<len-i;j++){
            if(abs(arr[i+j]-arr[i])==j)
                hit=true;
        }
        for(int j=1;j<=i;j++){
            if(abs(arr[i-j]-arr[i])==j)
                hit=true;
        }
    }
    return !hit;
}

void n_queens(int* arr, int start, int end, int len){
    int i;
    if (start == end && test_queens(arr, len)) { 
  	    for (i = 0; i <= end; i++) 
       	    cout << arr[i] << " ";
     	cout << endl;
    }
    else { 
        for (i = start; i <= end; i++){
  	 	    std::swap(arr[start], arr[i]);
  	 	    n_queens(arr, start + 1, end, len);
  	 	    std::swap(arr[start], arr[i]);
        }
  	}	
}

void hanoi_recursive(Stack<char> pegs[3], int disks, int source, int dest, int temp){
	if (disks >= 1) {
		hanoi_recursive(pegs, disks - 1, source, temp, dest);
        cout << "Disk "<< pegs[source].peek() << " moved from disk "<< source << " to disk "<<dest <<endl;
		pegs[dest].push(pegs[source].pop());
		hanoi_recursive(pegs, disks - 1, temp, dest, source);
	}
}

bool find_path_recursive(char maze[MAZE_VER_SIZE][MAZE_HOR_SIZE], int cur_y, int cur_x, int exit_y, int exit_x, int camefrom) {	
	maze[cur_y][cur_x] = GONE;

	if (cur_x == exit_x && cur_y == exit_y)
		return true;

	//print_maze(maze);	

	if ( cur_x > 0 && maze[cur_y][cur_x - 1] != WALL && camefrom != LEFT ) 
		if ( find_path_recursive(maze, cur_y, cur_x - 1, exit_y, exit_x, RIGHT) ) 
			return true;

	if ( cur_y < MAZE_VER_SIZE-1 && maze[cur_y + 1][cur_x] != WALL && camefrom != DOWN ) 
		if ( find_path_recursive(maze, cur_y + 1, cur_x, exit_y, exit_x, UP) ) 
			return true;

	if ( cur_y > 0 && maze[cur_y - 1][cur_x] != WALL && camefrom != UP ) 
		if ( find_path_recursive(maze, cur_y - 1, cur_x, exit_y, exit_x, DOWN)) 
			return true;

	if ( cur_x < MAZE_HOR_SIZE-1 && maze[cur_y][cur_x + 1] != WALL && camefrom != RIGHT) 
		if ( find_path_recursive(maze, cur_y, cur_x + 1, exit_y, exit_x, LEFT) ) 	
			return true;

	maze[cur_y][cur_x] = PATH; // delete incorrect paths
	//print_maze(maze); // display the return from the incorrect paths as well

	return false;
}

void print_maze(char maze[MAZE_VER_SIZE][MAZE_HOR_SIZE]){
    for (int i = 0; i < MAZE_VER_SIZE; i++) {
        for (int j = 0; j < MAZE_HOR_SIZE; j++)
            cout << maze[i][j];
        cout << endl;
    }
    cout << endl << endl;
}