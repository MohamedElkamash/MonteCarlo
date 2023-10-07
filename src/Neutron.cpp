#include "Neutron.h"
#include "RandomNumberGenerator.h"
#include <cmath>

Neutron::Neutron(double x, double mu, Cell & cell):
_x(x),
_mu(mu),
_cell(cell)
{}

double Neutron::x()
{ return _x; }

double Neutron::mu()
{ return _mu; }

Cell Neutron::cell()
{ return _cell; }

bool Neutron::isMovingForward()
{ return _mu > 0; }

double Neutron::xNearestSurface()
{
    double nearest_surface = 0;
    if (_mu > 0)
        nearest_surface = _cell.xRight();
    else
        nearest_surface = _cell.xLeft();
    
    return nearest_surface;
}

double Neutron::distanceToNearstSurface(double x_nearest_surface)
{ return std::abs(_x - x_nearest_surface); }

/*
double Neutron::distanceToNextCollision()
{
    return - std::log(randomNumber()) / _cell.material().crossSections()[]
} 
*/