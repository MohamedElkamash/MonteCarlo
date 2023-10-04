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

    //returns total number of cells in the InputParameters
    double cellCount();

    //returns number of bins in a cell
    double binsCount(int cell_index);

    //returns coordinates of the surfaces bounding a cell
    std::array<double, n_cell_boundaries> cellCoordinates(int cell_index);

    //returns material properties of a cell
    std::map<std::string, double> materialProperties(int cell_index);

    private:

    //number of cells in the geometry
    const int _n_cells;

    //number of flux bins in each cell
    std::vector<int> _n_bins;

    //carries coordinates of surfaces bounding each region
    //index 0: left surface & index 1: right surface
    std::vector<std::array<double, n_cell_boundaries>> _cells_coordinates;

    //carries material properties of each region
    std::vector<std::map<std::string, double>> _materials_properties;
};