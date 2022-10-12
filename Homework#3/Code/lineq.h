#ifndef LINEQ_H_
#define LINEQ_H_

typedef struct
{
  int rows;
  int cols;
  float **A;
  float **B;
  float *x;
  float *b;
} lineq_t;

lineq_t *alloc_lineq(int, int);
lineq_t *init_lineq(const char *);
void free_lineq(lineq_t *);
void print_lineq(lineq_t *);
void print_solution(lineq_t *);

#endif