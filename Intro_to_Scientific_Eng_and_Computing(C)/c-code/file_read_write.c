#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct
{
    char name[30];
    int id;
    int exams[3];
    int hws[3];
    char letter_grade;
} Student;

void write_into_binary_file(FILE *fptr, Student *student);
int read_from_binary_file(FILE *fptr, Student *student);
void write_into_text_file(FILE *fptr, Student *student);
int read_from_text_file(FILE *fptr, Student *student);

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        printf("not enough argumants");
        return EXIT_FAILURE;
    }
    FILE *read_text_ptr = NULL;
    FILE *write_bin_ptr = NULL;
    FILE *read_bin_ptr = NULL;
    FILE *write_text_ptr = NULL;
    Student student;
    if((read_text_ptr = fopen(argv[1], "r")) == NULL)
    {
        fprintf(stdout, "can not open text file for reading");
        return EXIT_FAILURE;
    }
    if((write_bin_ptr = fopen(argv[2], "wb")) == NULL)
    {
        fprintf(stdout, "can not open binary file for writing");
        return EXIT_FAILURE;
    }
    while (read_from_text_file(read_text_ptr, &student) > 0)
    {
        puts("entered 1");
        write_into_binary_file(write_bin_ptr, &student);
    }
    fclose(read_text_ptr);
    fclose(write_bin_ptr);
    
    if((read_bin_ptr = fopen(argv[2], "rb")) == NULL)
    {
        fprintf(stdout, "can not open binary file for reading");
        return EXIT_FAILURE;
    }
    if((write_text_ptr = fopen(argv[3], "w")) == NULL)
    {
        fprintf(stdout, "can not open text file for writing");
        return EXIT_FAILURE;
    }
    
    while (read_from_binary_file(read_bin_ptr, &student) > 0)
    {
        puts("entered 2");
        write_into_text_file(write_text_ptr, &student);
    }
    fclose(read_bin_ptr);
    fclose(write_text_ptr);

    return EXIT_SUCCESS;
}

int read_from_text_file(FILE *fptr, Student *student)
{
    return (fscanf(fptr, "%s %d %d %d %d %d %d %d %c", (
                                        student->name),
                                        &(student->id), 
                                        &((student->exams)[0]),
                                        &((student->exams)[1]),
                                        &((student->exams)[2]),
                                        &((student->hws)[0]),
                                        &((student->hws)[1]),
                                        &((student->hws)[2]),
                                        &(student->letter_grade)
                                        ));
}

void write_into_text_file(FILE *fptr, Student *student)
{
    fprintf(fptr, "%s %d %d %d %d %d %d %d %c\n", (
                                        student->name),
                                        (student->id), 
                                        (student->exams)[0],
                                        (student->exams)[1],
                                        (student->exams)[2],
                                        (student->hws)[0],
                                        (student->hws)[1],
                                        (student->hws)[2],
                                        (student->letter_grade)
                                        );
}

int read_from_binary_file(FILE *fptr, Student *student)
{
    return (fread(student, sizeof(Student), 1, fptr));
}

void write_into_binary_file(FILE *fptr, Student *student)
{
    fwrite(student, sizeof(Student), 1, fptr);
}