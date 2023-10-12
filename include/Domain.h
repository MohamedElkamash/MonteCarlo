#pragma once

#include "InputParameters.h"
#include "Material.h"
#include "Cell.h"
#include "Neutron.h"
#include "Constants.h"

#include <string>
#include <vector>

class Domain
{
    public:

    //constructor
    Domain(InputParameters & parameters);

    //returns a vector of the cells in the domain
    std::vector<Cell> cells();

    //returns vector of surfaces positions
    std::vector<double> surfaces();

    //returns a map of the materials in the domain
    std::vector<Material> materials();

    //returns number of cells in the domain
    int cellCount();

    //returns the x coordinate of the left boundary of the domain
    double xMin();

    //returns the x coordinate of the right boundary of the domain
    double xMax();

    //returns domain width
    double domainWidth();

    //returns cell width
    double cellWidth(int id);

    //returns number of materials in the domain
    int materialCount();


    private:

    //carrying cells information
    std::vector<Cell> _cells;

    //carrying surfaces positions
    std::vector<double> _surfaces;

    //carrying materials information
    std::vector<Material> _materials;
};