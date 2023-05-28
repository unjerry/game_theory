#ifndef FAST_FOURIER_TRANSFORM_H
#define FAST_FOURIER_TRANSFORM_H

#include "complexnumber.h"
#include <math.h>
#include <vector>

#define PI acos(-1)

std::vector<complexnumber> fast_fourier_transform_of_power_two(std::vector<complexnumber> P, int opt);
std::vector<complexnumber> fast_fourier_transform(std::vector<complexnumber> P, int opt);
template<class FIELD_WITH_PRIMITIVE_UNIT_ROOT>
std::vector<FIELD_WITH_PRIMITIVE_UNIT_ROOT> fast_fourier_transform_of_power_two(std::vector<FIELD_WITH_PRIMITIVE_UNIT_ROOT> P, int opt);
template<class FIELD_WITH_PRIMITIVE_UNIT_ROOT>
std::vector<FIELD_WITH_PRIMITIVE_UNIT_ROOT> fast_fourier_transform(std::vector<FIELD_WITH_PRIMITIVE_UNIT_ROOT> P, int opt);

#endif
