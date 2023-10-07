#pragma once

#include "InputParameters.h"
#include "Material.h"
#include "Cell.h"

#include <string>
#include <vector>
#include <map>

class Domain
{
    public:

    //constructor
    Domain(InputParameters & parameters);

    //returns a vector of the cells in the domain
    std::vector<Cell> cells();

    //returns a map of the materials in the domain
    std::vector<Material> materials();

    //returns x_min of the domain
    double xMin();

    //returns x_max of the domain
    double xMax();

    //returns number of cells in the domain
    int cellCount();

    //returns domain width
    double domainWidth();

    //returns cell width
    double cellWidth();

    //returns number of materials in the domain
    int materialCount();

    private:

    //carrying cells information
    std::vector<Cell> _cells;

    //carrying materials information
    std::vector<Material> _materials;
};