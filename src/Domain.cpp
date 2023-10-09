#include "Domain.h"

#include "Initialization.h"
#include "Sampling.h"

//Member Attributes

Domain::Domain(InputParameters & parameters)
{ initialization::domain(parameters, _materials, _cells); }

std::vector<Cell> Domain::cells()
{ return _cells; }

std::vector<Material> Domain::materials()
{ return _materials; }

std::queue<Neutron> & Domain::neutrons()
{ return _neutrons; }

//Neutron Domain::neutron()
//{ return _neutrons.front(); }

//std::map<int, int> Domain::neutronToCellMap()
//{ return _neutron_to_cell_map; }

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

int Domain::neutronCellIndex(double x)
{ return floor(x / cellWidth()); }

void Domain::generateCycleZero()
{
    for (int id = 0; id < N_Neutrons_Per_Cycle; ++id)
    {
        double x = sampling::x(xMin(), xMax());
        double mu = sampling::mu();
        Neutron neutron(x, mu, id);
        //_neutron_to_cell_map[id] = neutronCellIndex(x);
        _neutrons.push(neutron);
    }
}

bool Domain::isNeutronMovingToRight()
{ return _neutrons.front().mu() > 0; }

double Domain::xNearestSurface()
{
    double nearest_surface = 0;
    double x = _neutrons.front().x();
    int cell_index = neutronCellIndex(x);

    if (isNeutronMovingToRight())
        nearest_surface = _cells[cell_index].xRight();
    else
        nearest_surface = _cells[cell_index].xLeft();

    return nearest_surface;
} 

double Domain::xNextCollision()
{
    double x = _neutrons.front().x();
    double mu = _neutrons.front().mu();
    int cell_index = neutronCellIndex(x); 
    return x + (- std::log(randomNumber()) / _cells[cell_index].material().totalCrossSection() * mu);
}  

double Domain::xMin()
{ return _cells[0].xLeft(); }

double Domain::xMax()
{ return _cells[_cells.size()-1].xRight(); }
