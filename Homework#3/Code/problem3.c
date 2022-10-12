#include <stdio.h>
#include <stdlib.h>
#include "lineq.h"
#include "nr.h"

void run_inverse(const char *filename);
void run_determinant(const char *filename);

int main(void)
{
  run_inverse("lineq_dat/lineq1.dat");
  run_determinant("lineq_dat/lineq1.dat");

  run_inverse("lineq_dat/lineq2.dat");
  run_determinant("lineq_dat/lineq2.dat");

  run_inverse("lineq_dat/lineq3.dat");
  run_determinant("lineq_dat/lineq3.dat");
}

void run_inverse(const char *filename)
{
  lineq_t *lineq;
  lineq = init_lineq(filename);
  print_lineq(lineq);

  float **y;
  float *col;
  y = (float **)malloc(lineq->cols * sizeof(float *)) - 1;
  for (int i = 1; i <= lineq->rows; ++i)
    y[i] = (float *)malloc(lineq->rows * sizeof(float)) - 1;
  col = (float *)malloc(lineq->cols * sizeof(float)) - 1;

  int *indx;
  float *d;
  indx = (int *)malloc(lineq->cols * sizeof(int)) - 1;
  d = (float *)malloc(sizeof(float));

  for (int i = 1; i <= lineq->cols; ++i)
    lineq->x[i] = lineq->b[i];

  ludcmp(lineq->A, lineq->rows, indx, d);
  for (int j = 1; j <= lineq->rows; ++j)
  {
    for (int i = 1; i <= lineq->cols; ++i)
      col[i] = 0.0;
    col[j] = 1.0;
    lubksb(lineq->A, lineq->rows, indx, col);
    for (int i = 1; i <= lineq->cols; ++i)
      y[i][j] = col[i];
  }

  printf("\nInverse of A\n");
  for (int i = 1; i <= lineq->cols; ++i)
  {
    for (int j = 1; j <= lineq->rows; ++j)
    {
      printf("%20f", y[i][j]);
    }
    printf("\n");
  }

  free(d);
  free(indx + 1);
  free_lineq(lineq);
}

void run_determinant(const char *filename)
{
  lineq_t *lineq;
  lineq = init_lineq(filename);

  int *indx;
  float *d;
  indx = (int *)malloc(lineq->cols * sizeof(int)) - 1;
  d = (float *)malloc(sizeof(float));

  for (int i = 1; i <= lineq->cols; ++i)
    lineq->x[i] = lineq->b[i];

  ludcmp(lineq->A, lineq->rows, indx, d);
  for (int j = 1; j <= lineq->rows; ++j)
  {
    *d *= lineq->A[j][j];
  }

  printf("\nDet A = %f\n", *d);

  free(d);
  free(indx + 1);
  free_lineq(lineq);
}