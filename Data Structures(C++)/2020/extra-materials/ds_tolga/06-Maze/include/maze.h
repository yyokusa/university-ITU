#pragma once

struct Position{
	int x;
	int y;
	int right;
	int left;
	int down;
	int up;	
	int camefrom;
};

#define RIGHT   1
#define LEFT    2
#define UP      3
#define DOWN    4
#define MAZE_HOR_SIZE    8
#define MAZE_VER_SIZE    8

void print_maze(char[MAZE_HOR_SIZE][MAZE_VER_SIZE]);
void reset_possible_directions(Position&);
void check_possible_move(Position&, char [MAZE_HOR_SIZE][MAZE_VER_SIZE]);
bool move_to(Position&, Position&);
bool reached_exit(Position, Position);
bool made_choice(Position);