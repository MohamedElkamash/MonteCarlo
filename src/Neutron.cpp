#include "Neutron.h"

#include "RandomNumberGenerator.h"
#include <cmath>

#include <iostream>

Neutron::Neutron(double x, double mu, int id):
_id(id),
_x(x),
_mu(mu)
{}

double Neutron::x()
{ return _x; }

double Neutron::mu()
{ return _mu; }

int Neutron::id()
{ return _id; }

void Neutron::xUpdate(double x)
{ _x = x; }

//bool Neutron::isMovingToRight()
//{ return _mu > 0; }

/*
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


//

    

//}*/