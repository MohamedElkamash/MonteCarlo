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

    //start the neutron simulation 
    simulator.run();

    std::queue<Neutron> unfiltered_bank = simulator.unfilteredNeutronBank();

    std::cout << unfiltered_bank.size() << std::endl;

    while(!unfiltered_bank.empty())
    {
        Neutron neutron = unfiltered_bank.front();
        std::cout << neutron.id() << std::endl;
        std::cout << "x = " << neutron.x() << "     mu = " << neutron.mu() << std::endl;
        unfiltered_bank.pop();
    } 
    
    std::cout << unfiltered_bank.size() << std::endl; 






}