#pragma once

#include <vector>

/* Simulates the neutron inside the domain
*/

class Tallies
{
    public:

    //constructor
    Tallies();

    //returns the actual number of fission neutrons in a cycle
    std::vector<long int> fissionNeutrons();

    //returns the max relative change in fission neutrons between two cycles for all cycles
    std::vector<double> maxRelativeChangeFission();

    //returns fission neutrons distribution over all cycles
    std::vector<std::vector<long int>> normalizedFissionNeutrons();

    //returns Shannon entropy
    std::vector<double> shannonEntropy();

    //returns k_eff over active cycles
    std::vector<double> kEff();

    //returns cummulative average value of k
    std::vector<double> kEffCumulative();

    //returns relative change in k eff between two cycles
    std::vector<double> relativeKeff();

    //returns relative change in k eff between two cycles
    std::vector<double> relativeKeffCumulative();

    //returns the track length tally
    std::vector<double> trackLength();

    //returns flux distribution over active cycles
    std::vector<std::vector<double>> flux();

    //sets the dimensions of the tallies;
    void dimensions(int bins);

    //increment number of fission neutrons in a bin
    void incrementFissionNeutrons(int bin);

    //calculates the max relative change in fission neutrons
    void calculateMaxRelativeChangeFission();

    //sets the fission neutron tally to zero
    void flushFissionNeutrons();

    //sets the track length to zero for next cycle
    void flushTracklength();

    //fill normalized fission neutrons
    void fillNormalizedFissionNeutrons(int i_cycle, int bins);

    //calculates Shannon entropy
    void calculateShannonEntropy(int bins);

    //calculates keff for each cycle
    void calculateKeff(std::vector<long int> fission_0, std::vector<long int> fission_1, int i_cycle);

    //calculates k eff cumulative
    void calculateKeffCumulative();

    //calculates relative change in k eff between two successive cycles
    void calculateRelativeKEff();

    //updates the track length sum of a cell
    void updateTrackLength(double l, int bin);

    //calculate flux for every active cycle
    void calculateFlux(int i_cycle, std::vector<double> & bins_width);

    //calculate average flux over all active cycles
    std::vector<double> averageFlux();

    private:

    //actual number of fission neutrons in one cycle
    std::vector<long int> _fission_neutrons;

    //maximum relative change in fission neutrons between two successive cycles 
    std::vector<double> _max_relative_change_fission;

    //normalized fission neutrons distribution over all cycles
    std::vector<std::vector<long int>> _normalized_fission_neutrons;

    //Shannon entropy
    std::vector<double> _shannon_entropy;

    //k_eff over active cycles
    std::vector<double> _k_eff;

    //relative change in k_eff between two successive cycles
    std::vector<double> _relative_k_eff;

    //cumulative average keff
    std::vector<double> _k_eff_cumulative;

    //track length
    std::vector<double> _track_length;

    //flux distribution over active cycles
    std::vector<std::vector<double>> _flux;
};