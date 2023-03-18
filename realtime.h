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
void EDF(SortedJobList *job_list, int t);
double calculate_load(scheduling* CPU, int thread);

#endif
