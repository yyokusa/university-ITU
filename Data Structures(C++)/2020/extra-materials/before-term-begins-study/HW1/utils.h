/* @Author
 * Student Name: Yasin Abdulkadir Yokus
 * Student ID : 150190739
 * Date: <date>
 */
#ifndef UTILS_H // include guard
#define UTILS_H

#include <iostream>
#include <cstdio> // it would not portable if we were to rely on <iostream> to include this automatically

#define ROWS 15
#define COLS 15
#define SEARCHED_WORDS_SIZE 10

struct searchedWord {
    int id;
    char* word;
    int wordLength;
};

struct vSearchRes {
    int colStart;
    int colEnd;
    int row;
};

struct hSearchRes {
    int rowStart;
    int rowEnd;
    int col;
};

struct dSearchRes {
    int rowStart;
    int rowEnd;
    int colStart;
    int colEnd;
};

bool verticalSearch(char**, searchedWord*, vSearchRes*);
bool horizontalSearch(char**, searchedWord*, hSearchRes*);
bool diagonalSearch(char**, searchedWord*, dSearchRes*);
void searchWords(char**, searchedWord*, int);
void emptyPuzzleMatrix(char**);
void writeEmptiedPuzzleIntoFile(FILE*, char**);
void readPuzzleIntoArray(FILE*, char**);
int readSearchedWords(FILE*, searchedWord*);
char** createDynArr();
void deleteDynSWAWords(searchedWord*, int);
void deleteDynArr(char**);
void printSearchedWords(searchedWord*, int);
void printPuzzle(char**);

#endif