#include <stdlib.h>
#include <stdio.h>

    //TODO: Verification input

int FP(FILE* file, int maxsched) {

}

int EDF(FILE* file, int maxsched) {

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

    // Algorithm management
    if (strcmp(algorithm, "FP")) {
        printf("Je suis en EDF \n");
        EDF(file, maxsched);
    } 
    else 
    {
        printf("Je suis en FP \n");
        FP(file, maxsched);
    }

    // Max Schedulling management
    int thread;
    fscanf(file, "%d", &thread);
    
    
system("pause");
return 0;
}
