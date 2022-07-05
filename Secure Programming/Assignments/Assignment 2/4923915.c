#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void processFile(const char *filename) {
    printf("%s", "Process file executes\n");  // modified
    FILE *filepointer;
    int c;
    filepointer = fopen(filename, "r");

    if (filepointer == NULL) {
        printf("%s", "Could not open the file\n");
        return;    
    }
    
    while ((c = fgetc(filepointer)) != EOF)
        printf("%c", (char)c);

    fclose(filepointer);
    return;
}

void main(int argc, char *argv[]) {
    const char * protectedFiles[] = {"naivepasswordfile.txt", "naivecreditcarddetails.txt"};
    const size_t pf1l = strlen(protectedFiles[0]); // modified
    const size_t pf2l = strlen(protectedFiles[1]); // modified
    char absoluteFilePath1[100]; // modified
    char absoluteFilePath2[100]; // modified
    char absoluteFilePath3[100]; // modified
    realpath(protectedFiles[0], absoluteFilePath1); // modified
    realpath(protectedFiles[1], absoluteFilePath2); // modified

    char *fn = argv[1];
    realpath(fn, absoluteFilePath3); // modified
    if (strncmp(absoluteFilePath3, absoluteFilePath1, pf1l) != 0 && strncmp(absoluteFilePath3, absoluteFilePath2, pf2l) != 0) { // modified
        processFile(absoluteFilePath3); // modified
    }
    else {
        printf("%s", "Access to the file specified is not permitted!\n");
        return;
    }
    return;
}

