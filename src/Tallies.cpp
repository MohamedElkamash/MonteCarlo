#include "Tallies.h"
#include "Constants.h"
#include <cmath>
#include <numeric>
#include "RandomNumberGenerator.h"

Tallies::Tallies()
{}

std::vector<long int> Tallies::fissionNeutrons()
{ return _fission_neutrons; }

std::vector<double> Tallies::maxRelativeChangeFission()
{ return _max_relative_change_fission; }

std::vector<std::vector<long int>> Tallies::normalizedFissionNeutrons()
{ return _normalized_fission_neutrons; }

std::vector<double> Tallies::shannonEntropy()
{ return _shannon_entropy; }

std::vector<double> Tallies::kEff()
{ return _k_eff; }

std::vector<double> Tallies::kEffCumulative()
{ return _k_eff_cumulative; }

std::vector<double> Tallies::relativeKeff()
{ return _relative_k_eff; }

std::vector<double> Tallies::trackLength()
{ return _track_length; }

std::vector<std::vector<double>> Tallies::flux()
{return _flux; }


void Tallies::dimensions(int bins)
{
    _fission_neutrons.resize(bins, 0);
    _max_relative_change_fission.resize(INACTIVE_CYCLES + ACTIVE_CYCLES, 0);
    _shannon_entropy.resize(INACTIVE_CYCLES + ACTIVE_CYCLES, 0);
    _normalized_fission_neutrons.resize(INACTIVE_CYCLES + ACTIVE_CYCLES, std::vector<long int>(bins, 0));
    _k_eff.resize(ACTIVE_CYCLES, 0);
    _k_eff_cumulative.resize(ACTIVE_CYCLES, 0);
    _relative_k_eff.resize(ACTIVE_CYCLES, 0);
    _track_length.resize(bins, 0);
    _flux.resize(ACTIVE_CYCLES, std::vector<double>(bins, 0));
}

void Tallies::incrementFissionNeutrons(int bin)
{ ++_fission_neutrons[bin]; }

void Tallies::flushFissionNeutrons()
{
    for (int i = 0; i < _fission_neutrons.size(); ++i)
        _fission_neutrons[i] = 0;
}

void Tallies::calculateMaxRelativeChangeFission()
{
    int cycles = INACTIVE_CYCLES + ACTIVE_CYCLES;
    int bins = _normalized_fission_neutrons[0].size();
    for (int i = 1; i < cycles; ++i)
    {
        std::vector<double> relative_change(bins, 0);
        double max_relative_change = 0;
        for (int j = 0; j < bins; ++j)
        {
            relative_change[j] = fabs(_normalized_fission_neutrons[i][j] -  _normalized_fission_neutrons[i-1][j]) / 
                                      _normalized_fission_neutrons[i-1][j];
            if (max_relative_change < relative_change[j])
                max_relative_change = relative_change[j];
        }
        _max_relative_change_fission[i] = max_relative_change;
    }     
}

/* void Tallies::calculateMaxRelativeChangeFission(std::vector<int> fission_0, std::vector<int> fission_1, int i_cycle)
{
    //carries the relative change in each bin
    std::vector<double> relative_change(fission_0.size(), 0);
    double max_relative_change = 0;
    int bins = fission_0.size();
    for (int i = 0; i < bins; ++i)
    {
        relative_change[i] = static_cast<double>(abs(fission_1[i] - fission_0[i])) / static_cast<double>(fission_0[i]);
        if (max_relative_change < relative_change[i])
            max_relative_change = relative_change[i];
    }
    //fill the tally vector
    _max_relative_change_fission[i_cycle] = max_relative_change;      
} */

void Tallies::fillNormalizedFissionNeutrons(int i_cycle, int bins)
{
    double sum = std::accumulate(_fission_neutrons.begin(), _fission_neutrons.end(), 0);
    //loop over number of bins
    for (int bin = 0; bin < bins; ++bin)
    {
        _normalized_fission_neutrons[i_cycle][bin] = round(_fission_neutrons[bin] / sum * NEUTRONS_PER_CYCLE);
    }
    /*if the total number of neutrons in the normalized vector is different from the original number of neutrons per cycle
      due to rounding, discard neutrons randomly*/
    int sum_normalized = std::accumulate(_normalized_fission_neutrons[i_cycle].begin(), 
                                         _normalized_fission_neutrons[i_cycle].end(), 0);

    int difference = sum_normalized - NEUTRONS_PER_CYCLE;
    
    for (int i = 0; i < abs(difference); ++i)
    {
        int random_bin = round(randomNumber() * bins);
        if (difference > 0)
            --_normalized_fission_neutrons[i_cycle][random_bin];
        else
            ++_normalized_fission_neutrons[i_cycle][random_bin];
    }
}

void Tallies::calculateShannonEntropy(int bins)
{
    int cycles = INACTIVE_CYCLES + ACTIVE_CYCLES;
    for (int i = 0; i < INACTIVE_CYCLES; ++i)
    {
        for(int j = 0; j < bins; ++j)
        {
            double q = static_cast<double>(_normalized_fission_neutrons[i][j]) / static_cast<double>(NEUTRONS_PER_CYCLE);
            _shannon_entropy[i] += - q * log2(q);
        }
    }
}

void Tallies::calculateKeff(std::vector<long int> fission_0, std::vector<long int> fission_1, int i_cycle)
{
    int bins = fission_0.size();
    double sum_0 = std::accumulate(fission_0.begin(), fission_0.end(), 0);
    double sum_1 = std::accumulate(fission_1.begin(), fission_1.end(), 0);
    _k_eff[i_cycle] = sum_1 / sum_0;
} 

void Tallies::calculateRelativeKEff()
{
    int cycles = _k_eff.size();
    for (int i = 1; i < cycles; ++i)
        _relative_k_eff[i] = fabs(_k_eff[i] - _k_eff[i-1]) / _k_eff[i-1]; 
}

std::vector<double> Tallies::relativeKeffCumulative()
{
    std::vector<double> relative_k_eff_cumulative;
    relative_k_eff_cumulative.push_back(0);
    int cycles = _k_eff_cumulative.size();
    for (int i = 1; i < cycles; ++i)
        relative_k_eff_cumulative.push_back(fabs(_k_eff_cumulative[i] - _k_eff_cumulative[i-1]) / _k_eff_cumulative[i-1]); 
    return relative_k_eff_cumulative;
}

void Tallies::calculateKeffCumulative()
{

    for (int i = 0; i < ACTIVE_CYCLES; ++i)
    {
        double sum = 0;
        for (int j = 0; j <= i; ++j)
        {
             sum += _k_eff[j];
        }
        _k_eff_cumulative[i] = sum / (i + 1);
    }
}

void Tallies::updateTrackLength(double l, int bin)
{ _track_length[bin] += l; }

void Tallies::flushTracklength()
{
    for (int i = 0; i < _track_length.size(); ++i)
        _track_length[i] = 0;
}

void Tallies::calculateFlux(int i_cycle, std::vector<double> & bins_width)
{
    int bins = bins_width.size();
    for (int bin = 0; bin < bins; ++bin)
        _flux[i_cycle][bin] = _track_length[bin] / bins_width[bin] / NEUTRONS_PER_CYCLE;
}

std::vector<double> Tallies::averageFlux()
{
    std::vector<double> average_flux;
    int bins = _fission_neutrons.size();
    for (int i = 0; i < bins; ++i)
    {
        double sum = 0;
    
        for (int j = 0; j < ACTIVE_CYCLES; ++j)
        {
            sum += _flux[j][i];
        }
        average_flux.push_back(sum / ACTIVE_CYCLES);
    }
    return average_flux;
}