#include "InputParameters.h"
#include "Domain.h"
#include "Simulator.h"
#include "Tallies.h"

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

    //Construct Tallies
    Tallies tallies;

    //Initialize the simulator
    Simulator simulator(domain, tallies);

    //Populate the neutron bank with neutrons of cycle zero
    simulator.generateCycleZero();

    //start the neutron simulation 
    simulator.run();

/*
    std::queue<Neutron> neutron_bank = simulator.neutronBank();

    std::cout << neutron_bank.size() << std::endl;

    while(!neutron_bank.empty())
    {
        Neutron neutron = neutron_bank.front();
        //std::cout << neutron.id() << std::endl;
        //std::cout << "x = " << neutron.x() << "     mu = " << neutron.mu() << std::endl;
        neutron_bank.pop();
    } 
*/
/*
    std::cout << tallies.fissionNeutrons().size() << std::endl;

    int cell_count = domain.cellCount();
    std::cout << neutron_bank.size() << std::endl;
    for (int i = 0; i < cell_count; ++i)
    {
        std::cout << tallies.fissionNeutrons()[i] << std::endl;
    }
*/  






}