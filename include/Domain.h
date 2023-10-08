#pragma once

#include "InputParameters.h"
#include "Material.h"
#include "Cell.h"
#include "Neutron.h"
#include "Constants.h"

#include <string>
#include <vector>
#include <map>
#include <queue>

class Domain
{
    public:

    //constructor
    Domain(InputParameters & parameters);

    //returns a vector of the cells in the domain
    std::vector<Cell> cells();

    //returns a map of the materials in the domain
    std::vector<Material> materials();

    //returns the neutron queue
    std::queue<Neutron> & neutrons();

    //returns the first neutron in the queue
    Neutron neutron();

    //returns the neutron to cell map
    //std::map<int, int> neutronToCellMap();

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

    //returns neutron cell index
    int neutronCellIndex(double x);

    //first cycle
    void generateCycleZero();

    //checks neutron direction of travel
    bool isNeutronMovingToRight();

    //returns position of the nearst surface in the direction of travel
    double xNearestSurface();

    //returns distance to next collision
    double xNextCollision();

    //checks if the neutron will interact before reach the surface
    bool willInteract();

    //updates the neutron x-coordinate
    void xUpdate();

    //checks if the neutron is absorbed
    bool isAbsorbed();

    //updates the neutron cosine of polar angle
    void muUpdate();

    //checks if the neutron leaked outside the system
    bool isLeaked();

    private:

    //carrying cells information
    std::vector<Cell> _cells;

    //carrying materials information
    std::vector<Material> _materials;

    //neutron queue
    std::queue<Neutron> _neutrons;

    //neutron cell map
    //std::map<int, int> _neutron_to_cell_map;
};