#include "RandomNumberGenerator.h"

    std::mt19937 generator(1729);
    std::uniform_real_distribution<> distribution(0,1);

double randomNumber()
{ return distribution(generator); }
