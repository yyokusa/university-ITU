#pragma once
#include "stack.h"
#include "directions.h"

int recursive_factorial(int);
int iterative_factorial(int);
int binary_sum(const int*, int, int, int);
void iterative_permutation();
void recursive_permutation(char*, int, int);
void n_queens(int*, int, int, int);
void hanoi_recursive(Stack<char>[3], int, int, int, int);
bool find_path_recursive(char[MAZE_VER_SIZE][MAZE_HOR_SIZE], int, int, int, int, int);
void print_maze(char[MAZE_VER_SIZE][MAZE_HOR_SIZE]);
