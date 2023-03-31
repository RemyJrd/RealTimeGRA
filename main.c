#include <stdlib.h>
#include <stdio.h>
#include "realtime.h"
#include "sorted_job_list.h"

//TODO: Partie 2:
// charge DONE
// condition
// busy period
// revoir ce qui as été fait en TP2 par mail
// gamma, lambda, 
// conditions nécessaire et suffisante
// puis calcul beta
// calcul busy period premiere racine positive wt... itération
// sup h(T)/t calcul
// ---
// TD 2 Analyse edf poussée
// basé sur prédicat (non temQps réponse)
// calcul aplha(charge)  gamma plus petit que 1, alors jeu de charge faisable si on peux pas conclure, alors beta, calcul de lambda calcul de h(t)/t point discontiune, sur les échéances de taches (travail avec modulo)
// dans file 2.txt 

int main(int argc, char** argv) {

    const char* filename = argv[1];
    const char* algorithm = argv[2];
    int maxsched = atoi(argv[3]);
    scheduling *CPU;

    printf("filename: %s \n", filename);
    printf("Choosen Algorithm: %s \n", algorithm);
    printf("Max Schedulling: %d \n", maxsched);

    // Filename and Schedulling management
    int thread;
    FILE * file;
    file = fopen(filename, "r");
    if(file != NULL)
    {
        printf("Fichier bien ouvert");
        fscanf(file, "%d", &thread);
        printf("Nombre de thread: %d \n", thread);
        CPU = malloc(sizeof(scheduling) * thread);
        printf("Le fichier ouvert se compose de : \n");
        for (int i = 0; i < thread; i++) 
        {
            fscanf(file, "%d %d %d", &CPU[i].C, &CPU[i].D, &CPU[i].T);
            printf("Thread n°%d: %d %d %d \n", i+1, CPU[i].C, CPU[i].D, CPU[i].T);
        }
    }
    else
    {
        printf("Ouverture impossible du fichier %s", filename);
        exit(1);
    }

    // Algorithm management
    //TODO: Change condition
    if (strcmp(algorithm, "FP") == 0) 
    {
        
        SortedJobList list = create_empty_list();
        for (int i = 0; i< thread; i++)
        {
            add_job(&list, (i + 1), CPU[i].C, CPU[i].D);
        }
        printf("Voici le tableau en FP : \n");
        EDF(&list, maxsched);
        free_list(&list);
    } 
    else if (strcmp(algorithm, "EDF") == 0)
    {
        double load = calculate_load(CPU, thread);
        printf("System Load: %lf \n", load);
        printf("Voici le tableau en EDF : \n");
        SortedJobList list = create_empty_list();
        for (int i = 0; i < thread; i++) 
        {
            add_job(&list, (i + 1), CPU[i].C, CPU[i].D);
        }
        EDF(&list, maxsched);
        free_list(&list);
    } 
    else 
    {
        printf("Erreur: Algorithme non reconnu");
        return 1;
    }
free(CPU);
return 0;
}
