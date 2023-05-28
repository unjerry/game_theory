#ifndef ZAHLEN_H
#define ZAHLEN_H

#include <stdio.h>
#include <vector>
#include <string>
#include <fstream>
#include "list_convolution.h"

class zahlen
{

public:
    std::vector<char> dt;
    zahlen(std::string str = "0");
    void print(size_t opt = 0);
    void fprint(FILE *f, size_t opt = 0);
    int scan(size_t opt = 0);
    int fscan(FILE *f, size_t opt = 0);
    void operator=(const size_t &y);
    // void operator=(const zahlen &y);
};
zahlen operator~(const zahlen &a);
zahlen operator-(const zahlen &a);
zahlen operator+(const zahlen &a, const zahlen &b);
zahlen operator*(const zahlen &a, const zahlen &b);
std::ostream &operator<<(std::ostream &fo, const zahlen &z);
std::istream &operator>>(std::istream &fi, zahlen &z);

#endif
