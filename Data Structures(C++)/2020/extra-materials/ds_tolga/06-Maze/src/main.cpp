#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "maze.h"
using namespace std;

char maze[MAZE_HOR_SIZE][MAZE_VER_SIZE] = {{'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'},
										   {' ', ' ', 'x', 'x', 'x', ' ', ' ', ' '},
										   {'x', ' ', 'x', 'x', 'x', ' ', 'x', 'x'},
										   {'x', ' ', ' ', ' ', ' ', ' ', ' ', 'x'},
										   {'x', ' ', 'x', ' ', 'x', 'x', ' ', 'x'},
										   {'x', ' ', 'x', 'x', ' ', 'x', ' ', 'x'},
										   {'x', ' ', ' ', 'x', ' ', ' ', ' ', 'x'},
										   {'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'}};

int main()
{
	Stack<Position> s;
	s.create();
	Position entrance = {0, 1, 0, 0, 0, 0, 0};
	Position exit = {7, 1, 0, 0, 0, 0, 0};
	Position p = entrance;
	Position past;
	p.camefrom = LEFT;
	print_maze(maze);
	bool goback = false;
	bool moved = true;
	
	while (!reached_exit(p, exit))
	{
		maze[p.y][p.x] = 'o';
		print_maze(maze);
		getchar();
		
		if (!goback){ 
			reset_possible_directions(p);
			check_possible_move(p, maze);
		}
		else goback = false;

		past = p;
		moved = move_to(p, past);

		if (!reached_exit(p, exit) && made_choice(past))
			s.push(past);
			
		if (!reached_exit(p, exit) && !moved && !s.isempty()){
			p = s.pop();
			goback = true;
		}
	} 

	maze[p.y][p.x] = 'o';
	print_maze(maze);
	cout << "PATH found" << endl;
	s.close();

	getchar();
	return EXIT_SUCCESS;
}
