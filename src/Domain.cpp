#include "Domain.h"

#include "Initialization.h"

//Member Attributes

Domain::Domain(InputParameters & parameters)
{
    initialization::domain(parameters, _materials, _cells);
}


std::vector<Cell> Domain::cells()
{ return _cells; }

std::vector<Material> Domain::materials()
{ return _materials; }

double Domain::xMin()
{ return _cells[0].xLeft(); }

double Domain::xMax()
{ return _cells[_cells.size() - 1].xRight(); }

double Domain::domainWidth()
{ return xMax() - xMin(); }

int Domain::cellCount()
{ return _cells.size(); }

double Domain::cellWidth()
{ return domainWidth() / cellCount(); } 

int Domain::materialCount()
{ return _materials.size(); }