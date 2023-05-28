#include "list_convolution.h"

std::vector<complexnumber> list_convolution(const std::vector<complexnumber> &a, const std::vector<complexnumber> &b)
{
    long long LENA = a.size();
    long long LENB = b.size();
    long long NN = LENA + LENB - 1;
    long long N = exp2(ceil(log2(NN)));
    complexnumber complex_N(N, 0, 0); // wait for another api

    std::vector<complexnumber> ac;
    ac.resize(N);
    for (int i = 0; i < LENA; i++)
    {
        ac[i] = a[i];
    }
    std::vector<complexnumber> bc;
    bc.resize(N);
    for (int i = 0; i < LENB; i++)
    {
        bc[i] = b[i];
    }

    std::vector<complexnumber> A, B, C;
    A = fast_fourier_transform_of_power_two(ac, 1);
    B = fast_fourier_transform_of_power_two(bc, 1);

    C.resize(N);
    for (int i = 0; i < N; i++)
    {
        C[i] = (A[i] / complex_N) * B[i];
    }

    std::vector<complexnumber> cc;
    cc = fast_fourier_transform_of_power_two(C, -1);

    std::vector<complexnumber> c;
    c.resize(NN);
    for (int i = 0; i < NN; i++)
    {
        c[i] = cc[i];
    }

    return c;
}
std::vector<size_t> list_convolution(const std::vector<size_t> &a, const std::vector<size_t> &b)
{
    long long LENA = a.size();
    long long LENB = b.size();
    long long NN = LENA + LENB - 1;
    long long N = exp2(ceil(log2(NN)));
    size_t inv_N = number_theory_transform_inverse(N); // wait for another api

    std::vector<size_t> ac;
    ac.resize(N);
    for (int i = 0; i < LENA; i++)
    {
        ac[i] = a[i];
    }
    std::vector<size_t> bc;
    bc.resize(N);
    for (int i = 0; i < LENB; i++)
    {
        bc[i] = b[i];
    }

    std::vector<size_t> A, B, C;
    A = number_theory_transform_of_power_two(ac, 1);
    B = number_theory_transform_of_power_two(bc, 1);

    C.resize(N);
    for (int i = 0; i < N; i++)
    {
        C[i] = ((A[i] * inv_N) % NUMBER_THEORY_TRANSFORM_MODULAR * B[i]) % NUMBER_THEORY_TRANSFORM_MODULAR;
    }

    std::vector<size_t> cc;
    cc = number_theory_transform_of_power_two(C, -1);

    std::vector<size_t> c;
    c.resize(NN);
    for (int i = 0; i < NN; i++)
    {
        c[i] = cc[i];
    }

    return c;
}
