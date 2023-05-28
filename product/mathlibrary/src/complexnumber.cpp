#include "complexnumber.h"

complexnumber::complexnumber(const long double x, const long double y, int opt)
{
    switch (opt)
    {
    case 0:
        this->Re = x;
        this->Im = y;
        this->r = sqrt(this->Re * this->Re + this->Im * this->Im);
        this->theta = atan2(this->Im, this->Re);
        break;
    case 1:
        this->r = x;
        this->theta = y;
        this->Re = this->r * cos(this->theta);
        this->Im = this->r * sin(this->theta);
        break;
    }
}
void complexnumber::print(int opt)
{
    switch (opt)
    {
    case 0:
        printf("(%15.6lf+%15.6lfi)", this->Re, this->Im);
        break;
    case 1:
        printf("(%15.6lf*e^i%15.6lf)", this->r, this->theta);
        break;
    }
}
void complexnumber::fprint(FILE *f, int opt)
{
    switch (opt)
    {
    case 0:
        fprintf(f, "(%15.6lf+%15.6lfi)", this->Re, this->Im);
        break;
    case 1:
        fprintf(f, "(%15.6lf*e^i%15.6lf)", this->r, this->theta);
        break;
    case -1:
        fwrite(this, sizeof(*this), 1, f);
        break;
    }
}
int complexnumber::scan(int opt)
{
    int rt;
    switch (opt)
    {
    case 0:
        scanf("%*[^(]");
        rt = scanf("(%lf+%lfi)", &this->Re, &this->Im);
        this->r = sqrt(this->Re * this->Re + this->Im * this->Im);
        this->theta = atan2(this->Im, this->Re);
        break;
    case 1:
        scanf("%*[^(]");
        rt = scanf("(%lf*e^i%lf)", &this->r, &this->theta);
        this->Re = this->r * cos(this->theta);
        this->Im = this->r * sin(this->theta);
        break;
    }
    return rt;
}
int complexnumber::fscan(FILE *f, int opt)
{
    int rt;
    switch (opt)
    {
    case 0:
        fscanf(f, "%*[^(]");
        rt = fscanf(f, "(%lf+%lfi)", &this->Re, &this->Im);
        this->r = sqrt(this->Re * this->Re + this->Im * this->Im);
        this->theta = atan2(this->Im, this->Re);
        break;
    case 1:
        fscanf(f, "%*[^(]");
        rt = fscanf(f, "(%lf*e^i%lf)", &this->r, &this->theta);
        this->Re = this->r * cos(this->theta);
        this->Im = this->r * sin(this->theta);
        break;
    case -1:
        fread(this, sizeof(*this), 1, f);
        break;
    }
    return rt;
}
void complexnumber::operator=(const size_t &y)
{
    switch (y)
    {
    case 1:
        this->Re = 1;
        this->Im = 0;
        this->r = 1;
        this->theta = 0;
        break;

    default:
        this->Re = 0;
        this->Im = 0;
        this->r = 0;
        this->theta = 0;
        break;
    }
}
complexnumber complexnumber::operator-()
{
    return complexnumber(-this->Re, -this->Im);
}
complexnumber complexnumber::operator!()
{
    return complexnumber(1 / this->r, -this->theta, 1);
}

complexnumber operator+(const complexnumber &a, const complexnumber &b)
{
    complexnumber c;
    c.Re = a.Re + b.Re;
    c.Im = a.Im + b.Im;
    c.r = sqrt(c.Re * c.Re + c.Im * c.Im);
    c.theta = atan2(c.Im, c.Re);
    return c;
}
complexnumber operator-(const complexnumber &a, const complexnumber &b)
{
    complexnumber c;
    c.Re = a.Re - b.Re;
    c.Im = a.Im - b.Im;
    c.r = sqrt(c.Re * c.Re + c.Im * c.Im);
    c.theta = atan2(c.Im, c.Re);
    return c;
}
complexnumber operator*(const complexnumber &a, const complexnumber &b)
{
    complexnumber c;
    c.r = a.r * b.r;
    c.theta = a.theta + b.theta;
    c.theta = c.theta - (ceil(c.theta / (2 * COMPLEXNUMBER_PI)) * (2 * COMPLEXNUMBER_PI)) + (2 * COMPLEXNUMBER_PI);
    if (c.theta > COMPLEXNUMBER_PI)
    {
        c.theta = c.theta - (2 * COMPLEXNUMBER_PI);
    }
    c.Re = c.r * cos(c.theta);
    c.Im = c.r * sin(c.theta);
    return c;
}
complexnumber operator/(const complexnumber &a, const complexnumber &b)
{
    complexnumber c;
    c.r = a.r / b.r;
    c.theta = a.theta - b.theta;
    c.theta = c.theta - (ceil(c.theta / (2 * COMPLEXNUMBER_PI)) * (2 * COMPLEXNUMBER_PI)) + (2 * COMPLEXNUMBER_PI);
    if (c.theta > COMPLEXNUMBER_PI)
    {
        c.theta = c.theta - (2 * COMPLEXNUMBER_PI);
    }
    c.Re = c.r * cos(c.theta);
    c.Im = c.r * sin(c.theta);
    return c;
}
complexnumber operator^(const complexnumber &a, const complexnumber &b)
{
    if (a.r == 0)
    {
        complexnumber ans(0, 0, 0);
        return ans;
    }
    complexnumber c(log(a.r), a.theta, 0);
    complexnumber d = b * c;
    complexnumber ans(exp(d.Re), d.Im, 1);
    return ans;
}
bool operator==(const complexnumber &a, const complexnumber &b)
{
    if ((a - b).r < 1e-14)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
complexnumber generate_primitive_unit_root(const size_t &degree)
{
    complexnumber omega(1, (2 * COMPLEXNUMBER_PI) / degree, 1);
    return omega;
}
