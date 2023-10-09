#include "InputParameters.h"
#include "Domain.h"
#include "Simulator.h"

#include <iomanip>
#include <iostream>
#include <cmath>
#include <string>
#include <array>
#include <vector>
#include <map>
#include <queue>
#include <random>


int main()
{
    //Read input parameters
    InputParameters parameters;

    //construct Empty Domain
    Domain domain(parameters);

    //Generate neutron cycle 0
    domain.generateCycleZero();

    //Construct the simulator
    Simulator simulator(domain);

    simulator.run();


     //std::cout << neutronsQueue().size() << std::endl;

/*      for (int i = 0; i < domain.cellCount(); ++i)
     {
        std::cout << neutron_count_per_cell[i] << std::endl;
     }
 */


 /*    //creating neutron positions of first cycle
    std::vector<double> cycle_0_x;
    std::vector<int> born_cell_index;
    double random_number = 0;
    double x = 0;
    double x_min = cells[0].xLeft();
    double x_max = cells[cells.size()-1].xRight();

    for (int i = 0; i < N_neutronsQueue()_Per_Cycle; ++i)
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

    //creating first cycle neutronsQueue()
    for (int i = 0; i < N_neutronsQueue()_Per_Cycle; ++i)
    {
        mu = sampling::mu();
        Neutron neutron(cycle_0_x[i], mu, cells[born_cell_index[i]]);
        std::cout << neutron.mu() << "   " << neutron.distanceToNearstSurface(neutron.xNearestSurface()) << std::endl;
        //std::cout << neutron.x() << "    " << neutron.cell().xLeft() << std::endl;
    
    }    */
}  

