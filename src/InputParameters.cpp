#include "InputParameters.h"

#include <string>
#include <vector>
#include <map>

InputParameters::InputParameters() :
_n_cells(2)

{
    //initializing number of bins in each cell

    _n_bins.push_back(2);
    _n_bins.push_back(2);
    
    //initializing regions coordinates
    //first index is the region index
    //second index: '0' = left boundary coordinate, '1'= right boundary coordinate

    _cells_coordinates.push_back({0.0, 0.5});
    _cells_coordinates.push_back({0.5, 1.0});

    //initializing material properties
    //index is the region index

    _cross_sections.push_back({{"scattering_xs", 0.05},
                                     {"absorption_xs", 0.12},
                                     {"nu*fission_xs", 0.15}});

    _cross_sections.push_back({{"scattering_xs", 0.05},
                                     {"absorption_xs", 0.10},
                                     {"nu*fission_xs", 0.12}});
}

double InputParameters::cellCount()
{ return _n_cells; }

double InputParameters::binsCount(int cell_index)
{ return _n_bins[cell_index]; }

std::array<double, n_cell_boundaries> InputParameters::cellCoordinates(int cell_index)
{ return _cells_coordinates[cell_index]; }

std::map<std::string, double> InputParameters::crossSections(int cell_index)
{ return _cross_sections[cell_index]; }