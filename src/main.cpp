#include "InputParameters.h"
#include "Domain.h"
#include "Neutron.h"
#include "Sampling.h"

#include <iomanip>
#include <iostream>
#include <cmath>
#include <string>
#include <array>
#include <vector>
#include <map>
#include <queue>
#include <random>

const int N_Neutrons_Per_Cycle = 20;
 

int main()
{
    //Read input parameters
    InputParameters parameters;

    //construct Domain
    Domain domain(parameters);

/*     //neutron queue
    std::queue<Neutron> neutrons;
    std::vector<int> neutron_count_per_cell(domain.cellCount(), 0);

    for (int i = 0; i < N_Neutrons_Per_Cycle; ++i)
    {
        //neutron construction
        double x = sampling::x(domain.xMin(), domain.xMax());
        double mu = sampling::mu();
        int cell_index = floor(x / domain.cellWidth());
        Cell cell = domain.cells()[cell_index];
        Neutron neutron(x, mu, cell, domain);
        neutrons.push(neutron);

        //update neutron score
         ++neutron_count_per_cell[cell_index];
    }


    std::cout << neutrons.size() << std::endl;

    while(!neutrons.empty())
    {
        Neutron neutron = neutrons.front();
        std::cout << neutron.x() << "    " << neutron.mu() << std::endl;
        neutron.simulate();
        std::cout << neutron.x() << "    " << neutron.mu() << std::endl;
        neutrons.pop();
    } */

     //std::cout << neutrons.size() << std::endl;

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
    
    }    */
}  

