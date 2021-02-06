// compile using gcc -std=c99 -Wall -Werror transaction-processing-program.c -o [output_name]
#include <stdio.h>




//YARIM KALDI

typedef struct{
    char name[20];
    char id[20];
    int  exams[3];
    int  hws[3];
    char  letter_grade;
}Student; 

void write_into_text_file(FILE* file);

int main(int argc, char* argv[]) {
    
    FILE* fptr;
    printf("%d\n", argc);
    printf("%s\n", argv[0]);
    printf("%s\n", argv[argc - 1]);
    if ((fptr = fopen(argv[argc - 1], "r")) == NULL) { // rb+ bak
        puts("Could not open file");
    } //end if
    else {
        write_into_text_file(fptr);
        fclose(fptr);
    } //end while
    return 0;
}

void write_into_text_file(FILE* file){
    FILE* fptr = file;
    FILE* dest_ptr = NULL;
    Student student;
    //students_dst.txt
    if ((dest_ptr = fopen("students_dst.txt", "w")) == NULL) {
        puts("Could not open file");
    }
    else {  
        int a = 9;
        //while(!feof(fptr)) {
        while(a != 0 || a != 9) {
            a = fscanf(fptr, "%s%s%d%d%d%d%d%d%c", student.name, student.id, &student.exams[0], &student.exams[1], &student.exams[2],
             &student.hws[0], &student.hws[1], &student.hws[2], &(student.letter_grade));
            fprintf(fptr, "name: %s, id: %s, exam1: %d, exam2: %d, exam3: %d, hw1: %d, hw2: %d, hw3: %d, grade: %c",  student.name, student.id, student.exams[0], student.exams[1], student.exams[2],
             student.hws[0], student.hws[1], student.hws[2], (student.letter_grade));
        }
        fclose(dest_ptr);
    }
}