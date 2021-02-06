#include <stdio.h>
#include <stdlib.h>


#define x_size 100
#define y_size 100
const int matrix_1[x_size][y_size];

int main() {
    
    

    return 0;
}


void readMatrix() {
    //FILE* read_ptr;
    FILE* fptr;
    int m_size[2];
    int row;
    int col;
    if ((fptr = fopen("matrix.txt", "r")) == NULL) {
        puts("error opening file");
    } else {
        fread(m_size, sizeof(int), 2, fptr);
        row = m_size[0];    //x
        col = m_size[1];    //y
        rewind(fptr);
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                fread(&matrix_1[i][j], sizeof(int), 1, fptr);
            }
        }
        fclose(fptr);
    }
}
void writeBin() {
    FILE *fptr;
    int m_size[2];
    int row = matrix_1[0][0];
    int col = matrix_1[0][1];
    if ((fptr = fopen("matrix.dat", "wb")) == NULL) {
        puts("error opening file");
    } else {
        fwrite(&matrix_1[0][0], sizeof(int), 2, fptr);
        for (int i = 1; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (matrix_1[i][j] != 0)
                {
                    fwrite(&matrix_1[i][j], sizeof(int), 1, fptr);
                }
            }
        }
        fclose(fptr);
    }
}
void readBin() {
    FILE *fptr;
    int m_size[2];
    int row = matrix_1[0][0];
    int col = matrix_1[0][1];
    if ((fptr = fopen("matrix.dat", "rb")) == NULL) {
        puts("error opening file");
    } else {
        //fwrite(&matrix_1[0][0], sizeof(int), 2, fptr);
        printf("%d %d", matrix_1[0][0], matrix_1[0][1]);
        for (int i = 1; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (matrix_1[i][j] != 0)
                {
                    printf("%d", matrix_1[i][j]);
                }
            }
            printf("\n");
        }
        fclose(fptr);
    }
}