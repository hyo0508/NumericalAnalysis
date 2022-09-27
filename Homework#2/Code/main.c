#include <stdio.h>
#include <math.h>
#include "nr.h"

#define XACC (1e-6f)

void bessj0_with_gradient(float x, float *y, float *grad);
float run(float (*solver)(float (*)(float), float, float, float), float x1, float x2);
float run_diff_method(float (*solver)(void (*)(float, float *, float *), float, float, float), float x1, float x2);
float muller(float (*f)(float), float x1, float x2, float xacc);

int main()
{
    float xb1[100], xb2[100];
    int numRoots = 0;

    zbrak(bessj0, 1.0, 10.0, 900, xb1, xb2, &numRoots);

    printf("Bisection\n");
    for (int i = 1; i <= numRoots; i++)
        printf(" %.6f", run(rtbis, xb1[i], xb2[i]));
    printf("\n\n");

    printf("Linear interpolation\n");
    for (int i = 1; i <= numRoots; i++)
        printf(" %.6f", run(rtflsp, xb1[i], xb2[i]));
    printf("\n\n");

    printf("Secant\n");
    for (int i = 1; i <= numRoots; i++)
        printf(" %.6f", run(rtsec, xb1[i], xb2[i]));
    printf("\n\n");

    printf("Newton-Raphson\n");
    for (int i = 1; i <= numRoots; i++)
        printf(" %.6f", run_diff_method(rtnewt, xb1[i], xb2[i]));
    printf("\n\n");

    printf("Newton with bracketing\n");
    for (int i = 1; i <= numRoots; i++)
        printf(" %.6f", run_diff_method(rtsafe, xb1[i], xb2[i]));
    printf("\n\n");

    printf("Muller\n");
    for (int i = 1; i <= numRoots; i++)
    {
        printf(" %.6f", muller(bessj0, xb1[i], xb2[i], XACC));
    }
    printf("\n\n");

    return 0;
}

void bessj0_with_gradient(float x, float *y, float *grad)
{
    *y = bessj0(x);
    *grad = -bessj1(x);
}

float run(float (*solver)(float (*)(float), float, float, float), float x1, float x2)
{
    return solver(bessj0, x1, x2, XACC);
}

float run_diff_method(float (*solver)(void (*)(float, float *, float *), float, float, float), float x1, float x2)
{
    return solver(bessj0_with_gradient, x1, x2, XACC);
}

float muller(float (*f)(float), float x1, float x2, float xacc)
{
    float p0 = (x1 > x2) ? x2 : x1;
    float p1 = (x1 + x2) / 2.f;
    float p2 = (x1 > x2) ? x1 : x2;
    float p3;
    float h0, h1, d0, d1, a, b, c, dx;

    for (int j = 0; j < 30; ++j)
    {
        h0 = p1 - p0;
        h1 = p2 - p1;
        d0 = (f(p1) - f(p0)) / (p1 - p0);
        d1 = (f(p2) - f(p1)) / (p2 - p1);

        a = (d1 - d0) / (h1 + h0);
        b = a * h1 + d1;
        c = f(p2);

        dx = (-2 * c) / (b + sqrt(b * b - 4 * a * c) * (b > 0 ? 1 : -1));
        p3 = p2 + dx;

        if (fabs(dx) < p3 * xacc)
            return p3;
        if (isnan(a) || isnan(b) || isnan(c))
            return p2;

        p0 = p1;
        p1 = p2;
        p2 = p3;
    }
    return 0.f;
}