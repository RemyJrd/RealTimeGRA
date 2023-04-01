#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "realtime.h"
#include "sorted_job_list.h"

//TODO: Partie 2:
// charge 
// condition
// busy periodgrd
// revoir ce qui as été fait en TP2 par mail
// gamma, lambda, frdgrdghdrghdghdrtgr
// conditions nécessaire et suffisante
// puis calcul beta
// calcul busy period premiere racine positive wt... itération
// sup h(T)/t calcul
// ---
// TD 2 Analyse edf poussée
// basé sur prédicat (non temps réponse)
// calcul aplha(charge)  gamma plus petit que 1, alors jeu de charge faisable si on peux pas conclure, alors beta, calcul de lambda calcul de h(t)/t point discontiune, sur les échéances de taches (travail avec modulo)


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
        printf("Voici le tableau en EDF : \n");
        EDF(&list, maxsched);
        free_list(&list);
    } 
    else if (strcmp(algorithm, "EDF"))
    {
        printf("Voici le tableau en FP : \n");
        FP(CPU, maxsched, thread);
    } 
    else 
    {
        printf("Erreur: Algorithme non reconnu");
        return 1;
    }
return 0;
}
