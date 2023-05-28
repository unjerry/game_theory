#ifndef COMPLEXNUMBER_H
#define COMPLEXNUMBER_H

#include <stdio.h>
#include <math.h>

#define COMPLEXNUMBER_PI acos(-1)

class complexnumber
{
public:
    double Re;
    double Im;
    double r;     //[0,+infinity)
    double theta; //(-PI,PI]
    complexnumber(const long double x = 0, const long double y = 0, int opt = 0);
    void print(int opt = 0);
    void fprint(FILE *f, int opt = 0);
    int scan(int opt = 0);
    int fscan(FILE *f, int opt = 0);
    void operator=(const size_t &y);
    complexnumber operator-();
    complexnumber operator!();
};
complexnumber operator+(const complexnumber &a, const complexnumber &b);
complexnumber operator-(const complexnumber &a, const complexnumber &b);
complexnumber operator*(const complexnumber &a, const complexnumber &b);
complexnumber operator/(const complexnumber &a, const complexnumber &b);
complexnumber operator^(const complexnumber &a, const complexnumber &b);
bool operator==(const complexnumber &a, const complexnumber &b);
complexnumber generate_primitive_unit_root(const size_t &degree);
#endif
