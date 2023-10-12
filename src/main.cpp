#include "InputParameters.h"
#include "Domain.h"
#include "Simulator.h"
#include "Tallies.h"

#include <iomanip>
#include <iostream>
#include <fstream>
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


    

/*

/*
    results << tallies.fissionNeutrons().size() << std::endl;

    int cell_count = domain.cellCount();
    results << neutron_bank.size() << std::endl;
    for (int i = 0; i < cell_count; ++i)
    {
        results << tallies.fissionNeutrons()[i] << std::endl;
    }
*/  

/*     std::vector<std::vector<int>> matrix = tallies.normalizedFissionNeutrons();
    std::ofstream results("results.csv");

    int bins = domain.cellCount(); */

/*     results << "normalized fission neutrons" << '\n';
    for (int i = 0; i < INACTIVE_CYCLES; ++i)
    {
        results << "cycle: " << i << std::endl;
        for (int j = 0; j < bins; ++j)
        {
            results  << tallies.normalizedFissionNeutrons()[i][j] << '\n';
        }
        results << ',';
    } */

/* for (auto & row : matrix) {
  for (auto col : row)
    results << col <<',';
  results << '\n';
} */

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