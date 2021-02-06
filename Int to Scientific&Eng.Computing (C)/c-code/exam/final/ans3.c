#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void read_matrix_text(FILE *fptr, int **matrix, int row, int col);
void write_bin(FILE *fptr, int **matrix, int row, int col);
void print_matrix(int **matrix, int row, int col);
void read_bin(FILE *fptr, int **matrix, int row, int col);
#define SIZE 10

typedef struct val{
    unsigned int row;
    unsigned int col;
    int val;
}Val;

int main()
{
    int row;
    int col;
    FILE *fptr = NULL;
    if ((fptr = fopen("file.txt", "r")) == NULL)
    {
        puts("Can not open the file");
        return EXIT_FAILURE;
    }
    else{
        fscanf(fptr, "%d%d", &row, &col);
        int **matrix = (int **) malloc(sizeof(int *) * row);
        for (int i = 0; i < SIZE; i++)
        {
            matrix[i] = (int *) malloc(sizeof(int) * col);
        }
        //call funcs
        read_matrix_text(fptr, matrix, row, col);
        print_matrix(matrix, row, col);
        fclose(fptr);



        fptr = NULL;
        if ((fptr = fopen("file_b.dat", "w")) == NULL)
        {
            puts("Can not open the bin file");
            return EXIT_FAILURE;
        }
        else
        {
            write_bin(fptr, matrix, row, col);
            fclose(fptr);
        }
        fptr = NULL;
        if ((fptr = fopen("file_b.dat", "r")) == NULL)
        {
            puts("Can not open the bin file for read");
            return EXIT_FAILURE;
        }
        else
        {
            int **matrix2 = (int **) malloc(sizeof(int *) * row);
            for (int i = 0; i < SIZE; i++)
            {
                matrix2[i] = (int *) malloc(sizeof(int) * col);
            }
            puts("prints bin");
            read_bin(fptr, matrix2, row, col);
        
            for (int i = 0; i < row; i++)
            {
                free(matrix2[i]);
            }
            free(matrix2);
            fclose(fptr);
        }
        
        
        
        for (int i = 0; i < row; i++)
        {
            free(matrix[i]);
        }
        free(matrix);
    }

    return 0;
}

void read_matrix_text(FILE *fptr, int **matrix, int row, int col)
{
    
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            fscanf(fptr, "%d", &matrix[i][j]);
        }
    }
}
void print_matrix(int **matrix, int row, int col)
{
    
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void write_bin(FILE *fptr, int **matrix, int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {   
            Val val1;
            if (matrix[i][j] != 0) {
                val1.row = i;
                val1.col = j;
                val1.val = matrix[i][j];
                fwrite(&val1, sizeof(Val), 1, fptr);
            } 
        }
    }
}

void read_bin(FILE *fptr, int **matrix, int row, int col)
{   
    Val val1;
    while(fread(&val1, sizeof(Val), 1, fptr) != 0)
    {   
        matrix[val1.row][val1.col] = val1.val;
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {   
            printf("%d ", matrix[i][j]);
        }
            printf("\n");
    }
}
