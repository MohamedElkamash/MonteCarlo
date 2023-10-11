#pragma once

#include <vector>

class Tallies
{
    public:

    //constructor
    Tallies();

    //returns the actual number of fission neutrons in a cycle
    std::vector<int> fissionNeutrons();

    //returns fission neutrons distribution over all cycles
    std::vector<std::vector<int>> normalizedFissionNeutrons();

    //returns flux distribution over active cycles
    std::vector<std::vector<double>> flux();

    //returns k_eff over active cycles
    std::vector<double> kEff();

    //sets the dimensions of the tallies;
    void dimensions(int inactive_cycles, int active_cycles, int bins);

    //increment number of fission neutrons in a bin
    void incrementFissionNeutrons(int bin);

    //fill normalized fission neutrons
    void fillNormalizedFissionNeutrons(int i_inactive_cycle, int bins);

    private:

    //actual number of fission neutrons in one cycle
    std::vector<int> _fission_neutrons;

    //normalized fission neutrons distribution over all cycles
    std::vector<std::vector<int>> _normalized_fission_neutrons;

    //flux distribution over active cycles
    std::vector<std::vector<double>> _flux;

    //k_eff over active cycles
    std::vector<double> _k_eff;
};