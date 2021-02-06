/* @Author
 * Student Name: Yasin Abdulkadir Yokus
 * Student ID : 150190739
 * Date: <date>
 */

/*
    // write many tests
    // TODO: sort search words for priority order 
    Ask how many header etc. they want
    Ask if it is ok to use dynamically allocated array like this ( *(*(ptr+i)+j) usage)
    Ask priority thing

    print statementlar icin structlara direction eklenmeli
*/



#include "utils.h"

#include <iostream>
#include <cstdio> 
#include <string.h> // <cstring> // strcmp, strcpy

using namespace std;

int main(int argc, char const *argv[])
{
    // allocate memory
    // it would give better performance to use new arr[i*colNum + j] syntax
    // consecutive memory blocks means better performance in this case
    char** puzzleArray = createDynArr();
    if (puzzleArray == NULL) {
        cout << "Could not allocate memory!" << endl;
    } else {
        cout << "Allocation is succesfull" << endl;
    }

    // read puzzle into dynamically allocated memory
    FILE* puzzleFile = NULL;
    if (NULL != (puzzleFile = fopen("puzzle.txt", "r"))) {
        readPuzzleIntoArray(puzzleFile, puzzleArray);
        fclose(puzzleFile);
    }
    
    // read the searched words file into arr
    searchedWord searchedWordsArr[SEARCHED_WORDS_SIZE];
    int swa_size = 0;
    FILE* searchedWordsFile = NULL;
    if (NULL != (searchedWordsFile = fopen("searchedwords.txt", "r"))) {
        swa_size = readSearchedWords(searchedWordsFile, searchedWordsArr);
        fclose(searchedWordsFile);
    }

    // search words, also writing found words into foundWordsInfo.txt file
    searchWords(puzzleArray, searchedWordsArr, swa_size);
    emptyPuzzleMatrix(puzzleArray);
    // free memory
    deleteDynSWAWords(searchedWordsArr, swa_size);
    // free memory
    deleteDynArr(puzzleArray);

    return 0;
}



// each row is searched from right to left and vice versa
// naive pattern search
bool verticalSearch(char** puzzleArray, searchedWord* sWord, vSearchRes* res) {
    int id = sWord->id;
    int wordlen = sWord->wordLength;
    char word[wordlen];
    strcpy(word, sWord->word);

    int curr = 0;
    cout << "Searching for : "<<word << " in vertical direction."<< endl;
    char** ptr = puzzleArray;

    // left to right
    for (size_t i = 0; i < ROWS; i++)
    {
        for (size_t j = 0; j < COLS; j++)
        {
            if (*(*(ptr + i) + j) == word[curr]) {
                curr += 1;
                if (curr == wordlen) {
                    res->colStart = j - wordlen + 1;
                    res->colEnd = j;
                    res->row = i;
                    return true;
                }
            } else {
                j = j - curr;
                curr = 0;
            }
        }
    }
    // right to left
    for (int i = ROWS - 1; i >= 0; i--)
    {
        for (int j = COLS - 1; j >= 0; j--)
        {
            if (*(*(ptr + i) + j) == word[curr]) {
                curr += 1;
                if (curr == wordlen) {
                    res->colStart = j;
                    res->colEnd = j + wordlen - 1;
                    res->row = i;
                    return true;
                }
            } else {
                j = j + curr;
                curr = 0;
            }
        }
        
    }
    return false;
}

// each column is searched from up to down and vice versa
bool horizontalSearch(char** puzzleArray, searchedWord* sWord, hSearchRes* res) {
    int id = sWord->id;
    int wordlen = sWord->wordLength;
    char word[wordlen];
    strcpy(word, sWord->word);

    int curr = 0;
    cout << "Searching for : "<< word << " in horizontal direction."<< endl;
    char** ptr = puzzleArray;

    for (size_t i = 0; i < COLS; i++)
    {
        for (size_t j = 0; j < ROWS; j++)
        {
            if (*(*(ptr + j) + i) == word[curr]) {
                curr += 1;
                if (curr == wordlen) {
                    res->rowStart = j - wordlen + 1;
                    res->rowEnd = j;
                    res->col = i;
                    return true;
                }
            } else {
                j = j - curr;
                curr = 0;
            }
        }
    }
    for (int i = COLS - 1; i >= 0; i--)
    {
        for (int j = ROWS - 1; j >= 0; j--)
        {
            if (*(*(ptr + j) + i) == word[curr]) {
                curr += 1;
                if (curr == wordlen) {
                    res->rowStart = j + wordlen - 1;
                    res->rowEnd = j;
                    res->col = i;
                    return true;
                }
            } else {
                j = j + curr;
                curr = 0;
            }
        }
    }
    return false;
}

bool diagonalSearch(char** puzzleArray, searchedWord* sWord, dSearchRes* res) {
    int id = sWord->id;
    int wordlen = sWord->wordLength;
    char word[wordlen];
    strcpy(word, sWord->word);

    int curr = 0;
    cout << "Searching for : "<< word << " in diagonal direction." << endl;
    char** ptr = puzzleArray;
    
    //OK
    // 1st possibility: from first-col to right bottom
    for (size_t i = 0; i < ROWS - (wordlen - 1); i++)
    {
        int rowEnd = ROWS;
        int colEnd = COLS;
        int ix = i;
        int iy = 0;
        while (ix < rowEnd && iy < colEnd) {
            if (*(*(ptr + ix) + iy) == word[curr]) {
                curr++;
                if (curr == wordlen) {
                    res->colStart = iy - curr + 1;
                    res->colEnd = iy;
                    res->rowStart = ix - curr + 1;
                    res->rowEnd = ix;
                    return true;
                }
            } else {
                ix = ix - curr;
                iy = iy - curr;
                curr = 0;
            }
            ix++;
            iy++;
        }
        curr = 0;
    }

    //OK
    // 2nd possibility: from first-row to right bottom
    for (size_t i = 1; i < COLS - (wordlen - 1); i++)
    {
        int rowEnd = ROWS - 1;
        int colEnd = COLS;
        int ix = 0;
        int iy = i;
        while (ix < rowEnd && iy < colEnd) {
            if (*(*(ptr + ix) + iy) == word[curr]) {
                curr++;
                if (curr == wordlen) {
                    res->colStart = iy - curr + 1;
                    res->colEnd = iy;
                    res->rowStart = ix - curr + 1;
                    res->rowEnd = ix;
                    return true;
                }
            } else {
                ix = ix - curr;
                iy = iy - curr;
                curr = 0;
            }
            ix++;
            iy++;
        }
        curr = 0;
    }

    // OK
    // 3rd possibility: from last-col to left top
    for (size_t i = ROWS - 1; i >= wordlen - 1; i--)
    {
        int rowEnd = -1;
        int colEnd = -1;
        int ix = i;
        int iy = COLS - 1;
        while (ix > rowEnd && iy > colEnd) {
            if (*(*(ptr + ix) + iy) == word[curr]) {
                curr++;
                if (curr == wordlen) {
                    res->colStart = iy + curr - 1;
                    res->colEnd = iy;
                    res->rowStart = ix + curr - 1;
                    res->rowEnd = ix;
                    return true;
                }
            } else {
                ix = ix + curr;
                iy = iy + curr;
                curr = 0;
            }
            ix--;
            iy--;
        }
        curr = 0;
    }

    // OK
    // 4th possibility: from last-row to left top
    for (size_t i = COLS - 2; i >= wordlen - 1; i--)
    {
        int rowEnd = -1;
        int colEnd = -1;
        int ix = ROWS - 1;
        int iy = i;
        while (ix > rowEnd && iy > colEnd) {
            if (*(*(ptr + ix) + iy) == word[curr]) {
                curr++;
                if (curr == wordlen) {
                    res->colStart = iy + curr - 1;
                    res->colEnd = iy;
                    res->rowStart = ix + curr - 1;
                    res->rowEnd = ix;
                    return true;
                }
            } else {
                ix = ix + curr;
                iy = iy + curr;
                curr = 0;
            }
            ix--;
            iy--;
        }
        curr = 0;
    }
    
    // 5th
    for (size_t i = COLS - 1; i >= (wordlen - 1); i--)
    {
        int rowEnd = ROWS;
        int colEnd = -1;
        int ix = 0;
        int iy = i;
        while (ix < rowEnd && iy > colEnd) {
            if (*(*(ptr + ix) + iy) == word[curr]) {
                curr++;
                if (curr == wordlen) {
                    res->colStart = iy + curr - 1;
                    res->colEnd = iy;
                    res->rowStart = ix - curr + 1;
                    res->rowEnd = ix;
                    return true;
                }
            } else {
                ix = ix - curr;
                iy = iy + curr;
                curr = 0;
            }
            ix++;
            iy--;
        }
        curr = 0;
    }
    
    // 6th
    for (size_t i = 1; i <= ROWS - (wordlen - 1); i++)
    {
        int rowEnd = ROWS;
        int colEnd = 0;
        int ix = i;
        int iy = COLS - 1;
        while (ix < rowEnd && iy > colEnd) {
            if (*(*(ptr + ix) + iy) == word[curr]) {
                curr++;
                if (curr == wordlen) {
                    res->colStart = iy + curr - 1;
                    res->colEnd = iy;
                    res->rowStart = ix - curr + 1;
                    res->rowEnd = ix;
                    return true;
                }
            } else {
                ix = ix - curr;
                iy = iy + curr;
                curr = 0;
            }
            ix++;
            iy--;
        }
        curr = 0;
    }

    // OK
    //7th
    for (size_t i = ROWS - 1; i >= wordlen - 1; i--)
    {
        int rowEnd = -1;
        int colEnd = COLS;
        int ix = i;
        int iy = 0;
        while (ix > rowEnd && iy < colEnd) {
            if (*(*(ptr + ix) + iy) == word[curr]) {
                curr++;
                if (curr == wordlen) {
                    res->colStart = iy - curr + 1;
                    res->colEnd = iy;
                    res->rowStart = ix + curr - 1;
                    res->rowEnd = ix;
                    return true;
                }
            } else {
                ix = ix + curr;
                iy = iy - curr;
                curr = 0;
            }
            ix--;
            iy++;
        }
        curr = 0;
    }
    
    // OK
    //8th
    for (size_t i = 1; i <= COLS - 1; i++)
    {
        int rowEnd = 0;
        int colEnd = COLS;
        int ix = ROWS - 1;
        int iy = i;
        while (ix > rowEnd && iy < colEnd) {
            if (*(*(ptr + ix) + iy) == word[curr]) {
                curr++;
                if (curr == wordlen) {
                    res->colStart = iy - curr + 1;
                    res->colEnd = iy;
                    res->rowStart = ix + curr - 1;
                    res->rowEnd = ix;
                    return true;
                }
            } else {
                ix = ix + curr;
                iy = iy - curr;
                curr = 0;
            }
            ix--;
            iy++;
        }
        // What happens when the last character of the previous 
        // round is the same as wanted letter --> PROBLEM
        // So, we need to reset the curr counter
        curr = 0;
    }
    return false;
}

// Search words then write found words into foundWordsInfo file
void searchWords(char** puzzleArray, searchedWord* searchedWordsArr, int swa_size){
    FILE* foundWordsFile = NULL;
    if ((foundWordsFile = fopen("foundWordsInfo.txt", "w")) != NULL) {
        for (size_t i = 0; i < swa_size; i++)
        {
            vSearchRes vRes;
            hSearchRes hRes;
            dSearchRes dRes;
            int direction = 1;
            searchedWord* word = searchedWordsArr + i;
            
            bool wordFound = verticalSearch(puzzleArray, word, &vRes);
            if (wordFound){
                direction = 1;
            } else if (!wordFound) {
                wordFound = horizontalSearch(puzzleArray, word, &hRes);
                if (wordFound){
                    direction = 2;
                }
            }
            if (!wordFound) {
                wordFound = diagonalSearch(puzzleArray, word, &dRes);
                if (wordFound){
                    direction = 3;
                }
            }

            if (wordFound) 
            {
                cout << "Found the word! " << "Writing to file..." << endl;
                switch (direction)
                {
                case 1:
                {
                    fprintf(foundWordsFile, "%-12s\t%-12s\t[%d][%d] - [%d][%d]\n",
                            word->word, "VERTICAL", vRes.row, vRes.colStart, vRes.row, vRes.colEnd);
                    break;
                }
                case 2:
                {
                    fprintf(foundWordsFile, "%-12s\t%-12s\t[%d][%d] - [%d][%d]\n",
                            word->word, "HORIZONTAL", hRes.rowStart, hRes.col, hRes.rowEnd, hRes.col);
                    break;
                }
                case 3:
                {
                    fprintf(foundWordsFile, "%-12s\t%-12s\t[%d][%d] - [%d][%d]\n",
                            word->word, "DIAGONAL", dRes.rowStart, dRes.colStart, dRes.rowEnd, dRes.colEnd);
                    break;
                }
                default:
                    fprintf(foundWordsFile, "Something went wrong with this one!\n");
                    break;
                }
            } 
            else {
                cout << "Could not find the word! " << word << endl;
            }
        }
        fclose(foundWordsFile);
    } else {
        cout << "Could not open the file to write found words(if any)." << endl;
    }
}

void emptyPuzzleMatrix(char** puzzleArray) {
    char** ptr = puzzleArray;
    FILE* emptyPuzzleFile = NULL;
    FILE* foundWordsFile = NULL;
    if ((emptyPuzzleFile = fopen("lastVersionPuzzle.txt", "w")) != NULL) {
        if ((foundWordsFile = fopen("foundWordsInfo.txt", "r")) != NULL) {
            int rowStart = 0;
            int colStart = 0;
            int rowEnd = 0;
            int colEnd = 0;
            int scanned = 0;
            char w1[25];
            char w2[25];
            while ((scanned = fscanf(foundWordsFile, "%s\t%s\t[%d][%d] - [%d][%d]\n",
                                    w1, w2, &rowStart, &colStart, &rowEnd, &colEnd)) > 0)
            {
                if (rowStart == rowEnd) {
                    int biggerCol = (colStart < colEnd) ? colEnd : colStart;
                    int smallerCol = (colStart > colEnd) ? colEnd : colStart;
                    for (size_t i = smallerCol; i <= biggerCol; i++)
                        *(*(ptr + rowStart) + i) = ' ';
                } else if (colStart == colEnd) {
                    int biggerRow = (rowStart < rowEnd) ? rowEnd : rowStart;
                    int smallerRow = (rowStart > rowEnd) ? rowEnd : rowStart;
                    for (size_t i = smallerRow; i <= biggerRow; i++)
                        *(*(ptr + i) + colStart) = ' ';
                } else {
                    int mod1 = (rowStart < rowEnd) ? 0 : 1;
                    int mod2 = (colStart < colEnd) ? 0 : 1;
                    
                    if (mod1 == 0 && mod2 == 0) {
                        // right and bottom direction
                        for( int i=rowStart, j=colStart;
                            i <= rowEnd && j <= colEnd;
                            i++, j++)
                            *(*(ptr + i) + j) = ' ';
                    } else if (mod1 == 0 && mod2 == 1) {
                        // left and bottom direction
                        for( int i=rowStart, j=colStart;
                            i <= rowEnd && j >= colEnd;
                            i++, j--)
                            *(*(ptr + i) + j) = ' ';
                    } else if (mod1 == 1 && mod2 == 0) {
                        // right and top direction
                        for( int i=rowStart, j=colStart;
                            i >= rowEnd && j <= colEnd;
                            i--, j++)
                            *(*(ptr + i) + j) = ' ';
                    } else { // (mod1 == 1 && mod2 == 1)
                        // left and top direction
                        for( int i=rowStart, j=colStart;
                            i >= rowEnd && j >= colStart;
                            i--, j--)
                            *(*(ptr + i) + j) = ' ';
                    }
                }
            }
            /* for (size_t i = 0; i < ROWS; i++)
            {
                for (size_t j = 0; j < COLS; j++)
                {
                    cout <<  *(*(ptr + i) + j) << " ";
                }
                cout << endl;
            } */
            writeEmptiedPuzzleIntoFile(emptyPuzzleFile, ptr);
            fclose(foundWordsFile);
        } else {
            cout << "Could not open foundWordsInfo file to read!" << endl;
        }
        fclose(emptyPuzzleFile);
    } else {
        cout << "Could not open lastVPuzzle file to write!" << endl;
    }
}

void writeEmptiedPuzzleIntoFile(FILE* emptyPuzzFile, char** emptiedPuzzArr) {
    char** ptr = emptiedPuzzArr;
    char c = '\0';
    int row = 0;
    int col = 0;

    for (size_t i = 0; i < ROWS; i++)
    {
        for (size_t j = 0; j < COLS; j++)
        {
            fputc(*(*(ptr + i) + j), emptyPuzzFile);
            if (j == COLS - 1)
                continue;
            fputc(' ', emptyPuzzFile);
        }
        if (i == ROWS - 1)
                continue;
        fputc('\n', emptyPuzzFile);
    }
}

char** createDynArr() {
    // initialize 2D dynamic array
    char** puzzArr = new char* [ROWS];
    for (size_t row = 0; row < ROWS; row++)
    {
        puzzArr[row] = new char[COLS];
    }
    return puzzArr;
}

void readPuzzleIntoArray(FILE* puzzleFile, char** puzzleArr) {
    char c = '\0';
    int row = 0;
    int col = 0;
    while ((c = fgetc(puzzleFile)) != EOF && row != 15)
    {
        if (c >= 'A' && c <= 'Z') {
            *(*(puzzleArr + row) + col) = c;
            col++;
            if (col == 15) {
                row += 1;
                col = 0;
            }
        }
    }
}

int readSearchedWords(FILE* searchedWordsFile, searchedWord* searchedWordsArr) {
    int read = 0;
    int index = 0;
    
    int num = 0;
    char word[ROWS + 1];
    while((read = fscanf(searchedWordsFile, "%d %s", &num, word)) >= 0) {
        int word_len = strlen(word);
        
        searchedWordsArr[index].wordLength = word_len;
        searchedWordsArr[index].id = num;
        searchedWordsArr[index].word = new char[ROWS + 1];
        strcpy(searchedWordsArr[index].word, word);
        index++;
    }
    return index;
}

void deleteDynSWAWords(searchedWord* searchedWordsArr, int size) {
    // free allocated memory for searchedWordsArr
    for (size_t i = 0; i < size; i++)
    {
        delete [] searchedWordsArr[i].word;
    }
}

void deleteDynArr(char** puzzArr) {
    // free memory taken for 2D dynamic array
    for (size_t row = 0; row < ROWS; row++)
    {
        delete [] puzzArr[row];
    }
    delete [] puzzArr;
}

void printSearchedWords(searchedWord* searchedWordsArr, int size) {
    for (size_t i = 0; i < size; i++)
    {
        cout << "id: " << searchedWordsArr[i].id << ", word: " << searchedWordsArr[i].word << ", wordlen: " << searchedWordsArr[i].wordLength << endl;
    }
}

void printPuzzle(char** puzzArr) {
    char** ptr = puzzArr;
    for (size_t i = 0; i < ROWS; i++)
    {
        for (size_t j = 0; j < COLS; j++)
        {
            cout << *(*(puzzArr + i) + j) << ' ';
        }
        cout << endl;
    }
}