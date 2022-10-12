#include <stdio.h>
#include <stdlib.h>
#include "lineq.h"
#include "nr.h"

void run_mprove(const char *filename);

int main(void)
{
  run_mprove("lineq_dat/lineq1.dat");
  run_mprove("lineq_dat/lineq2.dat");
  run_mprove("lineq_dat/lineq3.dat");
}

void run_mprove(const char *filename)
{
  lineq_t *lineq;
  lineq = init_lineq(filename);

  int *indx;
  float *d;
  indx = (int *)malloc(lineq->cols * sizeof(int)) - 1;
  d = (float *)malloc(sizeof(float));
  float **A = (float **)malloc(lineq->rows * sizeof(float *)) - 1;
  for (int i = 1; i <= lineq->rows; ++i)
    A[i] = (float *)malloc(lineq->cols * sizeof(float)) - 1;
  float *b = (float *)malloc(lineq->cols * sizeof(float)) - 1;

  for (int i = 1; i <= lineq->rows; ++i)
  {
    for (int j = 1; j <= lineq->cols; ++j)
    {
      A[i][j] = lineq->A[i][j];
    }
  }

  for (int i = 1; i <= lineq->cols; ++i)
  {
    lineq->x[i] = lineq->b[i];
    b[i] = lineq->b[i];
  }

  ludcmp(lineq->A, lineq->rows, indx, d);
  lubksb(lineq->A, lineq->rows, indx, lineq->x);
  for (int i = 0; i < 10000; ++i)
    mprove(A, lineq->A, lineq->rows, indx, b, lineq->b);

  printf("mprove: ");
  print_solution(lineq);

  free(b + 1);
  for (int i = 1; i <= lineq->rows; ++i)
    free(A[i] + 1);
  free(A + 1);
  free(d);
  free(indx + 1);
  free_lineq(lineq);
}