/*This class carries all the input parameters
The geometery of the problem is divided into cells
Each cell represents a homogeneous material
Each cell is bounded by two surfaces
Each cell is divided into number of bins to tally the flux distribution
The user inputs the parameters of the problem, material properties, number of cells and number of bins*/

#pragma once

#include <string>
#include <array>
#include <vector>
#include <map>

//number of surfaces surrounding each cell is two only because it is 1D
const int n_cell_boundaries = 2;

class InputParameters
{
    public:

    //constructor, will be updated in the future to read data from input file
    InputParameters();

    //returns total number of cells
    int cellCount();

    //returns number of bins in a cell
    int binsPerCellCount(int cell_id);

    //returns number of materials in the problem
    int materialCount();

    //returns coordinates of the surfaces bounding a cell
    std::array<double, n_cell_boundaries> cellCoordinates(int cell_id);

    //returns cross sections of a material
    std::map<std::string, double> crossSections(int material_id);

    //returns a map between cells id and material id
    std::map<int, int> cellMaterialMap();

    private:

    //number of cells in the geometry
    const int _cells_count;

    //number of flux bins in each cell
    std::vector<int> _bins_per_cell_count;

    //number of materials in the problem
    const int _materials_count;

    //carries coordinates of surfaces bounding each region
    //index 0: left surface & index 1: right surface
    std::vector<std::array<double, n_cell_boundaries>> _cells_coordinates;

    //carries cross_sections of each material
    std::vector<std::map<std::string, double>> _cross_sections;

    //maps each cell with its material
    std::map<int, int> _cell_material_map;
};