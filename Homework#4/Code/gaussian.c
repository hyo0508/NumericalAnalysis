#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "nr.h"

int main(int argc, char **argv)
{
    float mean = 0;
    float std = 50;

    int num;
    if (argc < 1)
    {
        num = 100;
    }
    else
    {
        num = atol(argv[1]);
    }

    long idum = time(NULL);
    for (int i = 0; i < num; ++i)
    {
        printf("%f\n", (gasdev(&idum) * std) + mean);
    }
}