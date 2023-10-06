#include "InputParameters.h"
#include "Material.h"
#include "Cell.h"
#include "Initialization.h"

#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <map>


int main()
{
    //Read input parameters
    InputParameters parameters;

    //Materials construction   
    std::vector<Material> materials;
    //initialization::materials(parameters, materials);

    //Cells construction
    //number of main cells
    //int main_cell_count = parameters.mainCellCount();
    //total number of cells in the domain
    int cell_count = initialization::cellCount(parameters);

    //create new cell to material map
    //std::map<int, int> cell_material_map;
    //initialization::cellMaterialMap(parameters, cell_material_map);

    //double cell_width = initialization::cellWidth(parameters);

    std::vector<Cell> cells;
    //initialization::cells(parameters, materials, cells);

    initialization::start(parameters, materials, cells);
}