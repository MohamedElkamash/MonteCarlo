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
    double cellWidth();

    //returns number of materials in the domain
    int materialCount();




    //checks if the neutron will interact before reach the surface
    //bool willInteract();

    //updates the neutron x-coordinate
    //void xUpdate();

    //checks if the neutron is absorbed
    bool isAbsorbed(int material_id);

    //updates the neutron cosine of polar angle
    void muUpdate();

    //checks if the neutron leaked outside the system
    bool willLeak(double x, double mu);

    private:

    //carrying cells information
    std::vector<Cell> _cells;

    //carrying materials information
    std::vector<Material> _materials;
};