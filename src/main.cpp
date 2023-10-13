#include "InputParameters.h"
#include "Domain.h"
#include "Simulator.h"
#include "Tallies.h"
#include "Finalizer.h"

#include <iostream>
#include <fstream>
#include <chrono>


int main()
{
    //start timer
    auto start = std::chrono::high_resolution_clock::now();

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

    //outputs
    std::ofstream results("results.txt");
    Finalizer finalizer(results, tallies, domain.cellCount());
    finalizer.run();
    results.close();   

    //print runtime
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
    std::cout << '\n' << "duration =  " << duration.count() << " s" << std::endl;
}
 