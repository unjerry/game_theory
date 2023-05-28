#ifndef FIELD_MATRIX_H
#define FIELD_MATRIX_H

#include <vector>
#include <stdio.h>
#include "number_theory_algorithm.h"

#define FIELD_MATRIX_MAX(a, b) ((a > b) ? (a) : (b))
#define FIELD_MATRIX_MIN(a, b) ((a < b) ? (a) : (b))

template <class F>
class field_matrix
{
public:
    long long r, c;
    std::vector<std::vector<F>> dt;
    field_matrix(const long long r = 0, const long long c = 0);
    void print(int opt = 0);
    void fprint(FILE *f, int opt = 0);
    int scan(int opt = 0);
    int fscan(FILE *f, int opt = 0);
    field_matrix operator-();
};
template <class F>
field_matrix<F>::field_matrix(const long long r, const long long c)
{
    this->r = r;
    this->c = c;
    this->dt.resize(r + 1);
    for (int i = 1; i <= r; i++)
    {
        this->dt[i].resize(c + 1);
        for (int j = 1; j <= this->c; j++)
        {
            dt[i][j] = 0;
        }
    }
}
template <class F>
void field_matrix<F>::print(int opt)
{
    printf("[%d,%d\n", r, c);
    if (r * c != 0)
    {
        for (int i = 1; i <= this->r; i++)
        {
            for (int j = 1; j <= this->c; j++)
            {
                this->dt[i][j].print(opt);
                printf(",");
            }
            printf("\n");
        }
    }
    else
    {
        printf("NULLMATRIX\n");
    }
    printf("]\n");
}
template <class F>
void field_matrix<F>::fprint(FILE *f, int opt)
{
    fprintf(f, "[%d,%d\n", r, c);
    if (r * c != 0)
    {
        for (int i = 1; i <= this->r; i++)
        {
            for (int j = 1; j <= this->c; j++)
            {
                this->dt[i][j].fprint(f, opt);
                fprintf(f, ",");
            }
            fprintf(f, "\n");
        }
    }
    else
    {
        fprintf(f, "NULLMATRIX\n");
    }
    fprintf(f, "]\n");
}
template <class F>
int field_matrix<F>::scan(int opt)
{
    int rt;
    scanf("%*[^[]");
    rt = scanf("[%d,%d\n", &this->r, &this->c);
    this->dt.resize(r + 1);
    for (int i = 1; i <= r; i++)
    {
        this->dt[i].resize(c + 1);
    }
    if (r * c != 0)
    {
        for (int i = 1; i <= this->r; i++)
        {
            for (int j = 1; j <= this->c; j++)
            {
                this->dt[i][j].scan(opt);
                scanf(",");
            }
            scanf("\n");
        }
    }
    else
    {
        scanf("NULLMATRIX\n");
    }
    scanf("]\n");
    return rt;
}
template <class F>
int field_matrix<F>::fscan(FILE *f, int opt)
{
    int rt;
    fscanf(f, "%*[^[]");
    rt = fscanf(f, "[%d,%d\n", &this->r, &this->c);
    this->dt.resize(r + 1);
    for (int i = 1; i <= r; i++)
    {
        this->dt[i].resize(c + 1);
    }
    if (r * c != 0)
    {
        for (int i = 1; i <= this->r; i++)
        {
            for (int j = 1; j <= this->c; j++)
            {
                this->dt[i][j].fscan(f, opt);
                fscanf(f, ",");
            }
            fscanf(f, "\n");
        }
    }
    else
    {
        fscanf(f, "NULLMATRIX\n");
    }
    fscanf(f, "]\n");
    return rt;
}
template <class F>
field_matrix<F> field_matrix<F>::operator-()
{
    field_matrix<F> ans(this->r, this->c);
    for (int i = 1; i <= ans.r; i++)
    {
        for (int j = 1; j <= ans.c; j++)
        {
            ans.dt[i][j] = -this->dt[i][j];
        }
    }
    return ans;
}

template <class F>
field_matrix<F> operator*(const field_matrix<F> &a, const field_matrix<F> &b)
{
    if (a.c == b.r)
    {
        field_matrix<F> c(a.r, b.c);
        for (int i = 1; i <= c.r; i++)
        {
            for (int j = 1; j <= c.c; j++)
            {
                for (int k = 1; k <= a.c; k++)
                {
                    c.dt[i][j] = c.dt[i][j] + (a.dt[i][k] * b.dt[k][j]);
                }
            }
        }
        return c;
    }
    else
    {
        field_matrix<F> c;
        return c;
    }
}
template <class F>
field_matrix<F> operator*(const F &a, const field_matrix<F> &b)
{
    // printf("field_matrix_number_multiplicationNOTICE:scalor multiplication\n");
    field_matrix<F> c(b.r, b.c);
    for (int i = 1; i <= c.r; i++)
    {
        for (int j = 1; j <= c.c; j++)
        {
            c.dt[i][j] = a * b.dt[i][j];
        }
    }
    return c;
}
template <class F>
field_matrix<F> operator+(const field_matrix<F> &a, const field_matrix<F> &b)
{
    if (a.r != b.r || a.c != b.c)
    {
        // printf("field_matrix_additionNOTICE:matrix size different\n");
    }
    field_matrix<F> c(FIELD_MATRIX_MAX(a.r, b.r), FIELD_MATRIX_MAX(a.c, b.c));
    for (int i = 1; i <= a.r; i++)
    {
        for (int j = 1; j <= a.c; j++)
        {
            c.dt[i][j] = c.dt[i][j] + a.dt[i][j];
        }
    }
    for (int i = 1; i <= b.r; i++)
    {
        for (int j = 1; j <= b.c; j++)
        {
            c.dt[i][j] = c.dt[i][j] + b.dt[i][j];
        }
    }
    return c;
}
template <class F>
field_matrix<F> operator-(const field_matrix<F> &a, const field_matrix<F> &b)
{
    field_matrix<F> tmp = b;
    return a + (-tmp);
}
template <class F>
field_matrix<F> matrix_pointwise_multiplication(const field_matrix<F> &a, const field_matrix<F> &b)
{
    if (a.r != b.r || a.c != b.c)
    {
        printf("field_matrix_pointwise_multiplicationNOTICE:matrix size different\n");
    }
    field_matrix<F> c(FIELD_MATRIX_MAX(a.r, b.r), FIELD_MATRIX_MAX(a.c, b.c));
    for (int i = 1; i <= c.r; i++)
    {
        for (int j = 1; j <= c.c; j++)
        {
            c.dt[i][j] = 1;
        }
    }
    for (int i = 1; i <= a.r; i++)
    {
        for (int j = 1; j <= a.c; j++)
        {
            c.dt[i][j] = c.dt[i][j] * a.dt[i][j];
        }
    }
    for (int i = 1; i <= b.r; i++)
    {
        for (int j = 1; j <= b.c; j++)
        {
            c.dt[i][j] = c.dt[i][j] * b.dt[i][j];
        }
    }
    return c;
}
template <class F>
field_matrix<F> row_echelon(const field_matrix<F> &x)
{
    field_matrix<F> M = x;
    const F zero;
    long long r = 1;
    long long c = 1;
    long long tr;
    long long tc;
    F tmp;
    while (1)
    {
        if (r > M.r || c > M.c)
        {
            break;
        }
        tr = tc = 0;
        // find where to start
        for (int j = c; j <= M.c; j++)
        {
            if (tr != 0)
            {
                break;
            }
            for (int i = r; i <= M.r; i++)
            {
                if (!(M.dt[i][j] == zero))
                {
                    tr = i;
                    tc = j;
                    break;
                }
            }
        }
        if (tr == 0)
        {
            break;
        }
        // exchange
        for (int j = tc; j <= M.c; j++)
        {
            tmp = M.dt[r][j];
            M.dt[r][j] = M.dt[tr][j];
            M.dt[tr][j] = tmp;
        }
        tmp = M.dt[r][tc];
        for (int j = tc; j <= M.c; j++)
        {
            M.dt[r][j] = M.dt[r][j] / tmp;
        }
        for (int i = 1; i <= M.r; i++)
        {
            if (i == r)
            {
                continue;
            }
            tmp = M.dt[i][tc];
            for (int j = tc; j <= M.c; j++)
            {
                M.dt[i][j] = M.dt[i][j] - M.dt[r][j] * tmp;
            }
        }
        r = r + 1;
        c = tc + 1;
    }
    return M;
}
template <class F>
field_matrix<F> column_echelon(const field_matrix<F> &x) // can be replace by transpose & rowechelon
{
    field_matrix<F> M = x;
    const F zero;
    long long r = 1;
    long long c = 1;
    long long tr;
    long long tc;
    F tmp;
    while (1)
    {
        if (r > M.r || c > M.c)
        {
            break;
        }
        tr = tc = 0;
        // find where to start
        for (int i = r; i <= M.r; i++)
        {
            if (tr != 0)
            {
                break;
            }
            for (int j = c; j <= M.c; j++)
            {
                if (!(M.dt[i][j] == zero))
                {
                    tr = i;
                    tc = j;
                    break;
                }
            }
        }
        if (tr == 0)
        {
            break;
        }
        // exchange
        for (int i = tr; i <= M.r; i++)
        {
            tmp = M.dt[i][c];
            M.dt[i][c] = M.dt[i][tc];
            M.dt[i][tc] = tmp;
        }
        tmp = M.dt[tr][c];
        for (int i = tr; i <= M.r; i++)
        {
            M.dt[i][c] = M.dt[i][c] / tmp;
        }
        for (int j = 1; j <= M.c; j++)
        {
            if (j == c)
            {
                continue;
            }
            tmp = M.dt[tr][j];
            for (int i = tr; i <= M.r; i++)
            {
                M.dt[i][j] = M.dt[i][j] - M.dt[i][c] * tmp;
            }
        }
        c = c + 1;
        r = tr + 1;
    }
    return M;
}
template <class F>
field_matrix<F> transpose(const field_matrix<F> &x) // not ready and im tendto make it a sudoinverse
{
    field_matrix<F> M(x.c, x.r);
    for (int i = 1; i <= M.r; i++)
    {
        for (int j = 1; j <= M.c; j++)
        {
            M.dt[i][j] = x.dt[j][i];
        }
    }
    return M;
}
template <class F>
F determinant(const field_matrix<F> &x) // E means Euclidean Ring not ready and im tendto make it a sudoinverse
{
    if (x.r != x.c)
    {
        F r;
        return r;
    }
    if (x.r == 1)
    {
        return x.dt[1][1];
    }
    long long N = x.c;
    field_matrix<F> M = x, M1(N - 1, N - 1);
    F P;
    P = M.dt[1][1];
    for (int i = 1; i <= N - 1; i++)
    {
        for (int j = 1; j <= N - 1; j++)
        {
            // printf("i=%d j=%d\n", i, j);
            M1.dt[i][j] = M.dt[i + 1][j + 1] * M.dt[1][1] - M.dt[1][j + 1] * M.dt[i + 1][1];
        }
    }
    return determinant(M1) / fast_power(P, M.r - 2);
}
template <class F>
F norm(const field_matrix<F> &x) // E means Euclidean Ring not ready and im tendto make it a sudoinverse
{
    F ans;
    for (int i = 1; i <= x.r; i++)
    {
        for (int j = 1; j <= x.c; j++)
        {
            ans = ans + (x.dt[i][j] * x.dt[i][j]);
        }
    }
    return ans;
}
template <class F>
field_matrix<F> equivalent_normalized_form(const field_matrix<F> &x)
{
    return column_echelon(row_echelon(x));
}
#endif
