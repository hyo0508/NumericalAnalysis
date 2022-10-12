#include "lineq.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

lineq_t *alloc_lineq(rows, cols)
{
    lineq_t *lineq;
    lineq = (lineq_t *)malloc(sizeof(lineq_t));
    lineq->rows = rows;
    lineq->cols = cols;
    lineq->A = (float **)malloc(rows * sizeof(float *)) - 1;
    for (int i = 1; i <= rows; ++i)
    {
        lineq->A[i] = (float *)malloc(cols * sizeof(float)) - 1;
    }
    lineq->B = (float **)malloc(rows * sizeof(float *)) - 1;
    for (int i = 1; i <= rows; ++i)
    {
        lineq->B[i] = (float *)malloc(sizeof(float)) - 1;
    }
    lineq->x = (float *)malloc(cols * sizeof(float)) - 1;
    lineq->b = (float *)malloc(rows * sizeof(float)) - 1;
    return lineq;
}

lineq_t *init_lineq(const char *filename)
{
    int rows, cols;
    FILE *fp;
    fp = fopen(filename, "r");
    assert(fp);
    fscanf(fp, "%d %d", &rows, &cols);
    lineq_t *lineq = alloc_lineq(rows, cols);
    for (int i = 1; i <= lineq->rows; ++i)
    {
        for (int j = 1; j <= lineq->cols; ++j)
        {
            fscanf(fp, "%f", &lineq->A[i][j]);
        }
    }
    for (int i = 1; i <= lineq->rows; ++i)
    {
        fscanf(fp, "%f", &lineq->b[i]);
        lineq->B[i][1] = lineq->b[i];
    }
    fclose(fp);
    return lineq;
}

void free_lineq(lineq_t *lineq)
{
    int rows, cols;
    rows = lineq->rows;
    cols = lineq->cols;
    for (int i = 1; i <= rows; ++i)
    {
        free(lineq->A[i] + 1);
        lineq->A[i] = NULL;
    }
    free(lineq->A + 1);
    lineq->A = NULL;
    for (int i = 1; i <= rows; ++i)
    {
        free(lineq->B[i] + 1);
        lineq->B[i] = NULL;
    }
    free(lineq->B + 1);
    lineq->B = NULL;
    free(lineq->x + 1);
    lineq->x = NULL;
    free(lineq->b + 1);
    lineq->b = NULL;
    lineq = NULL;
}

void print_lineq(lineq_t *lineq)
{
    printf("\nA | b\n");
    for (int i = 1; i <= lineq->rows; ++i)
    {
        for (int j = 1; j <= lineq->cols; ++j)
        {
            printf("%20f", lineq->A[i][j]);
        }
        printf("\t| %20f\n", lineq->b[i]);
    }
}

void print_solution(lineq_t *lineq)
{
    printf("\nx\n");
    for (int i = 1; i <= lineq->cols; ++i)
    {
        printf("%20f\n", lineq->x[i]);
    }
}