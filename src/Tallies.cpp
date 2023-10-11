#include "Tallies.h"
#include "Constants.h"
#include <cmath>
#include <numeric>
#include "RandomNumberGenerator.h"

Tallies::Tallies()
{}

std::vector<int> Tallies::fissionNeutrons()
{ return _fission_neutrons; }

std::vector<std::vector<int>> Tallies::normalizedFissionNeutrons()
{ return _normalized_fission_neutrons; }

std::vector<std::vector<double>> Tallies::flux()
{return _flux; }

std::vector<double> Tallies::kEff()
{ return _k_eff; }

void Tallies::dimensions(int inactive_cycles, int active_cycles, int bins)
{
    _fission_neutrons.resize(bins, 0);
    _normalized_fission_neutrons.resize(active_cycles + inactive_cycles, std::vector<int>(bins, 0));
    _flux.resize(active_cycles, std::vector<double>(bins, 0));
    _k_eff.resize(active_cycles - 1, 0);
}

void Tallies::incrementFissionNeutrons(int bin)
{ ++_fission_neutrons[bin]; }

void Tallies::fillNormalizedFissionNeutrons(int i_inactive_cycle, int bins)
{
    double sum = std::accumulate(_fission_neutrons.begin(), _fission_neutrons.end(), 0);
    //loop over number of bins
    for (int bin = 0; bin < bins; ++bin)
    {
        _normalized_fission_neutrons[i_inactive_cycle][bin] = round(_fission_neutrons[bin] / sum * NEUTRONS_PER_CYCLE);
    }
    /*if the total number of neutrons in the normalized vector is different from the original number of neutrons per cycle
      due to rounding, discard neutrons randomly*/
    int sum_normalized = std::accumulate(_normalized_fission_neutrons[i_inactive_cycle].begin(), 
                                         _normalized_fission_neutrons[i_inactive_cycle].end(), 0);

    int difference = sum_normalized - NEUTRONS_PER_CYCLE;
    
    for (int i = 0; i < abs(difference); ++i)
    {
        int random_bin = round(randomNumber() * bins);
        if (difference > 0)
            --_normalized_fission_neutrons[i_inactive_cycle][random_bin];
        else
            ++_normalized_fission_neutrons[i_inactive_cycle][random_bin];
    }
}