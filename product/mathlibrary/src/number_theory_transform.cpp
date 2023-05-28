#include "number_theory_transform.h"

size_t number_theory_transform_fast_power(size_t a, size_t b)
{
    size_t ans = 1;
    size_t res = a;
    while (b)
    {
        if (b % 2 == 1)
        {
            ans = (ans * res) % NUMBER_THEORY_TRANSFORM_MODULAR;
        }
        res = (res * res) % NUMBER_THEORY_TRANSFORM_MODULAR;
        b = b / 2;
    }
    return ans;
}
size_t number_theory_transform_inverse(size_t x)
{
    return number_theory_transform_fast_power(x, NUMBER_THEORY_TRANSFORM_MODULAR - 2);
}
std::vector<size_t> number_theory_transform_of_power_two(std::vector<size_t> P, int opt)
{
    size_t N = P.size();
    size_t logN = 0;
    while (N % 2 == 0)
    {
        logN++;
        N /= 2;
    }
    N = P.size();
    if (N == 1)
    {
        return P;
    }
    size_t zeta = number_theory_transform_fast_power(NUMBER_THEORY_TRANSFORM_PRIME_ROOT, ((NUMBER_THEORY_TRANSFORM_MODULAR - 1) + (opt * NUMBER_THEORY_TRANSFORM_BASE * number_theory_transform_fast_power(2, NUMBER_THEORY_TRANSFORM_POWER - logN))) % (NUMBER_THEORY_TRANSFORM_MODULAR - 1)); // wait for standarlize
    // size_t zeta = number_theory_transform_fast_power(3, 4179340454199820288); // wait for standarlize
    // printf("%llu\n", zeta);
    std::vector<size_t> Pe, Po;
    Pe.resize(N / 2);
    Po.resize(N / 2);
    for (int i = 0; i < N / 2; i++)
    {
        Pe[i] = P[2 * i];
        Po[i] = P[2 * i + 1];
    }
    std::vector<size_t> ye = number_theory_transform_of_power_two(Pe, opt);
    std::vector<size_t> yo = number_theory_transform_of_power_two(Po, opt);
    std::vector<size_t> y;
    y.resize(N);
    for (int i = 0; i < N / 2; i++)
    {
        y[i] = (ye[i] + (number_theory_transform_fast_power(zeta, i) * yo[i]) % NUMBER_THEORY_TRANSFORM_MODULAR) % NUMBER_THEORY_TRANSFORM_MODULAR;
        y[i + N / 2] = (NUMBER_THEORY_TRANSFORM_MODULAR + ye[i] - (number_theory_transform_fast_power(zeta, i) * yo[i]) % NUMBER_THEORY_TRANSFORM_MODULAR) % NUMBER_THEORY_TRANSFORM_MODULAR;
    }
    return y;
}
std::vector<size_t> number_theory_transform(std::vector<size_t> P, int opt)
{
    size_t LEN = P.size();
    if (LEN == 0)
    {
        printf("fast_fourier_transformERROR:you have input a null vector\n");
        return P;
    }
    size_t N = exp2(ceil(log2(LEN)));
    std::vector<size_t> PP;
    PP.resize(N);
    for (int i = 0; i < LEN; i++)
    {
        PP[i] = P[i];
    }
    printf("fast_fourier_transformOUTPUT:we are deal with:[%d\n", N);
    for (int i = 0; i < N; i++)
    {
        printf("%llu\n", PP[i]);
    }
    printf("]\n");
    return number_theory_transform_of_power_two(PP, opt);
}
