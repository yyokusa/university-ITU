#include "maze.h"

#include <iostream>
using namespace std;

void print_maze(char maze[MAZE_HOR_SIZE][MAZE_VER_SIZE]){
    for (int i = 0; i < MAZE_HOR_SIZE; i++) {
        for (int j = 0; j < MAZE_VER_SIZE; j++)
            cout << maze[i][j];
        cout << endl;
    }
    cout << endl << endl;
}

void reset_possible_directions(Position& p){
			p.right = 0;
			p.left = 0;
			p.down = 0;
			p.up = 0;
}

void check_possible_move(Position& p, char maze[MAZE_HOR_SIZE][MAZE_VER_SIZE]){
	if (p.x < MAZE_HOR_SIZE-1 && maze[p.y][p.x + 1] != 'x')
		p.right = 1; //right
	if (p.x > 0 && maze[p.y][p.x - 1] != 'x')
		p.left = 1; //left
	if (p.y < MAZE_VER_SIZE-1 && maze[p.y + 1][p.x] != 'x')
		p.down = 1; //down
	if (p.y > 0 && maze[p.y - 1][p.x] != 'x')
		p.up = 1; //up
}

bool move_to(Position& p, Position& past){
	if (p.down && p.camefrom != DOWN)
	{
		p.y++;
		p.camefrom = UP;
		past.down = 0;
	}
	else if (p.up && p.camefrom != UP)
	{
		p.y--;
		p.camefrom = DOWN;
		past.up = 0;
	}
	else if (p.left && p.camefrom != LEFT)
	{
		p.x--;
		p.camefrom = RIGHT;
		past.left = 0;
	}
	else if (p.right && p.camefrom != RIGHT)
	{
		p.x++;
		p.camefrom = LEFT;
		past.right = 0;
	}
	else
		return false; 
		
	return true;
}

bool reached_exit(Position p, Position exit){
	return p.x == exit.x && p.y == exit.y;
}

bool made_choice(Position past){
 	return past.down + past.up + past.right + past.left > 1;
}