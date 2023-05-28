#ifndef NUMBER_THEORY_TRANSFORM_H
#define NUMBER_THEORY_TRANSFORM_H

#include <vector>
#include <stdio.h>
#include <math.h>

#define NUMBER_THEORY_TRANSFORM_MODULAR 1004535809 // 4179340454199820289
#define NUMBER_THEORY_TRANSFORM_PRIME_ROOT 3
#define NUMBER_THEORY_TRANSFORM_POWER 21 // 57
#define NUMBER_THEORY_TRANSFORM_BASE 479 // 29

size_t number_theory_transform_inverse(size_t x);
std::vector<size_t> number_theory_transform_of_power_two(std::vector<size_t> P, int opt);
std::vector<size_t> number_theory_transform(std::vector<size_t> P, int opt);

#endif
