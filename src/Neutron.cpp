#include "Neutron.h"

Neutron::Neutron( int id, double x, double mu):
_id(id),
_x(x),
_mu(mu)
{}

int Neutron::id()
{ return _id; }

double Neutron::x()
{ return _x; }

double Neutron::mu()
{ return _mu; }

void Neutron::updateX(double x)
{ _x = x; }

void Neutron::updateMu(double mu)
{ _mu = mu; }

bool Neutron::isDirectionPositive()
{ return _mu > 0; }