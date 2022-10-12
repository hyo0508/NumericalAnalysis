#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include "lineq.h"
#include "nr.h"

void run_gaussj(const char *);
void run_ludcmp(const char *);
void run_svdcmp(const char *);

int main()
{
    run_gaussj("lineq_dat/lineq1.dat");
    run_ludcmp("lineq_dat/lineq1.dat");
    run_svdcmp("lineq_dat/lineq1.dat");

    run_gaussj("lineq_dat/lineq2.dat");
    run_ludcmp("lineq_dat/lineq2.dat");
    run_svdcmp("lineq_dat/lineq2.dat");

    run_gaussj("lineq_dat/lineq3.dat");
    run_ludcmp("lineq_dat/lineq3.dat");
    run_svdcmp("lineq_dat/lineq3.dat");

    return 0;
}

void run_gaussj(const char *filename)
{
    printf("\n");
    printf("gaussj\n");
    lineq_t *lineq;
    lineq = init_lineq(filename);
    print_lineq(lineq);

    gaussj(lineq->A, lineq->rows, lineq->B, 1);

    for (int i = 1; i <= lineq->cols; ++i)
        lineq->x[i] = lineq->B[i][1];
    print_solution(lineq);
    free_lineq(lineq);
}

void run_ludcmp(const char *filename)
{
    printf("\n");
    printf("ludcmp\n");
    lineq_t *lineq;
    lineq = init_lineq(filename);
    print_lineq(lineq);

    int *indx;
    float *d;
    indx = (int *)malloc(lineq->cols * sizeof(int)) - 1;
    d = (float *)malloc(sizeof(float));

    ludcmp(lineq->A, lineq->rows, indx, d);
    lubksb(lineq->A, lineq->rows, indx, lineq->b);

    for (int i = 1; i <= lineq->cols; ++i)
        lineq->x[i] = lineq->b[i];
    print_solution(lineq);
    free_lineq(lineq);
}

void run_svdcmp(const char *filename)
{
    printf("\n");
    printf("svdcmp\n");
    lineq_t *lineq;
    lineq = init_lineq(filename);
    print_lineq(lineq);

    float *w;
    float **v;
    int wnorm = (((lineq->rows) < (lineq->cols)) ? (lineq->rows) : (lineq->cols));
    w = (float *)malloc(wnorm * sizeof(float)) - 1;
    v = (float **)malloc(lineq->cols * sizeof(float *)) - 1;
    for (int i = 1; i <= lineq->cols; i++)
        v[i] = (float *)malloc(lineq->cols * sizeof(float)) - 1;

    svdcmp(lineq->A, lineq->rows, lineq->cols, w, v);
    svbksb(lineq->A, w, v, lineq->rows, lineq->cols, lineq->b, lineq->x);

    print_solution(lineq);
    free_lineq(lineq);
}
