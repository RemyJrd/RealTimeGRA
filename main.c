#include <stdlib.h>
#include <stdio.h>
#include "realtime.c"
#include "realtime.h"

//TODO: Partie 2:
// charge 
// condition
// busy period
// revoir ce qui as été fait en TP2 par mail
// gamma, lambda, 
// conditions nécessaire et suffisante
// puis calcul beta
// calcul busy period premiere racine positive wt... itération
// sup h(T)/t calcul

int main(int argc, char** argv) {

    const char* filename = argv[1];
    const char* algorithm = argv[2];
    int maxsched = atoi(argv[3]);

    printf("filename: %s \n", filename);
    printf("Choosen Algorithm: %s \n", algorithm);
    printf("Max Schedulling: %d \n", maxsched);

    // Filename management
    int thread;
    FILE * file;
    file = fopen(filename, "r");
    if(file != NULL)
    {
        fscanf(file, "%d", &thread);

    }
    else
    {
        printf("Ouverture impossible du fichier %s", filename);
        exit(1);
    }

    // Max Schedulling management
    //TODO: S'assurer de la chaine de caractere correcte
    fscanf(file, "%d", &thread);

    // Task preparation
    for (int i = 0; i < thread; i++) {
        
    }

    // Algorithm management
    if (strcmp(algorithm, "FP")) 
    {
        printf("Voici le tableau en EDF : \n");
        EDF(file, maxsched, thread);
    } 
    else if (strcmp(algorithm, "EDF"))
    {
        printf("Voici le tableau en FP : \n");
        FP(file, maxsched, thread);
    } 
    else 
    {
        printf("Erreur: Algorithme non reconnu");
        return 1;
    }

    
    
system("pause");
return 0;
}
