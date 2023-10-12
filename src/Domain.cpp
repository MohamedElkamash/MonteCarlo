#include "Domain.h"

#include "Initialization.h"
#include "Sampling.h"

//Member Attributes

Domain::Domain(InputParameters & parameters)
{ initialization::domain(parameters, _materials, _cells, _surfaces); }

std::vector<Cell> Domain::cells()
{ return _cells; }

std::vector<double> Domain::surfaces()
{ return _surfaces; }

std::vector<Material> Domain::materials()
{ return _materials; }

int Domain::cellCount()
{ return _cells.size(); }

double Domain::xMin()
{ return _cells[0].xLeft(); }

double Domain::xMax()
{ return _cells[cellCount() - 1].xRight(); }

double Domain::domainWidth()
{ return xMax() - xMin(); }

double Domain::cellWidth(int id)
{ return _cells[id].cellWidth(); } 

int Domain::materialCount()
{ return _materials.size(); }

std::vector<double> Domain::binsWidthVector()
{
    std::vector<double> bins_width;
    int bins = cellCount();
    for (int i = 0; i < bins; ++i)
        bins_width.push_back(cellWidth(i));
    
    return bins_width;
}
