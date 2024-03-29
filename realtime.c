#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "realtime.h"
#include "sorted_job_list.h"



void FP(scheduling *CPU, int maxsched, int thread)
{
    int *array;
    array = malloc(maxsched * sizeof(int));
    if (array ==NULL)
    {
        perror("Memoire non allouee");
        exit(1);
    }

    int x;
    for(int i= 0; i< maxsched; i++)
    {
        array[i]= CPU[i].C;
    }

    for(int task = 1; task<= maxsched ; task++)
    {
        for(x = 0; x < thread ; x++)
        {
            if(array[x] != 0)
            {
                printf(" %d |", x+1);
                array[x]--;
                break;
            }
        }
        if (x == thread)
		{
			printf(" 0 |");
		}
		for(int i = 0; i < thread; i++)
		{
			if(task % CPU[i].T == 0)
			{
				array[i] = CPU[i].C;
			}
		}
	}
	printf("\n");
	free(array);
    }
    

int EDF(SortedJobList *job_list, int thread, scheduling *CPU) {
    int i = 1;
    Job *job;
    SortedJobList joblist = create_empty_list();
    float U=0.0, D=0.0, W=0.0;

    for (job = *job_list; job != NULL; job = job->next)
    {
        add_job(&joblist, job->id, job-> rc, job->d);
    }

    compute_parameters(CPU, thread, &U, &D, &W); // Ajout de l'appel à compute_parameters

    if (is_schedulable(CPU, thread, &U, &D, &W))
    {
        printf("Le système est faisable en EDF.\n");
    }
    else
    {
        printf("Le système n'est pas faisable en EDF.\n");
        return 1;
    }

    printf("Charge CPU (U) : %.2f\n", U);
    printf("Période d'occupation (B) : %.2f\n", (1.0 - U) * D);
    printf("Nombre d'instances : %d\n", thread);

    while (i <= thread)
    {
        for (job = *job_list; job != NULL; job = job->next)
        {
            if (i % job->d == 0)
            {
                add_job(&joblist, job->id, job-> rc, job->d + i);
            }
        }
        printf("%d", schedule_first(&joblist));
        i++;
    }

    float busy_period = W + ((1.0 - U) * D);
    printf("busy period : : %.2f\n", busy_period);

    for (int i = 0; i < thread; i++) {
        float response_time = CPU[i].C + (float)(int)(busy_period / CPU[i].T) * CPU[i].C;
        printf("Busy period for the task %d : %.2f\n", i + 1, response_time);
    }

    printf("Response time in worst case : %.2f\n", D + W);

    free(CPU);
}

// En cours
void compute_parameters(scheduling *CPU, int thread, float *U, float *D, float *W) {
    float sum_U = 0.0;
    float max_D = 0.0;
    float max_W = 0.0;

    for (int i = 0; i < thread-1; i++) {
        printf("%d \n", thread);
        printf("%d \n", CPU[i].T);
        if (CPU[i].T == 0) {
        printf("Erreur: La période (T) pour la tâche %d est égale à zéro.\n", i);
        exit(0);
        }

        float u = (float)CPU[i].C / (float)CPU[i].T;
        sum_U += u;

        if (CPU[i].D > max_D) {
            max_D = (float)CPU[i].D;
        }

        float w = (float)CPU[i].C / (float)CPU[i].T;
        if (w > max_W) {
            max_W = w;
        }
    }

    *U = sum_U;
    *D = max_D;
    *W = max_W;
}

int is_schedulable(scheduling *CPU, int thread, float *U, float *D, float *W) {
        printf("Charge CPU (U) : %f\n", *U);
    printf("Période d'occupation maximale (D) : %f\n", *D);
    printf("Taux d'utilisation maximale (W) : %f\n", *W);

printf("U = %.2f, D = %.2f, W = %.2f\n", *U, *D, *W);
float B = (1.0 - *U) * *D;
float busy_period = *W + B;
printf("B = %.2f, busy_period = %.2f\n", B, busy_period);

   printf("Période d'occupation (B) : %f\n", B);
    printf("Période chargée (busy_period) : %f\n", busy_period);

    for (int i = 0; i < thread; i++) {
        float response_time = CPU[i].C + (busy_period / CPU[i].T) * CPU[i].C;
        printf("Tâche %d: Temps de réponse = %.2f\n", i + 1, response_time);
        if (response_time > CPU[i].D) {
            printf("Tâche %d non faisable en EDF : Temps de réponse (%.2f) > Deadline (%d)\n", i + 1, response_time, CPU[i].D);
            return 0;
        }
    }

    if (*U > 1) {
        printf("Non faisable en EDF : Utilisation totale U (%.2f) > 1\n", *U);
        return 0;
    }

    printf("Faisable en EDF\n");
    return 1;
}

