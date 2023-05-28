#include "artificial_neural_network.h"

artificial_neural_network::artificial_neural_network(long long layer)
{
    printf("construct_layer=%lld\n", layer);
    this->layer_depth = layer;
    resize_brain(layer);
}
void artificial_neural_network::resize_brain(long long layer)
{
    this->weight.resize(this->layer_depth + 1);
    this->bias.resize(this->layer_depth + 1);
    this->activation.resize(this->layer_depth + 1);
    this->preactivation.resize(this->layer_depth + 1);
    this->del_bias.resize(this->layer_depth + 1);
    this->del_weight.resize(this->layer_depth + 1);
}
void artificial_neural_network::resize_knowledge(long long size)
{
    this->knowledge_input_set.resize(knowledge_set_size + 1);
    this->knowledge_output_set.resize(knowledge_set_size + 1);
}
int artificial_neural_network::fscan_knowledge(const char *name)
{
    int rt;
    std::string string_name(name);
    std::string string_name_addition(".annknowledge");
    FILE *f;
    f = fopen((string_name + string_name_addition).c_str(), "rb");
    rt = fscanf(f, "%lld", &knowledge_set_size);
    printf("knowledge_set_size=%lld\n", knowledge_set_size);
    this->resize_knowledge(knowledge_set_size);
    for (int i = 1; i <= knowledge_set_size; i++)
    {
        knowledge_input_set[i].fscan(f);
        knowledge_output_set[i].fscan(f);
    }
    fclose(f);
    return rt;
}
int artificial_neural_network::fscan_brain(const char *name)
{
    int rt;
    std::string string_name(name);
    std::string string_name_addition(".annbrainin");
    FILE *f;
    f = fopen((string_name + string_name_addition).c_str(), "rb");
    rt = fscanf(f, "%lld", &layer_depth);
    printf("layer_depth=%lld\n", layer_depth);
    this->resize_brain(layer_depth);
    for (int i = 1; i <= layer_depth; i++)
    {
        weight[i].fscan(f);
        bias[i].fscan(f);
    }
    fclose(f);
    return rt;
}
void artificial_neural_network::fprint_brain(const char *name)
{
    std::string string_name(name);
    std::string string_name_addition(".annbrainout");
    FILE *f;
    f = fopen((string_name + string_name_addition).c_str(), "wb");
    fprintf(f, "%lld\n", layer_depth);
    for (int i = 1; i <= layer_depth; i++)
    {
        weight[i].fprint(f);
        bias[i].fprint(f);
    }
    fclose(f);
}

field_matrix<complexnumber> artificial_neural_network::forward_propagation(field_matrix<complexnumber> x)
{
    activation[0] = x;
    // x.print();
    for (int i = 1; i <= layer_depth; i++)
    {
        // printf("fplay=%d\n", i);
        preactivation[i] = weight[i] * activation[i - 1] + bias[i];
        // preactivation[i].print();
        //  preactivation[1].print();
        activation[i] = nonlinear_function(preactivation[i]);
        // activation[i].print();
    }
    return activation[layer_depth];
}
complexnumber artificial_neural_network::back_propagation()
{
    std::vector<field_matrix<complexnumber>> temporary_del_weight, temporary_del_bias;
    complexnumber delta;
    temporary_del_weight.resize(layer_depth + 1);
    temporary_del_bias.resize(layer_depth + 1);
    // printf("bp\n");
    complexnumber step(10, 0);
    complexnumber half(0.5, 0);
    for (int t = 1; t <= knowledge_set_size; t++)
    {

        del_bias[0] = (forward_propagation(knowledge_input_set[t]) - knowledge_output_set[t]);
        // del_bias[0].print();
        // preactivation[layer_depth].print();
        delta = delta + norm(del_bias[0]);
        norm(del_bias[0]).print();
        del_bias[0] = (step * (norm(del_bias[0]))) * del_bias[0];
        del_bias[layer_depth] = matrix_pointwise_multiplication(del_bias[0], del_nonlinear_function(preactivation[layer_depth]));
        // del_bias[layer_depth].print();
        del_weight[layer_depth] = del_bias[layer_depth] * transpose(activation[layer_depth - 1]);
        for (int i = layer_depth - 1; i >= 1; i--)
        {
            del_bias[i] = matrix_pointwise_multiplication(transpose(weight[i + 1]) * del_bias[i + 1], del_nonlinear_function(preactivation[i]));
            del_weight[i] = del_bias[i] * transpose(activation[i - 1]);
            // del_bias[i].print();
        }
        for (int i = 1; i <= layer_depth; i++)
        {
            temporary_del_weight[i] = temporary_del_weight[i] + del_weight[i];
            temporary_del_bias[i] = temporary_del_bias[i] + del_bias[i];
            // temporary_del_weight[i].print();
        }
    }
    // tdW[10].print();
    // printf("%lld\n", knowledge_set_size);
    complexnumber scalor(1.0 / knowledge_set_size, 0);
    for (int i = 1; i <= layer_depth; i++)
    {
        del_weight[i] = scalor * temporary_del_weight[i];
        del_bias[i] = scalor * temporary_del_bias[i];
    }
    delta = scalor * delta;
    // dW[3].print();

    for (int i = 1; i <= layer_depth; i++)
    {
        weight[i] = weight[i] - del_weight[i];
        bias[i] = bias[i] - del_bias[i];
    }
    return delta;
}
complexnumber artificial_neural_network::back_propagation_chop(long long start, long long len)
{
    std::vector<field_matrix<complexnumber>> temporary_del_weight, temporary_del_bias;
    complexnumber delta;
    temporary_del_weight.resize(layer_depth + 1);
    temporary_del_bias.resize(layer_depth + 1);
    // printf("bp\n");
    complexnumber step(10, 0);
    complexnumber half(0.5, 0);
    for (int t = start; t <= start + len - 1; t++)
    {

        del_bias[0] = (forward_propagation(knowledge_input_set[t]) - knowledge_output_set[t]);
        // del_bias[0].print();
        // preactivation[layer_depth].print();
        delta = delta + norm(del_bias[0]);
        // norm(del_bias[0]).print();
        del_bias[0] = (step * norm(del_bias[0])) * del_bias[0];
        del_bias[layer_depth] = matrix_pointwise_multiplication(del_bias[0], del_nonlinear_function(preactivation[layer_depth]));
        // del_bias[layer_depth].print();
        del_weight[layer_depth] = del_bias[layer_depth] * transpose(activation[layer_depth - 1]);
        for (int i = layer_depth - 1; i >= 1; i--)
        {
            del_bias[i] = matrix_pointwise_multiplication(transpose(weight[i + 1]) * del_bias[i + 1], del_nonlinear_function(preactivation[i]));
            del_weight[i] = del_bias[i] * transpose(activation[i - 1]);
            // del_bias[i].print();
        }
        for (int i = 1; i <= layer_depth; i++)
        {
            temporary_del_weight[i] = temporary_del_weight[i] + del_weight[i];
            temporary_del_bias[i] = temporary_del_bias[i] + del_bias[i];
            // temporary_del_weight[i].print();
        }
    }
    // tdW[10].print();
    // printf("%lld\n", knowledge_set_size);
    complexnumber scalor(1.0 / len, 0);
    for (int i = 1; i <= layer_depth; i++)
    {
        del_weight[i] = scalor * temporary_del_weight[i];
        del_bias[i] = scalor * temporary_del_bias[i];
    }
    delta.print();
    delta = scalor * delta;
    // dW[3].print();

    for (int i = 1; i <= layer_depth; i++)
    {
        weight[i] = weight[i] - del_weight[i];
        bias[i] = bias[i] - del_bias[i];
    }
    return delta;
}

complexnumber ReLU(const complexnumber &x)
{
    complexnumber z;
    if (x.Re <= 0)
    {
        complexnumber zero;
        z = zero;
    }
    else
    {
        z = x;
    }
    return z;
}
complexnumber del_ReLU(const complexnumber &x)
{
    complexnumber z;
    if (x.Re <= 0)
    {
        complexnumber zero;
        z = zero;
    }
    else
    {
        complexnumber one;
        one = 1;
        z = one;
    }
    return z;
}
complexnumber Sigmoid(const complexnumber &x)
{
    complexnumber complex_euler_number(exp(1), 0);
    complexnumber one;
    one = 1;
    complexnumber y;
    y = x;
    return one / (one + (complex_euler_number ^ (-y)));
}
complexnumber del_Sigmoid(const complexnumber &x)
{
    complexnumber complex_euler_number(exp(1), 0);
    complexnumber one;
    one = 1;
    complexnumber y, ey;
    y = x;
    ey = complex_euler_number ^ (-y);
    return ey / ((one + ey) * (one + ey));
}

field_matrix<complexnumber> artificial_neural_network::nonlinear_function(field_matrix<complexnumber> x)
{
    field_matrix<complexnumber> z(x.r, x.c);
    for (int i = 1; i <= x.r; i++)
    {
        for (int j = 1; j <= x.c; j++)
        {
            z.dt[i][j] = Sigmoid(x.dt[i][j]);
        }
    }
    return z;
}
field_matrix<complexnumber> artificial_neural_network::del_nonlinear_function(field_matrix<complexnumber> x)
{
    field_matrix<complexnumber> z(x.r, x.c);
    for (int i = 1; i <= x.r; i++)
    {
        for (int j = 1; j <= x.c; j++)
        {
            z.dt[i][j] = del_Sigmoid(x.dt[i][j]);
        }
    }
    return z;
}
void artificial_neural_network::self_realer()
{
    for (int ll = 1; ll <= this->layer_depth; ll++)
    {
        for (int i = 1; i <= this->weight[ll].r; i++)
        {
            for (int j = 1; j <= this->weight[ll].c; j++)
            {
                this->weight[ll].dt[i][j].Im = 0;
            }
        }
        for (int i = 1; i <= this->bias[ll].r; i++)
        {
            this->bias[ll].dt[i][1].Im = 0;
        }
    }
}
