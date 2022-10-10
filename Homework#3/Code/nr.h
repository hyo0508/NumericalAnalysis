#ifndef NR_H_
#define NR_H_

void gaussj(float **a, int n, float **b, int m);
void ludcmp(float **a, int n, int *indx, float *d);
void svdcmp(float **a, int m, int n, float w[], float **v);
void lubksb(float **a, int n, int *indx, float b[]);

#endif