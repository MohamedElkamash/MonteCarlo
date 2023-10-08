#include "Neutron.h"
#include "RandomNumberGenerator.h"
#include <cmath>
#include <iostream>

Neutron::Neutron(double x, double mu, Cell cell, const Domain & domain):
_x(x),
_mu(mu),
_cell(cell),
_domain(domain)
{

}

double Neutron::x()
{ return _x; }

double Neutron::mu()
{ return _mu; }

Cell Neutron::cell()
{ return _cell; }

bool Neutron::isMovingToRight()
{ return _mu > 0; }

double Neutron::xNearestSurface()
{
    double nearest_surface = 0;
    if (isMovingToRight())
        nearest_surface = _cell.xRight();
    else
        nearest_surface = _cell.xLeft();
    
    return nearest_surface;
}

double Neutron::distanceToNearstSurface()
{ return std::abs(_x - xNearestSurface()); }

double Neutron::xNextCollision()
{
    return _x + (- std::log(randomNumber()) / _cell.material().totalCrossSection() * _mu);
} 


/* void Neutron::simulate()
{
    double x_nearest_surface = xNearestSurface();
    std::cout << x_nearest_surface << std::endl;
    double x_next_collision = xNextCollision();
    std::cout << x_next_collision << std::endl;
    bool will_collide = isMovingToRight() && x_nearest_surface > x_next_collision || 
                       !isMovingToRight() && x_nearest_surface < x_next_collision;

    if (will_collide)
    {
        _x = x_next_collision;
        _cell = _domain.cells()[0];
    }

    else
    {
        _x = x_nearest_surface;
    } */

    

//} 