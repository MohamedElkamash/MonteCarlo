#pragma once

#include "RandomNumberGenerator.h"

namespace sampling
{
    double x(double x_min, double x_max);
    
    double mu();

    bool isScattered(int material_id);

    int neutron_number();
}


