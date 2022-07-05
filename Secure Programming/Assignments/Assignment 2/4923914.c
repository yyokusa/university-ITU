#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void processFile(const char *path) {
    printf("%s", "Process file executes\n");  // modified
    char sampleCommandToExecute[100] = {"ls -la "};
    strcat(sampleCommandToExecute, path);
    printf("sampleCommandToExecute: %s\n", sampleCommandToExecute); // new
    int status = system(sampleCommandToExecute);
    return;
}

void main(int argc, char *argv[]) {
    const char *safepath = "/home";
    const size_t spl = strlen(safepath); // modified
    char *fn = argv[1];
    char inputPath[spl]; // new line - modified
    strncpy(inputPath, fn, spl); // new line - modified

    
    if (!strncmp(inputPath, safepath, spl)) { // modified
        processFile(inputPath); // modified   
    }
    else {
        printf("Path specified is not valid!\n");
        return;
    }
    return;
}

