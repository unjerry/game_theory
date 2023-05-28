#include "fast_fourier_transform.h"

std::vector<complexnumber> fast_fourier_transform_of_power_two(std::vector<complexnumber> P, int opt)
{
    long long N = P.size();
    if (N == 1)
    {
        return P;
    }
    complexnumber zeta(1, opt * 2.0 * PI / N, 1); // wait for standarlize
    std::vector<complexnumber> Pe, Po;
    Pe.resize(N / 2);
    Po.resize(N / 2);
    for (int i = 0; i < N / 2; i++)
    {
        Pe[i] = P[2 * i];
        Po[i] = P[2 * i + 1];
    }
    std::vector<complexnumber> ye = fast_fourier_transform_of_power_two(Pe, opt);
    std::vector<complexnumber> yo = fast_fourier_transform_of_power_two(Po, opt);
    std::vector<complexnumber> y;
    y.resize(N);
    for (int i = 0; i < N / 2; i++)
    {
        complexnumber power_i(i, 0, 0); // wait for change
        y[i] = ye[i] + (zeta ^ power_i) * yo[i];
        y[i + N / 2] = ye[i] - (zeta ^ power_i) * yo[i];
    }
    //printf("po2=%d\n", N);
    return y;
}
std::vector<complexnumber> fast_fourier_transform(std::vector<complexnumber> P, int opt)
{
    long long LEN = P.size();
    if (LEN == 0)
    {
        printf("fast_fourier_transformERROR:you have input a null vector\n");
        return P;
    }
    long long N = exp2(ceil(log2(LEN)));
    std::vector<complexnumber> PP;
    PP.resize(N);
    for (int i = 0; i < LEN; i++)
    {
        PP[i] = P[i];
    }
    printf("fast_fourier_transformOUTPUT:we are deal with:[%d\n", N);
    for (int i = 0; i < N; i++)
    {
        PP[i].print();
        printf("\n");
    }
    printf("]\n");
    return fast_fourier_transform_of_power_two(PP, opt);
}
