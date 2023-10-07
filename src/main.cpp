#include "InputParameters.h"
#include "Material.h"
#include "Cell.h"
#include "Initialization.h"
#include "Neutron.h"
#include "Sampling.h"

#include <iomanip>
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <map>
#include <random>

const int N_Neutrons_Per_Cycle = 10;
 

int main()
{
    //Read input parameters
    InputParameters parameters;

    //Domain initialization 
    std::vector<Material> materials;
    std::vector<Cell> cells;
    initialization::start(parameters, materials, cells);

    //creating neutron positions of first cycle
    std::vector<double> cycle_0_x;
    std::vector<int> born_cell_index;
    double random_number = 0;
    double x = 0;
    double x_min = cells[0].xLeft();
    double x_max = cells[cells.size()-1].xRight();

    for (int i = 0; i < N_Neutrons_Per_Cycle; ++i)
    {
        x = sampling::x(x_min, x_max);
        cycle_0_x.push_back(x);
        
        for (int j = 0; j < cells.size(); ++j)
        {
            if (x < cells[j].xRight())
            {
                born_cell_index.push_back(j);
                break;
            }    
        }
        //std::cout << cycle_0_x[i] << "     " << born_cell_index[i] << std::endl;
    }

    double mu = 0;

    //creating first cycle neutrons
    for (int i = 0; i < N_Neutrons_Per_Cycle; ++i)
    {
        mu = sampling::mu();
        Neutron neutron(cycle_0_x[i], mu, cells[born_cell_index[i]]);
        std::cout << neutron.mu() << "   " << neutron.distanceToNearstSurface(neutron.xNearestSurface()) << std::endl;
        //std::cout << neutron.x() << "    " << neutron.cell().xLeft() << std::endl;
    
    }   
}  

