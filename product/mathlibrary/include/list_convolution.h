#ifndef LIST_CONVOLUTION_H
#define LIST_CONVOLUTION_H

#include "fast_fourier_transform.h"
#include "number_theory_transform.h"
#include <math.h>

std::vector<complexnumber> list_convolution(const std::vector<complexnumber> &a, const std::vector<complexnumber> &b);
std::vector<size_t> list_convolution(const std::vector<size_t> &a, const std::vector<size_t> &b);

#endif
