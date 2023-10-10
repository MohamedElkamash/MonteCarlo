#include "Sampling.h"
#include "Constants.h"
#include <cmath>

double sampling::x(double x_min, double x_max)
{ return randomNumber() * (x_max - x_min) + x_min; }

double sampling::mu()
{ return 2 * randomNumber() - 1; }

double sampling::phi()
{ return 2 * pi * randomNumber(); }

int sampling::fissionNeutronsCount(double eta)
{
    int fission_neutrons_count = 0;
    double remainder = eta - floor(eta);
    double random_number = randomNumber();
    if (remainder > random_number)
        fission_neutrons_count = ceil(eta);
    else
        fission_neutrons_count = floor(eta);
        
    return fission_neutrons_count; 
}
