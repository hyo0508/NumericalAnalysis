#include <stdio.h>
#include <stdlib.h>
#include "nr.h"
#include "assert.h"

typedef struct
{
    float x, y, v, w;
} row_t;

typedef struct
{
    int N;
    row_t *rows;
} data_t;

data_t *init_data(const char *filename);
void free_data(data_t *data);
void run_data_fitting(const char *filename);

int main(int argc, char **argv)
{
    run_data_fitting("fitdata/fitdata1.dat");
    run_data_fitting("fitdata/fitdata2.dat");
    run_data_fitting("fitdata/fitdata3.dat");
}

data_t *init_data(const char *filename)
{
    data_t *data;
    FILE *fp;
    data = (data_t *)malloc(sizeof(data_t));
    fp = fopen(filename, "r");
    assert(fp);
    data->N = 0;
    data->rows = (row_t *)malloc(100 * sizeof(row_t));
    while (!feof(fp))
    {
        row_t r;
        if (fscanf(fp, "%f %f %f %f", &r.x, &r.y, &r.v, &r.w) != 4)
            break;
        data->rows[data->N++] = r;
    }
    data->rows = (row_t *)realloc(data->rows, data->N * sizeof(row_t));
    data->rows = data->rows - 1;
    return data;
}

void free_data(data_t *data)
{
    free(data->rows + 1);
    data->N = 0;
}

void run_data_fitting(const char *filename)
{

    data_t *data;
    data = init_data(filename);

    float **J = matrix(1, data->N, 1, 3);
    float **y = matrix(1, data->N, 1, 2);
    for (int i = 1; i <= data->N; i++)
    {
        J[i][1] = data->rows[i].x;
        J[i][2] = data->rows[i].y;
        J[i][3] = 1;
        y[i][1] = data->rows[i].v;
        y[i][2] = data->rows[i].w;
    }

    float **JJ = matrix(1, 3, 1, 3);
    float **Jy = matrix(1, 3, 1, 2);
    for (int j = 1; j <= 3; ++j)
    {
        for (int i = 1; i <= 3; ++i)
        {
            JJ[i][j] = 0;
            for (int k = 1; k <= data->N; ++k)
            {
                JJ[i][j] += J[k][i] * J[k][j];
            }
        }
    }

    for (int j = 1; j <= 2; ++j)
    {
        for (int i = 1; i <= 3; ++i)
        {
            Jy[i][j] = 0;
            for (int k = 1; k <= data->N; ++k)
            {
                Jy[i][j] += J[k][i] * y[k][j];
            }
        }
    }

    gaussj(JJ, 3, Jy, 2);
    for (int i = 1; i <= 3; ++i)
        for (int j = 1; j <= 2; ++j)
            printf("a%d: %f ", j + (i - 1) * 2, Jy[j][i]);
    printf("\n");

    free_matrix(Jy, 1, 2, 1, 3);
    free_matrix(JJ, 1, 3, 1, 3);
    free_matrix(y, 1, data->N, 1, 2);
    free_matrix(J, 1, data->N, 1, 3);
    free_data(data);
}