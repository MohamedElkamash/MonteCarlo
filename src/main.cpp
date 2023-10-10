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

    //Create problem domain
    Domain domain(parameters);

    //Initialize the simulator
    Simulator simulator(domain);

    //Populate the neutron bank with neutrons of cycle zero
    simulator.generateCycleZero();

/*     while(!neutron_bank.empty())
    {
        Neutron neutron = neutron_bank.front();
        std::cout << neutron.id() << "   " << neutron.x() << "   " << neutron.mu() << std::endl;
        neutron_bank.pop();
    } 
    std::cout << neutron_bank.size() << std::endl; */

    //Start the random walk of the neutrons

    simulator.run();

}