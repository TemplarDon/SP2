#include "MathUtility.h"

int factorial(int n)
{
    if (n == 1 || n == 0)
    {
        return 1;
    }
    else
    {
        return n * factorial(n - 1);
    }
}

int nCr(int n, int r)
{
    float ans = (factorial(n) / (factorial(n - r) * factorial(r)));
	return ans;
}

int nPr(int n, int r)
{
    float ans = (factorial(n) / factorial(n - r));
    return ans;
}

int nTermAP(int a, int d, int n)
{
    int term = 1;
    while (term <= n)
    {
        a += d;
        ++term;
    }
	return a;
}

int summationAP(int a, int d, int n)
{
    int term = 2;
    while (term <= n)
    {
        a += nTermAP(a,d,term);
        ++term;
    }
    return a;
}

int nTermGP(int a, int r, int n)
{
    int term = 1;
    while (term < n)
    {
        a *= r;
        ++term;
    }
    return a;
}

int summationGP(int a, int r, int n)
{
    int term = 1;
    while (term < n)
    {
        a *= nTermGP(a, r, term + 1);
        ++term;
    }
    return a;
}