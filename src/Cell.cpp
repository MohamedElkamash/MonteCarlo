#include "Cell.h"

Cell::Cell(double x_left, double x_right, const Material & material) : 
_x_left(x_left),
_x_right(x_right),
_material(material)
{}

double Cell::xLeft()
{ return _x_left; }

double Cell::xRight()
{ return _x_right; }

void Cell::setXLeft(double x_left)
{ _x_left = x_left; }

void Cell::setXRight(double x_right)
{ _x_right = x_right; }

double Cell::cellWidth()
{ return _x_right - _x_left; }

Material Cell::material()
{ return _material; }




