#include "zahlen.h"

void ensign(zahlen &a)
{
    if (a.dt[a.dt.size() - 1] == 9 || a.dt[a.dt.size() - 1] == 0)
    {
        return;
    }
    if (-4 <= a.dt[a.dt.size() - 1] - 9 && a.dt[a.dt.size() - 1] - 9 <= 4)
    {
        a.dt.resize(a.dt.size() + 1);
        a.dt[a.dt.size() - 1] = 9;
        return;
    }
    if (-4 <= a.dt[a.dt.size() - 1] && a.dt[a.dt.size() - 1] <= 4)
    {
        a.dt.resize(a.dt.size() + 1);
        a.dt[a.dt.size() - 1] = 0;
        return;
    }
    return;
}
void anihiprechar(zahlen &c)
{
    size_t len = c.dt.size();
    while (len >= 2)
    {
        if ((c.dt[len - 1] == 0 || c.dt[len - 1] == 9) && (c.dt[len - 1] == c.dt[len - 2]))
        {
            len--;
        }
        else
        {
            break;
        }
    }
    c.dt.resize(len);
}
void digit_completetion(const zahlen &b, zahlen &bp)
{
    for (size_t i = 0; i < bp.dt.size(); i++)
    {
        if (i < b.dt.size())
        {
            bp.dt[i] = b.dt[i];
        }
        else
        {
            bp.dt[i] = bp.dt[b.dt.size() - 1];
        }
    }
}

zahlen::zahlen(std::string str)
{
    this->dt.resize(str.length());
    for (size_t i = 0; i < this->dt.size(); i++)
    {
        this->dt[i] = str[this->dt.size() - 1 - i] - '0';
    }
    ensign(*this);
    anihiprechar(*this);
}
void zahlen::print(size_t opt)
{
    std::string tmp;
    tmp.resize(this->dt.size());
    if (this->dt.size() == 0)
    {
        printf("zahlen_warning(print):length==0\n");
    }
    switch (opt)
    {
    case 0:
        for (int i = 0; i < this->dt.size(); i++)
        {
            tmp[i] = this->dt[this->dt.size() - 1 - i] + '0';
        }
        printf("(zahlen)< _%s >", tmp.c_str());
        break;
    case 1:
        if (this->dt[this->dt.size() - 1] >= 5)
        {
            zahlen I("1"), c = ~(*this), b;
            b = c + I;
            // b.print();
            tmp.resize(b.dt.size());
            for (int i = 0; i < b.dt.size(); i++)
            {
                tmp[i] = b.dt[b.dt.size() - 1 - i] + '0';
            }
            printf("(zahlen)< -%s >", tmp.c_str());
        }
        else
        {
            for (int i = 0; i < this->dt.size(); i++)
            {
                tmp[i] = this->dt[this->dt.size() - 1 - i] + '0';
            }
            printf("(zahlen)< +%s >", tmp.c_str());
        }
        break;
    }
}
void zahlen::fprint(FILE *f, size_t opt)
{
    std::string tmp;
    tmp.resize(this->dt.size());
    if (this->dt.size() == 0)
    {
        printf("zahlen_warning(print):length==0\n");
    }
    switch (opt)
    {
    case 0:
        for (int i = 0; i < this->dt.size(); i++)
        {
            tmp[i] = this->dt[this->dt.size() - 1 - i] + '0';
        }
        fprintf(f, "(zahlen)< _%s >", tmp.c_str());
        break;
    case 1:
        if (this->dt[this->dt.size() - 1] >= 5)
        {
            zahlen I("1"), c = ~(*this), b;
            b = c + I;
            tmp.resize(b.dt.size());
            for (int i = 0; i < b.dt.size(); i++)
            {
                tmp[i] = b.dt[b.dt.size() - 1 - i] + '0';
            }
            fprintf(f, "(zahlen)< -%s >", tmp.c_str());
        }
        else
        {
            for (int i = 0; i < this->dt.size(); i++)
            {
                tmp[i] = this->dt[this->dt.size() - 1 - i] + '0';
            }
            fprintf(f, "(zahlen)< +%s >", tmp.c_str());
        }
        break;
    }
}
int zahlen::scan(size_t opt)
{
    int rt = 0;
    char sw;
    std::string tmp;
    scanf("%*[^(]");
    rt = scanf("(zahlen)< %c%s >", &sw, tmp.c_str());
    // printf("%c\n", sw);
    zahlen c(tmp.c_str());
    *this = c;
    if (this->dt.size() == 0)
    {
        printf("zahlen_warning(scan):length==0\n");
    }
    if (sw == '-')
    {
        zahlen I("1");
        *this = ~(*this) + I;
    }
    return rt;
}
int zahlen::fscan(FILE *f, size_t opt)
{
    int rt = 0, len = 0;
    char sw, ch = 0;
    std::string tmp;
    fscanf(f, "%*[^(]");
    rt = fscanf(f, "(zahlen)< %c", &sw);
    while (1)
    {
        tmp.resize(len + 1);
        rt = fscanf(f, "%c", &ch);
        if (ch == ' ')
        {
            break;
        }
        tmp[len++] = ch;
    }
    // printf("%d\n", tmp.size());
    //  printf("%c\n", sw);
    zahlen c(tmp.c_str());
    *this = c;
    if (this->dt.size() == 0)
    {
        printf("zahlen_warning(scan):length==0\n");
    }
    if (sw == '-')
    {
        zahlen I("1");
        *this = ~(*this) + I;
    }
    return rt;
}
void zahlen::operator=(const size_t &y)
{
    if (this->dt.size() == 0)
    {
        printf("zahlen_warning(operator=):length==0\n");
    }
    this->dt.resize(1);
    switch (y)
    {
    case 1:
        this->dt[0] = 1;
        ensign(*this);
        break;
    default:
        this->dt[0] = 0;
        break;
    }
}
/*
void zahlen::operator=(const zahlen &y)
{
    if (this->dt.size() == 0)
    {
        printf("zahlen_warning(operator=):length==0\n");
    }
    this->dt.resize(y.dt.size());
    for (size_t i = 0; i < this->dt.size(); i++)
    {
        this->dt[i] = y.dt[i];
    }
}
*/

zahlen operator~(const zahlen &a)
{
    zahlen c;
    c.dt.resize(a.dt.size());
    for (size_t i = 0; i < a.dt.size(); i++)
    {
        c.dt[i] = 9 - a.dt[i];
    }
    return c;
}
zahlen operator-(const zahlen &a)
{
    zahlen I("1");
    //(~a).print();
    return (~a) + I;
}
zahlen operator+(const zahlen &a, const zahlen &b)
{
    if (a.dt.size() < b.dt.size())
    {
        return b + a;
    }
    zahlen c, bp, ba;
    size_t len;
    c.dt.resize(a.dt.size());
    bp.dt.resize(a.dt.size());
    digit_completetion(b, bp);
    /*
    printf("\n----\n");
    bp.print();
    c.print();
    c.dt[0] = 0;
    printf("\n----\n");
    */
    for (size_t i = 0; i < a.dt.size(); i++)
    {
        if (i < a.dt.size() - 1)
        {
            c.dt[i + 1] = (((a.dt[i]) + (bp.dt[i]) + (c.dt[i])) / 10);
        }
        c.dt[i] = (((a.dt[i]) + (bp.dt[i]) + (c.dt[i])) % 10);
    }
    ensign(c);
    anihiprechar(c);
    return c;
}
/*
zahlen operator*(const zahlen &a, const zahlen &b)
{
    if (a.dt.size() < b.dt.size())
    {
        return b * a;
    }
    zahlen c, ap, bp;
    c.dt.resize(a.dt.size() + b.dt.size() - 1);
    ap.dt.resize(c.dt.size());
    bp.dt.resize(c.dt.size());
    digit_completetion(a, ap);
    digit_completetion(b, bp);

    // printf("\n------\n");
    // c.print();
    // ap.print();
    // bp.print();
    // printf("\n------\n\n");

    for (int i = 0; i < c.dt.size(); i++)
    {
        for (int j = 0; j < c.dt.size() - i; j++)
        {
            if (i + j < c.dt.size() - 1)
            {
                c.dt[i + j + 1] += (c.dt[i + j] + (ap.dt[j] * bp.dt[i])) / 10;
            }
            c.dt[i + j] = (c.dt[i + j] + (ap.dt[j] * bp.dt[i])) % 10;
        }
    }
    anihiprechar(c);
    ensign(c);
    return c;
}
*/
zahlen operator*(const zahlen &a, const zahlen &b)
{
    if (a.dt.size() < b.dt.size())
    {
        return b * a;
    }
    zahlen c, ap, bp;
    c.dt.resize(a.dt.size() + b.dt.size() - 1);
    ap.dt.resize(c.dt.size());
    bp.dt.resize(c.dt.size());
    std::vector<size_t> A, B, K;
    A.resize(c.dt.size());
    B.resize(c.dt.size());
    digit_completetion(a, ap);
    digit_completetion(b, bp);
    for (int i = 0; i < c.dt.size(); i++)
    {
        A[i] = ap.dt[i];
        B[i] = bp.dt[i];
    }
    K = list_convolution(A, B);
    for (int i = 0; i < c.dt.size(); i++)
    {
        c.dt[i] = K[i] % 10;
        K[i + 1] += K[i] / 10;
        // printf("%llu\n", K[i]);
    }
    anihiprechar(c);
    ensign(c);
    return c;
}
std::ostream &operator<<(std::ostream &fo, const zahlen &z)
{
    std::string tmp, ops;
    tmp.resize(z.dt.size());
    ops.resize(z.dt.size() + 20);
    if (z.dt.size() == 0)
    {
        printf("zahlen_warning(print):length==0\n");
    }
    if (z.dt[z.dt.size() - 1] >= 5)
    {
        zahlen I("1"), c = ~z, b;
        b = c + I;
        tmp.resize(b.dt.size());
        for (int i = 0; i < b.dt.size(); i++)
        {
            tmp[i] = b.dt[b.dt.size() - 1 - i] + '0';
        }
        sprintf((char *)ops.c_str(), "(zahlen)< -%s >", tmp.c_str());
    }
    else
    {
        for (int i = 0; i < z.dt.size(); i++)
        {
            tmp[i] = z.dt[z.dt.size() - 1 - i] + '0';
        }
        sprintf((char *)ops.c_str(), "(zahlen)< +%s >", tmp.c_str());
    }
    fo << ops.c_str();
    return fo;
}
std::istream &operator>>(std::istream &fi, zahlen &z)
{
    int len = 0;
    char sw, ch = 0;
    std::string tmp;
    while (ch != '(')
    {
        fi >> ch;
    }
    fi >> tmp;
    // printf("%s\n", tmp.c_str());
    fi >> sw;
    // printf("%c\n", sw);
    //  fscanf((FILE *)fi.cur, "(zahlen)< %c", &sw);
    while (1)
    {
        tmp.resize(len + 1);
        ch = fi.get();
        // rt = fscanf((FILE *)fi.cur, "%c", &ch);
        // printf("%c\n", ch);
        if (ch == ' ')
        {
            break;
        }
        tmp[len++] = ch;
    }
    // printf("%d\n", tmp.size());
    //  printf("%c\n", sw);
    zahlen c(tmp.c_str());
    z = c;
    if (z.dt.size() == 0)
    {
        printf("zahlen_warning(scan):length==0\n");
    }
    if (sw == '-')
    {
        zahlen I("1");
        z = ~z + I;
    }
    /*
     */
    return fi;
}
