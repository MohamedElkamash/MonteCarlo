#include "Sampling.h"

#include <cmath>

double sampling::x(double x_min, double x_max)
{ return randomNumber() * (x_max - x_min) + x_min; }

double sampling::mu()
{ return 2 * randomNumber() - 1; }



//int sampling::neutron_number()
//{return 0;}