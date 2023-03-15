#include <stdlib.h>
#include <stdio.h>
#include "functions.c"
#include "functions.h"

    //TODO: Verification input

void FP(FILE* file, int maxsched, int thread) {
    int test;
    //TODO
}

void EDF(FILE* file, int maxsched, int thread) {
    int test;
    //TODO
}

int main(int argc, char** argv) {

    const char* filename = argv[1];
    const char* algorithm = argv[2];
    int maxsched = atoi(argv[3]);

    printf("filename: %s \n", filename);
    printf("Choosen Algorithm: %s \n", algorithm);
    printf("Max Schedulling: %d \n", maxsched);

    // Filename management
    FILE * file;
    file = fopen(filename, "r");

    // Max Schedulling management
    int thread;
    fscanf(file, "%d", &thread);

    // Task preparation
    for (int i = 0; i < thread; i++) {
        
    }

    // Algorithm management
    if (strcmp(algorithm, "FP")) {
        printf("Je suis en EDF \n");
        EDF(file, maxsched, thread);
    } 
    else 
    {
        printf("Je suis en FP \n");
        FP(file, maxsched, thread);
    }

    
    
system("pause");
return 0;
}
