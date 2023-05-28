#ifndef FIELD_POLYNOMIAL_H
#define FIELD_POLYNOMIAL_H

#include <vector>
#include <stdio.h>
#include <math.h>
#include "complexnumber.h"
#include "list_convolution.h"
#include "number_theory_algorithm.h"

#define FIELD_POLYNOMIAL_MAX(a, b) ((a > b) ? (a) : (b))
#define FIELD_POLYNOMIAL_MIN(a, b) ((a < b) ? (a) : (b))
#define Abs(a, b) (((a - b) >= 0) ? (a - b) : (b - a))
#define Eps 1e-15

template <class F>
class field_polynomial
{
public:
    std::vector<F> dt; // coefficient
    field_polynomial();
    field_polynomial(F *coefficient, size_t len); // len>=1
    field_polynomial operator-();                 // negative O(N)
    void print(int opt = 0);
    void fprint(FILE *f, int opt = 0);
    int scan(int opt = 0);
    int fscan(FILE *f, int opt = 0);
    void operator=(const size_t &y);
    void monic_polynomialize();
    F interopolation(const F &x);
};
template <class F>
field_polynomial<F>::field_polynomial()
{
    this->dt.resize(1);
    this->dt[0] = 0;
}
template <class F>
field_polynomial<F>::field_polynomial(F *coefficient, size_t len)
{
    this->dt.resize(len);
    for (int i = 0; i < len; i++)
    {
        this->dt[i] = coefficient[i];
    }
}
template <class F>
field_polynomial<F> field_polynomial<F>::operator-() // negative O(N)
{
    field_polynomial<F> x = *this;
    for (int i = 0; i < x.dt.size(); i++)
    {
        x.dt[i] = -x.dt[i];
    }
    return x;
}
template <class F>
void field_polynomial<F>::print(int opt) // k=1 coefficient k=2 polynomial
{
    switch (opt)
    {
    case 2:
        printf("(len=%d)<", this->dt.size());
        this->dt[0].print(opt);
        for (int i = 1; i < this->dt.size(); i++)
        {
            printf("+");
            this->dt[i].print(0);
            printf("*x^%d", i);
        }
        printf(">");
        break;

    default:
        printf("(len=%d)<", this->dt.size());
        this->dt[0].print(opt);
        for (int i = 1; i < this->dt.size(); i++)
        {
            printf(",");
            this->dt[i].print(opt);
        }
        printf(">");
        break;
    }
}
template <class F>
void field_polynomial<F>::fprint(FILE *f, int opt) // k=1 coefficient k=2 polynomial
{
    switch (opt)
    {
    case 2:
        fprintf(f, "(len=%d)<", this->dt.size());
        this->dt[0].fprint(f);
        for (int i = 1; i < this->dt.size(); i++)
        {
            fprintf(f, "+");
            this->dt[i].fprint(f);
            fprintf(f, "*x^%d", i);
        }
        fprintf(f, ">");
        break;

    default:
        fprintf(f, "(len=%d)<", this->dt.size());
        this->dt[0].fprint(f, opt);
        for (int i = 1; i < this->dt.size(); i++)
        {
            fprintf(f, ",");
            this->dt[i].fprint(f, opt);
        }
        fprintf(f, ">");
        break;
    }
}
template <class F>
int field_polynomial<F>::scan(int opt) // k=1 coefficient k=2 polynomial
{
    int rt, tmp;
    switch (opt)
    {
    case 2:
        scanf("%*[^(]");
        rt = scanf("(len=%d)<", &tmp);
        this->dt.resize(tmp);
        this->dt[0].scan();
        for (int i = 1; i < this->dt.size(); i++)
        {
            scanf("+");
            this->dt[i].scan();
            scanf("*x^%d", &tmp);
        }
        scanf(">");
        break;

    default:
        scanf("%*[^(]");
        rt = scanf("(len=%d)<", &tmp);
        this->dt.resize(tmp);
        this->dt[0].scan(opt);
        for (int i = 1; i < this->dt.size(); i++)
        {
            scanf(",");
            this->dt[i].scan(opt);
        }
        scanf(">");
        break;
    }
    return rt;
}
template <class F>
int field_polynomial<F>::fscan(FILE *f, int opt) // k=1 coefficient k=2 polynomial
{
    int rt, tmp;
    switch (opt)
    {
    case 2:
        fscanf(f, "%*[^(]");
        rt = fscanf(f, "(len=%d)<", &tmp);
        this->dt.resize(tmp);
        this->dt[0].fscan(f);
        for (int i = 1; i < this->dt.size(); i++)
        {
            fscanf(f, "+");
            this->dt[i].fscan(f);
            fscanf(f, "*x^%d", &tmp);
        }
        fscanf(f, ">");
        break;

    default:
        // printf("fscanf\n");
        fscanf(f, "%*[^(]");
        rt = fscanf(f, "(len=%d)<", &tmp);
        // printf("%d %d\n", rt, tmp);
        this->dt.resize(tmp);
        this->dt[0].fscan(f, opt);
        for (int i = 1; i < this->dt.size(); i++)
        {
            fscanf(f, ",");
            this->dt[i].fscan(f, opt);
        }
        fscanf(f, ">");
        break;
    }
    return rt;
}
template <class F>
void field_polynomial<F>::operator=(const size_t &y)
{
    switch (y)
    {
    case 1:
        this->dt.resize(1);
        this->dt[0] = 1;
        break;

    default:
        this->dt.resize(1);
        this->dt[0] = 0;
        break;
    }
}
template <class F>
void field_polynomial<F>::monic_polynomialize()
{
}
template <class F>
F field_polynomial<F>::interopolation(const F &x)
{
    F ans;
    for (int i = 0; i < this->dt.size(); i++)
    {
        ans = ans + (this->dt[i] * fast_power(x, i));
    }
    return ans;
}

template <class F>
field_polynomial<F> operator+(const field_polynomial<F> &x, const field_polynomial<F> &y) // polynomial plus O(N)
{
    field_polynomial<F> z;
    if (x.dt.size() >= y.dt.size())
    {
        z.dt.resize(x.dt.size());
        for (int i = 0; i < y.dt.size(); i++)
        {
            z.dt[i] = x.dt[i] + y.dt[i];
        }
        for (int i = y.dt.size(); i < z.dt.size(); i++)
        {
            z.dt[i] = x.dt[i];
        }
    }
    else
    {
        z.dt.resize(y.dt.size());
        for (int i = 0; i < x.dt.size(); i++)
        {
            z.dt[i] = x.dt[i] + y.dt[i];
        }
        for (int i = x.dt.size(); i < z.dt.size(); i++)
        {
            z.dt[i] = y.dt[i];
        }
    }
    F zero;
    for (int i = z.dt.size() - 1; i >= 0; i--)
    {
        if (!(z.dt[i] == zero))
        {
            z.dt.resize(i + 1);
            break;
        }
        if (i == 0)
        {
            z.dt.resize(i + 1);
            break;
        }
    }
    return z;
}
template <class F>
field_polynomial<F> operator-(const field_polynomial<F> &x, const field_polynomial<F> &y) // polynomial minus O(N)
{
    field_polynomial<F> z = y;
    return x + (-z);
}
template <class F>
field_polynomial<F> operator*(const field_polynomial<F> &x, const field_polynomial<F> &y) // polynomial muti O(N^2)
{
    field_polynomial<F> z;
    z.dt.resize(x.dt.size() - 1 + y.dt.size() - 1 + 1);
    for (int i = 0; i < x.dt.size(); i++)
    {
        for (int j = 0; j < y.dt.size(); j++)
        {
            z.dt[i + j] = z.dt[i + j] + (x.dt[i] * y.dt[j]);
        }
    }
    return z;
}
/*
field_polynomial<complexnumber> operator*(const field_polynomial<complexnumber> &x, const field_polynomial<complexnumber> &y) // polynomial muti O(N^2)
{
    printf("field_polynomial_mutiplicationNOTICE:fft mutiplication\n");
    field_polynomial<complexnumber> z;
    z.dt = list_convolution(x.dt, y.dt);
    return z;
}
*/
template <class F>
field_polynomial<F> operator/(const field_polynomial<F> &x, const field_polynomial<F> &y) // polynomial divi O(N^2)
{
    field_polynomial<F> z;
    field_polynomial<F> xx = x;
    size_t degx = x.dt.size() - 1;
    size_t degy = y.dt.size() - 1;
    size_t degz = degx - degy;
    printf("field_polynomial_divisionNOTICE:dg=%d\n", degz);
    z.dt.resize(FIELD_POLYNOMIAL_MAX(degz + 1, 1));
    F leady = y.dt[degy];
    for (int i = degz; i >= 0; i--)
    {
        z.dt[i] = xx.dt[i + degy] / leady;
        for (int j = degy; j >= 0; j--)
        {
            xx.dt[i + j] = xx.dt[i + j] - (y.dt[j] * z.dt[i]);
        }
    }
    return z;
}
template <class F>
field_polynomial<F> operator%(const field_polynomial<F> &x, const field_polynomial<F> &y) // polynomial modu O(N^2)
{
    field_polynomial<F> z;
    field_polynomial<F> xx = x;
    size_t degx = x.dt.size() - 1;
    size_t degy = y.dt.size() - 1;
    size_t degz = degx - degy;
    z.dt.resize(degz + 1);
    F leady = y.dt[degy];
    for (int i = degz; i >= 0; i--)
    {
        z.dt[i] = xx.dt[i + degy] / leady;
        for (int j = degy; j >= 0; j--)
        {
            xx.dt[i + j] = xx.dt[i + j] - (y.dt[j] * z.dt[i]);
        }
    }
    for (int i = degx; i >= 0; i--)
    {
        if (!(xx.dt[i] == 0))
        {
            xx.dt.resize(i + 1);
            break;
        }
        if (i == 0)
        {
            xx.dt.resize(i + 1);
            break;
        }
    }
    return xx;
}
template <class F>
bool operator==(const field_polynomial<F> &x, const field_polynomial<F> &y) // polynomial equal O(N)
{
    if (x.dt.size() != y.dt.size())
    {
        return 0;
    }
    for (int i = 0; i < x.dt.size(); i++)
    {
        if (!(x.dt[i] == y.dt[i]))
        {
            return 0;
        }
    }
    return 1;
}
template <class F>
field_polynomial<F> factor_by_Shie(const field_polynomial<F> &f, const field_polynomial<F> &h)
{
    /*
    field_polynomial<F> r, g, rq, rp, X;
    field_polynomial<F> hh = h;
    hh.print(1);
    double dr;
    double ds;
    double dp = 1;
    double dq = 1;
    double drdq;
    double dsdq;
    double drdp;
    double dsdp;
    X.ctf.resize(2);
    X.ctf[1] = 1;
    X.ctf[0] = 0;
    while (Abs(dp, 0) > Eps || Abs(dq, 0) > Eps)
    {
        r = f % hh;
        g = f / hh;
        // printf("r=");
        // r.print(1);
        // printf("\n");
        // printf("g=");
        // g.print(1);
        // printf("\n");
        dr = -r.ctf[1];
        ds = -r.ctf[0];
        rp = (X * g) % hh;
        // printf("rp=");
        // rp.print(1);
        // printf("\n");
        drdp = -rp.ctf[1];
        dsdp = -rp.ctf[0];
        rq = g % hh;
        // printf("rq=");
        // rq.print(1);
        // printf("\n");
        drdq = -rq.ctf[1];
        dsdq = -rq.ctf[0];
        if (Abs((drdp * dsdq - drdq * dsdp), 0) < Eps)
        {
            break;
        }
        dq = (drdp * ds - dr * dsdp) / (drdp * dsdq - drdq * dsdp);
        dp = (dr * dsdq - drdq * ds) / (drdp * dsdq - drdq * dsdp);
        // printf("dp=%lf\ndq=%lf\n", dp, dq);
        hh.ctf[1] += dp;
        hh.ctf[0] += dq;
        // printf("hh=");
        // hh.print(1);
        // printf("\n");
    }
    return hh;
    */
}
template <class F>
field_polynomial<F> derive_polynomial(const field_polynomial<F> &P)
{
    field_polynomial<F> tmp;
    tmp.dt.resize(FIELD_POLYNOMIAL_MAX(P.dt.size() - 1, 1));
    tmp.dt[0] = 0;
    for (int i = 1; i < P.dt.size(); i++)
    {
        tmp.dt[i - 1] = fast_addition(P.dt[i], i);
    }
    return tmp;
}

std::vector<complexnumber> factorization(const field_polynomial<complexnumber> &P)
{
    std::vector<complexnumber> ans;
    ans.resize(0);
    if ((long long)(P.dt.size()) == 1)
    {
        return ans;
    }
    if ((long long)(P.dt.size()) == 2)
    {
        complexnumber a = P.dt[1];
        complexnumber b = P.dt[0];
        ans.push_back(-b / a);
        return ans;
    }
    if ((long long)(P.dt.size()) == 3)
    {
        complexnumber c_2(2, 0);
        complexnumber c_4(4, 0);
        complexnumber c_1_2(0.5, 0);
        complexnumber a = P.dt[2];
        complexnumber b = P.dt[1];
        complexnumber c = P.dt[0];
        complexnumber delta = (b * b) - (c_4 * a * c);
        ans.push_back((-b + (delta ^ c_1_2)) / (c_2 * a));
        ans.push_back((-b - (delta ^ c_1_2)) / (c_2 * a));
        return ans;
    }
    long long l = -1;
    complexnumber zero;
    for (int i = 0; i < P.dt.size(); i++)
    {
        if (!(P.dt[i] == zero))
        {
            l = i;
            break;
        }
    }
    if (l == -1)
    {
        return ans;
    }
    printf("field_polynomial_factoriazationNOTICE:l=%d\n", l);
    field_polynomial<complexnumber> dP, Pp, Q, h;
    Pp.dt.resize(P.dt.size() - l);
    for (int i = 0; i < Pp.dt.size(); i++)
    {
        Pp.dt[i] = P.dt[i + l];
    }
    dP = derive_polynomial(Pp);
    complexnumber r, val;

    val = Pp.interopolation(r);
    /*
    printf("Pp=");
    Pp.print();
    printf("\n");
    printf("dP=");
    dP.print();
    printf("\n");
    printf("r=");
    r.print();
    printf("\n");
    printf("val=");
    val.print();
    printf("\n");
    */
    while (!(val == zero))
    {
        // printf("r=");
        // r.print();
        // printf("\n");
        r = r - (Pp.interopolation(r) / dP.interopolation(r));
        val = Pp.interopolation(r);
    }
    h.dt.resize(2);
    h.dt[0] = -r;
    h.dt[1] = 1;
    printf("dominator=h=");
    h.print();
    printf("\n");
    Q = Pp / h;
    ans = factorization(Q);
    ans.push_back(r);
    for (int i = 1; i <= l; i++)
    {
        ans.push_back(zero);
    }
    return ans;
}

#endif
