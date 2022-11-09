#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "nr.h"

int main(int argc, char **argv)
{
    float a = 0;
    float b = 100;

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
        printf("%f\n", a + (b - a) * ran1(&idum));
    }
}