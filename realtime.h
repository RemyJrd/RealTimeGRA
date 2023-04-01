#ifndef STRUCT_H
#define STRUCT_H
#include "sorted_job_list.h"
typedef struct scheduling
{
  int C;
  int D;
  int T;
}scheduling;

void FP(scheduling *CPU, int maxsched, int thread);
<<<<<<< HEAD
void EDF(SortedJobList *job_list, int thread, scheduling *CPU);
void compute_parameters(scheduling *CPU, int thread, float *U, float *D, float *W);
int is_schedulable(scheduling *CPU, int thread, float *U, float *D, float *W);
=======
void EDF(SortedJobList *job_list, int t);
double calculate_load(scheduling* CPU, int thread);
>>>>>>> 48ab77060ef3164b95d45842f5fc4c9c835bab38

#endif