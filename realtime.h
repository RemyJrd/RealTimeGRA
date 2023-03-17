#ifndef STRUCT_H
#define STRUCT_H

typedef struct scheduling
{
  int C;
  int D;
  int T;
}scheduling;

void FP(int nbTache, int n, scheduling *systeme);
void EDF(SortedJobList *job_list, int t);

#endif
