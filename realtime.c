#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "realtime.h"
#include "sorted_job_list.h"

double calculate_load(scheduling *CPU, int thread) {
    double load = 0.0;
    for (int i = 0; i < thread; i++) {
        load += (double) CPU[i].C / (double) CPU[i].T;
    }
    return load;
}


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
    //TOD

void EDF(SortedJobList *job_list, int thread, scheduling *CPU) {
    int i = 1;
    Job *job;
    SortedJobList joblist = create_empty_list();
    float U[thread], D[thread], W[thread];

    for (job = *job_list; job != NULL; job = job->next)
    {
        add_job(&joblist, job->id, job-> rc, job->d);
    }

    compute_parameters(CPU, thread, U, D, W); // Ajout de l'appel à compute_parameters

    if (is_schedulable(CPU, thread, U, D, W))
    {
        printf("Le systeme est faisable en EDF.\n");
    }
    else
    {
        printf("Le systeme n'est pas faisable en EDF.\n");
    }

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
<<<<<<< HEAD

   free(CPU);
}

// En cours
void compute_parameters(scheduling *CPU, int thread, float *U, float *D, float *W) {
    float sum_U = 0.0;
    float max_D = 0.0;
    float max_W = 0.0;

    for (int i = 0; i < thread; i++) {
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
float B = (1.0 - *U) * *D;
float busy_period = *W + B;

    for (int i = 0; i < thread; i++) {
        float response_time = CPU[i].C + (float)(int)(busy_period / CPU[i].T) * CPU[i].C;
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
=======
>>>>>>> 48ab77060ef3164b95d45842f5fc4c9c835bab38
}

