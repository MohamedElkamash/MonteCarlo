#include "Finalizer.h"
#include <iomanip>
#include "Constants.h"

Finalizer::Finalizer(std::ofstream & file, Tallies & tallies, int bins):
_file(file),
_tallies(tallies),
_bins(bins)
{}

void Finalizer::run()
{
    //print criticality
    tableTitle("Criticality");
    _file << std::left
    << std::setw(20) << "Active Cycle" 
    << std::setw(20) << "k_eff"
    << std::setw(20) << "rel_diff_k_eff"
    << std::setw(20) << "k_eff_cumulative" 
    << '\n';
    dashLine();
    for (int i = 0; i < ACTIVE_CYCLES; ++i)
    {
        _file
        << std::setw(20) << i+1
        << std::setw(20) << std::fixed      << std::setprecision(5) << _tallies.kEff()[i]
        << std::setw(20) << std::scientific << std::setprecision(2) << _tallies.relativeKeff()[i]
        << std::setw(20) << std::fixed      << std::setprecision(5) << _tallies.kEffCumulative()[i] 
        << '\n';
    }
    dashLine();
}

void Finalizer::dashLine()
{
    _file
    << "-------------------------------------------------------------------------------" << '\n';
}

void Finalizer::tableTitle(std::string title)
{
    dashLine(); 
    dashLine();
    _file << title << '\n';
    dashLine();
    dashLine();
}
