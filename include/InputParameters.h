#pragma once

#include <string>
#include <array>
#include <vector>
#include <map>

/*This class carries all the input parameters
The geometery of the problem is divided into cells
Each cell represents a homogeneous material
Each cell is bounded by two surfaces
Each cell is divided into number of bins to tally the flux distribution
The user inputs the parameters of the problem, material properties, number of cells and number of bins
This class will be refined into the future to read the input parameters from a file*/


//number of surfaces surrounding each cell is two only because it is 1D
static const int cell_boundaries_count = 2;

class InputParameters
{
    public:

    //constructor, will be updated in the future to read data from input file
    InputParameters();

    //returns total number of cells
    int mainCellCount();

    //returns number of bins in a cell
    int binsPerMainCellCount(int main_cell_id);

    //returns number of materials in the problem
    int materialCount();

    //returns coordinates of the surfaces bounding a cell
    std::array<double, cell_boundaries_count> cellCoordinates(int cell_id);

    //returns cross sections of a material
    std::map<std::string, double> crossSections(int material_id);

    //returns a map between cells id and material id
    std::map<int, int> mainCellMaterialMap();

    private:

    //number of cells in the geometry
    int _main_cells_count;

    //number of flux bins in each cell
    std::vector<int> _bins_per_main_cell_count;

    //number of materials in the problem
    int _materials_count;

    //carries coordinates of surfaces bounding each region
    //index 0: left surface & index 1: right surface
    std::vector<std::array<double, cell_boundaries_count>> _main_cells_coordinates;

    //carries cross_sections of each material
    std::vector<std::map<std::string, double>> _cross_sections;

    //maps each cell with its material
    //each cell has one material only but each material can have many cells
    std::map<int, int> _main_cell_material_map;
};