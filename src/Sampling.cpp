#include "Sampling.h"
#include "Constants.h"
#include <cmath>

double sampling::x(double x_min, double x_max)
{ return randomNumber() * (x_max - x_min) + x_min; }

double sampling::mu()
{ return 2 * randomNumber() - 1; }

double sampling::phi()
{ return 2 * pi * randomNumber(); }



//int sampling::neutron_number()
//{return 0;}