#pragma once

#include "InputParameters.h"
#include "Material.h"
#include "Cell.h"

/* This namespace contains the utility functions to construct the domain using the input parameters
*/

namespace initialization
{
    void domain(InputParameters & parameters, std::vector<Material> & materials, std::vector<Cell> & cells, 
                std::vector<double> & surfaces);

    //fills the materials vector
    void materials(InputParameters & parameters, std::vector<Material> & materials);

    //returns the total number of cells in the domain after expanding each main cell into smaller cells using the bins
    int cellCount(InputParameters & parameters);

    //create cell to material map
    void cellMaterialMap(InputParameters & parameters, std::map<int, int> & cell_material_map);

    //returns the cell width
    //double cellWidth(InputParameters & parameters);

    //fills the cells vector
    void cells(InputParameters & parameters, std::vector<Material> & materials, std::vector<Cell> & cells,
               std::vector<double> & surfaces);
}

