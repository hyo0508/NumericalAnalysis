#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "nr.h"

#define XACC (1e-6f)

void function(float x, float *y, float *d)
{
  *y = tan(x);
  *d = exp(x) - 1;
}

int main(int argc, char **argv)
{
  float root = rtsafe(function, 1.1f, 2.f, XACC);
  printf("root: %.6f\n", root);
}