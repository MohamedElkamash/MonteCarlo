#include "InputParameters.h"
#include "Domain.h"
#include "Simulator.h"
#include "Tallies.h"
#include "Finalizer.h"

#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
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

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
    std::cout << "duration =  " << duration.count() << " s" << std::endl;

  /*   for (int i = 0; i < bins; ++i)
    {
        std::cout << domain.binsWidthVector()[i] << '\n';
    }  */

   /*      std::vector<std::vector<double>> matrix = tallies.flux();
    //std::ofstream results("results_new.csv");
 
    std::cout << "flux" << '\n';
    for (int i = 0; i < INACTIVE_CYCLES + ACTIVE_CYCLES; ++i)
    {
        std::cout << "cycle: " << i << std::endl;
        for (int j = 0; j < bins; ++j)
        {
            std::cout  << tallies.flux()[i][j] << '\n';
        }
        std::cout << '\n';
    }  


    std::vector<double> k_eff = tallies.kEff();
    std::vector<double> rel_k_eff = tallies.relativeKeff();
    std::vector<double> k_cum = tallies.kEffCumulative();
    int size_k = k_eff.size();
    int size_rel = rel_k_eff.size();
    int size_cum = k_cum.size();


    for (int i = 0; i < size_k; ++i)
    {
        std::cout << k_eff[i] << '\n';
    }

    std::cout << "cum" << '\n';

    for (int i = 0; i < size_k; ++i)
    {
        std::cout << k_cum[i] << '\n';
    }

    std::cout << std::endl;

     for (int i = 0; i < size_rel; ++i)
    {
        std::cout << rel_k_eff[i] << '\n';
    }    


 */

 /*    results << tallies.fissionNeutrons().size() << std::endl;

    int cell_count = domain.cellCount();
    results << neutron_bank.size() << std::endl;
    for (int i = 0; i < cell_count; ++i)
    {
        results << tallies.fissionNeutrons()[i] << std::endl;
    } */
  

/*      std::vector<std::vector<int>> matrix = tallies.normalizedFissionNeutrons();
    std::ofstream results("results_new.csv");

    //int bins = domain.cellCount();  
 
    results << "normalized fission neutrons" << '\n';
    for (int i = 0; i < INACTIVE_CYCLES; ++i)
    {
        results << "cycle: " << i << std::endl;
        for (int j = 0; j < bins; ++j)
        {
            results  << tallies.normalizedFissionNeutrons()[i][j] << '\n';
        }
        results << ',';
    }   */

/*  for (auto & row : matrix) {
  for (auto col : row)
    results << col <<',';
  results << '\n';
}   */

/*     results << "max relative change " << std::endl;
    for (int i = 0; i < INACTIVE_CYCLES - 1; ++i)
    {
        results << tallies.maxRelativeChangeFission()[i] << std::endl;
    }
    results << ',';

    results << '\n';
    tallies.calculateShannonEntropy(domain.cellCount());
    std::vector<double> entropy = tallies.shannonEntropy();

    results << "shannon entropy" << std::endl;
    for (int i = 0; i < INACTIVE_CYCLES; ++i)
    {
        results << entropy[i] << std::endl;
    } 

    results.close(); */







} 