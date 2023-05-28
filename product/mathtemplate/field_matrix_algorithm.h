#ifndef FIELD_MATRIX_ALGORITHM
#define FIELD_MATRIX_ALGORITHM

#include "field_matrix.h"
#include "field_polynomial.h"

// replaced by determinant
/*
template <class F>
field_polynomial<F> character_polynomial(const field_matrix<field_polynomial<F>> &x) // E means Euclidean Ring not ready and im tendto make it a sudoinverse
{
    if (x.r != x.c)
    {
        field_polynomial<F> r;
        return r;
    }
    if (x.r == 1)
    {
        return x.dt[1][1];
    }
    long long N = x.c;
    field_matrix<field_polynomial<F>> M = x, M1(N - 1, N - 1);
    field_polynomial<F> P;
    P = M.dt[1][1];
    for (int i = 1; i <= N - 1; i++)
    {
        for (int j = 1; j <= N - 1; j++)
        {
            // printf("i=%d j=%d\n", i, j);
            M1.dt[i][j] = M.dt[i + 1][j + 1] * M.dt[1][1] - M.dt[1][j + 1] * M.dt[i + 1][1];
        }
    }
    return character_polynomial(M1) / fast_power(P, M.r - 2);
}
*/
template <class F>
field_polynomial<F> character_polynomial(const field_matrix<F> &x) // E means Euclidean Ring not ready and im tendto make it a sudoinverse
{
    // printf("sdfsdf1\n");
    if (x.r != x.c)
    {
        field_polynomial<F> r;
        return r;
    }
    // printf("sdfsdf2\n");
    field_matrix<field_polynomial<F>> M(x.r, x.r);
    // printf("sdfsdf3\n");
    F one;
    one = 1;
    // printf("sdfsdf4\n");
    for (int i = 1; i <= x.r; i++)
    {
        for (int j = 1; j <= x.c; j++)
        {
            if (i == j)
            {
                M.dt[i][j].dt.resize(2);
                M.dt[i][j].dt[0] = x.dt[i][j];
                M.dt[i][j].dt[1] = -one;
            }
            else
            {
                M.dt[i][j].dt.resize(1);
                M.dt[i][j].dt[0] = x.dt[i][j];
            }
        }
    }
    // printf("sdfsdf5\n");
    // M.print();
    return determinant(M);
}
void spectral_decomposition(const field_matrix<complexnumber> &x, field_matrix<complexnumber> &q, field_matrix<complexnumber> &l) // not ready and im tendto make it a sudoinverse
{
    printf("spectral_decompositionNOTICE:start\n");
    if (x.r != x.c)
    {
        printf("spectral_decompositionERROR:not square matrix\n");
        return;
    }
    field_polynomial<complexnumber> char_poly = character_polynomial(x);
    field_matrix<complexnumber> y = x, z, Q(x.r, x.r), L(x.r, x.r);
    std::vector<complexnumber> v = factorization(char_poly);
    complexnumber zero;
    complexnumber one(1, 0);
    for (int i = 1; i <= x.r; i++)
    {
        for (int j = 1; j <= x.r; j++)
        {
            L.dt[i][j] = zero;
            if (i == j)
            {
                L.dt[i][j] = v[i - 1];
            }
        }
    }
    for (int t = x.r; t >= 1; t--)
    {
        for (int i = 1; i <= x.r; i++)
        {
            y.dt[i][i] = x.dt[i][i] - v[t - 1];
        }
        z = row_echelon(y);
        complexnumber len(0, 0);
        complexnumber c_2nd(0.5, 0);
        for (int i = 1; i <= x.r - 1; i++)
        {
            complexnumber dl2(z.dt[i][x.r].r * z.dt[i][x.r].r, 0);
            len = len + (dl2);
        }
        len = len + one;
        len = len ^ c_2nd;
        len.print();
        for (int i = 1; i <= x.r - 1; i++)
        {
            Q.dt[i][t] = z.dt[i][x.r] / len;
        }
        Q.dt[x.r][t] = -one / len;
    }
    complexnumber det = determinant(Q);
    complexnumber tmp;
    printf("------det\n");
    det.print(1);
    printf("\n");
    if (!(det == one))
    {
        for (int i = 1; i <= x.r; i++)
        {
            tmp = Q.dt[i][1];
            Q.dt[i][1] = Q.dt[i][2];
            Q.dt[i][2] = tmp;
        }
        tmp = L.dt[1][1];
        L.dt[1][1] = L.dt[2][2];
        L.dt[2][2] = tmp;
    }
    q = Q;
    l = L;
}
void jordan_decomposition(const field_matrix<complexnumber> &x, field_matrix<complexnumber> &q, field_matrix<complexnumber> &l) // not ready and im tendto make it a sudoinverse
{
    printf("jordan_decompositionNOTICE:start\n");
    if (x.r != x.c)
    {
        printf("jordan_decompositionERROR:not square matrix\n");
        return;
    }
    field_polynomial<complexnumber> char_poly = character_polynomial(x);
    field_matrix<complexnumber> y = x, z, Q(x.r, x.r), L(x.r, x.r);
    std::vector<complexnumber> v = factorization(char_poly);
    std::vector<complexnumber> vv;
    std::vector<int> vvv(v.size());
    std::vector<std::vector<std::vector<field_matrix<complexnumber>>>> V;
    char_poly.print();
    printf("\n");
    vv.push_back(v[0]);
    vvv[0] = 1;
    for (int i = 1; i < v.size(); i++)
    {
        int inn = 1;
        for (int j = 0; j < vv.size(); j++)
        {
            if ((vv[j] - v[i]).r < 1e-5)
            {
                inn = 0;
                vvv[j] += 1;
                break;
            }
        }
        if (inn == 0)
        {
            continue;
        }
        vv.push_back(v[i]);
        vvv[vv.size() - 1] = 1;
    }
    for (int i = 0; i < v.size(); i++)
    {
        v[i].print();
    }
    printf("v\n");
    for (int i = 0; i < vv.size(); i++)
    {
        vv[i].print();
    }
    printf("vv\n");
    for (int i = 0; i < vv.size(); i++)
    {
        printf("%d ", vvv[i]);
    }
    printf("vvv\n");
    V.resize(vv.size());
    complexnumber zero;
    complexnumber one(1, 0);
    for (int i = 0; i < vv.size(); i++)
    {
        for (int j = 1; j <= x.r; j++)
        {
            y.dt[j][j] = x.dt[j][j] - vv[i];
        }
        z = row_echelon(y);
        z.print();
        for (int j = x.r; j >= 1; j--)
        {
            if (!(z.dt[j][j] == zero))
            {
                break;
            }
            V[i].resize(V[i].size() + 1);
            field_matrix<complexnumber> cl(x.r, 1);
            for (int k = 1; k <= x.r; k++)
            {
                cl.dt[k][1] = z.dt[k][j];
            }
            cl.dt[j][1] = -one;
            V[i][V[i].size() - 1].resize(1);
            V[i][V[i].size() - 1][0] = cl;
        }
    }
    for (int i = 0; i < V.size(); i++)
    {
        for (int j = 0; j < V[i].size(); j++)
        {
            for (int k = 0; k < V[i][j].size(); k++)
            {
                V[i][j][k].print();
            }
        }
        printf("\n");
    }
    /*
    for (int i = 1; i <= x.r; i++)
    {
        for (int j = 1; j <= x.r; j++)
        {
            L.dt[i][j] = zero;
            if (i == j)
            {
                L.dt[i][j] = v[i - 1];
            }
        }
    }
    for (int t = x.r; t >= 1; t--)
    {
        for (int i = 1; i <= x.r; i++)
        {
            y.dt[i][i] = x.dt[i][i] - v[t - 1];
        }
        z = row_echelon(y);
        complexnumber len(0, 0);
        complexnumber c_2nd(0.5, 0);
        for (int i = 1; i <= x.r - 1; i++)
        {
            complexnumber dl2(z.dt[i][x.r].r * z.dt[i][x.r].r, 0);
            len = len + (dl2);
        }
        len = len + one;
        len = len ^ c_2nd;
        len.print();
        for (int i = 1; i <= x.r - 1; i++)
        {
            Q.dt[i][t] = z.dt[i][x.r] / len;
        }
        Q.dt[x.r][t] = -one / len;
    }
    complexnumber det = determinant(Q);
    complexnumber tmp;
    printf("------det\n");
    det.print(1);
    printf("\n");
    if (!(det == one))
    {
        for (int i = 1; i <= x.r; i++)
        {
            tmp = Q.dt[i][1];
            Q.dt[i][1] = Q.dt[i][2];
            Q.dt[i][2] = tmp;
        }
        tmp = L.dt[1][1];
        L.dt[1][1] = L.dt[2][2];
        L.dt[2][2] = tmp;
    }
    q = Q;
    l = L;
    */
}
void singular_value_decomposition(const field_matrix<complexnumber> &x, field_matrix<complexnumber> &U, field_matrix<complexnumber> &Sigma, field_matrix<complexnumber> &V) // not ready and im tendto make it a sudoinverse
{
    field_matrix<complexnumber> SL = x * transpose(x);
    field_matrix<complexnumber> SR = transpose(x) * x;
    field_matrix<complexnumber> L;
    field_matrix<complexnumber> s(x.r, x.c);
    complexnumber c_2nd(0.5, 0);
    printf("SL\n");
    SL.print();
    SR.print();
    // U.print();
    // V.print();
    // L.print();
    // s.print();
    spectral_decomposition(SL, U, L);
    spectral_decomposition(SR, V, L);
    for (int i = 1; i <= FIELD_MATRIX_MIN(x.r, x.c); i++)
    {
        s.dt[i][i] = L.dt[i][i] ^ c_2nd;
    }
    Sigma = s;
}
field_matrix<complexnumber> general_inverse(const field_matrix<complexnumber> &x) // not ready and im tendto make it a sudoinverse
{
    field_matrix<complexnumber> ix(x.r, x.c), U, S, V, s;
    singular_value_decomposition(x, U, S, V);
    complexnumber one(1, 0);
    printf("S\n");
    S.print();
    U.print();
    V.print();
    printf("or\n");
    s = S;
    (U * s * transpose(V)).print();
    for (int i = 1; i <= FIELD_MATRIX_MIN(x.r, x.c); i++)
    {
        S.dt[i][i] = one / S.dt[i][i];
    }
    S.print();
    (U * transpose(U)).print();
    determinant(U).print();
    printf("\n");
    (transpose(V) * V).print();
    determinant(V).print();
    printf("\n");
    ix = V * transpose(S) * transpose(U);
    (x * ix).print();
    (U * s * transpose(V) * V * transpose(S) * transpose(U)).print();
    return ix;
}

#endif
