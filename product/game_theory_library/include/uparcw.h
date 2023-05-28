#ifndef UPARCW_H
#define UPARCW_H

#include "field_matrix.h"

class uparcw
{
public:
    field_matrix<double> dt = field_matrix<double>(3, 1);
    uparcw();
};

uparcw::uparcw()
{
}

#endif
