#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "realtime.h"
#include "sorted_job_list.h"

int main(int argc, char** argv) {
    const char* filename = argv[1];
    const char* algorithm = argv[2];
    int maxsched = atoi(argv[3]);
    scheduling *CPU;

    printf("filename: %s \n\n", filename);

    printf("Choosen Algorithm: %s \n\n", algorithm);
    printf("Max Schedulling: %d \n\n", maxsched);

    // Filename and Schedulling management
    int thread;
    FILE * file;
    file = fopen(filename, "r");
    if(file != NULL)
    {
        fscanf(file, "%d", &thread);
        printf("There is %d threads in the file, the file is composed of :\n", thread);
        CPU = malloc(sizeof(scheduling) * thread);
        for (int i = 0; i < thread; i++)
        {
            fscanf(file, "%d %d %d", &CPU[i].C, &CPU[i].D, &CPU[i].T);
            printf("Thread %d: %d %d %d \n", i+1, CPU[i].C, CPU[i].D, CPU[i].T);
        }
    }
    else
    {
        printf("Can't opend the file %s \n", filename);
        exit(1);
    }

    // Algorithm management
    //TODO: Change condition
    if (strcmp(algorithm, "FP"))
    {

        SortedJobList list = create_empty_list();
        for (int i = 0; i< thread; i++)
        {
            add_job(&list, (i + 1), CPU[i].C, CPU[i].D);
        }
        printf("\n===========================================================================\n");
        printf("\n Here is the EDF array : \n\n");
        printf("|");
        EDF(&list, maxsched, CPU);
        printf("\n===========================================================================\n");
        free_list(&list);
    }
    else if (strcmp(algorithm, "EDF"))
    {
        printf("\n===========================================================================\n");
        printf("\n Here is the FP array : \n\n");
        printf("|");
        FP(CPU, maxsched, thread);
        printf("\n===========================================================================\n");
    }
    else
    {
        printf("Erreur: Algorithme non reconnu");
        return 1;
    }
free(CPU);
system("pause");
return 0;
}
