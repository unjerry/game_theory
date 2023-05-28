#ifndef ARTIFICIAL_NEURAL_NETWORK
#define ARTIFICIAL_NEURAL_NETWORK

#include <vector>
#include <stdio.h>
#include <string>
#include <math.h>

#include "complexnumber.h"
#include "field_matrix.h"

class artificial_neural_network
{
public:
    long long layer_depth, knowledge_set_size;
    std::vector<field_matrix<complexnumber>> weight, bias, activation, preactivation;
    std::vector<field_matrix<complexnumber>> knowledge_input_set, knowledge_output_set;
    std::vector<field_matrix<complexnumber>> del_weight, del_bias;

    artificial_neural_network(long long layer = 0);
    void resize_brain(long long layer);
    void resize_knowledge(long long layer);
    int fscan_knowledge(const char *name);
    int fscan_brain(const char *name);
    void fprint_brain(const char *name);

    field_matrix<complexnumber> forward_propagation(field_matrix<complexnumber> x);
    complexnumber back_propagation();
    complexnumber back_propagation_chop(long long start, long long len);

    field_matrix<complexnumber> nonlinear_function(field_matrix<complexnumber> x);
    field_matrix<complexnumber> del_nonlinear_function(field_matrix<complexnumber> x);

    void self_realer();
};

#endif
