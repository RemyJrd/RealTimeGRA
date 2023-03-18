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
                printf("%d", x+1);
                array[x]--;
                break;
            }
        }
        if (x == thread)
		{
			printf("0 ");
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

void EDF(SortedJobList *job_list, int thread) {
    int i = 1;
    Job *job;
    SortedJobList joblist = create_empty_list();
    for (job = *job_list; job != NULL; job = job->next)
    {
        add_job(&joblist, job->id, job-> rc, job->d);
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
}

