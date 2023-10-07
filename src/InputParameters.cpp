//This file is temporarily used as an input file

#include "InputParameters.h"

#include <string>
#include <vector>
#include <map>

InputParameters::InputParameters() :
    
    //Enter the number of cells in the domain
    _main_cells_count(2),

    //Enter the number of materials in the problem
    _materials_count(2)

{
    //Reserving memory
    _bins_per_main_cell_count.reserve(_main_cells_count);
    _cells_coordinates.reserve(_main_cells_count);
    _cross_sections.reserve(_materials_count);

    //Enter the coordinates of the cell boundaries
    //index is the cell id
    //first entry is the left boundary coordinate
    //second entry is the right boundary coordinate
    _cells_coordinates[0] = {0.0, 0.5};
    _cells_coordinates[1] = {0.5, 1.0};

    //Enter the number of bins in each cell
    //index is the cell id
    _bins_per_main_cell_count[0] = 5;
    _bins_per_main_cell_count[1] = 5;

    //Enter cross sections of each material
    //index is the material id
    _cross_sections[0] = {{"scattering_xs", 0.05},
                          {"absorption_xs", 0.12},
                          {"nu*fission_xs", 0.15}};

    _cross_sections[1] = {{"scattering_xs", 0.05},
                          {"absorption_xs", 0.10},
                          {"nu*fission_xs", 0.12}};

    //Enter cell material map
    //First entry is cell id
    //Second entry is the material id
    _main_cell_material_map = {{0,0},
                               {1,1}};
} //End of input file


int InputParameters::mainCellCount()
{ return _main_cells_count; }

int InputParameters::binsPerMainCellCount(int main_cell_id)
{ return _bins_per_main_cell_count[main_cell_id]; }

int InputParameters::materialCount()
{ return _materials_count; }

std::array<double, cell_boundaries_count> InputParameters::cellCoordinates(int cell_id)
{ return _cells_coordinates[cell_id]; }

std::map<std::string, double> InputParameters::crossSections(int material_id)
{ return _cross_sections[material_id]; }

std::map<int, int> InputParameters::mainCellMaterialMap()
{ return _main_cell_material_map; }