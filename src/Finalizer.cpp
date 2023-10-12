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
    //print fission source
    const int cycles = INACTIVE_CYCLES + ACTIVE_CYCLES;
    tableTitle("Normalized Fission Neutrons Density");
    _file << std::left
    << std::setw(8) << "cycle";

    for (int i = 0; i < cycles; ++i)
    {
        if (i == 0)
        {
            for (int j = 0; j < _bins; ++j)
                _file << std::setw(4) << "bin" << std::setw(7) << j+1;
            _file << std::setw(15) << "max_rel_change" << '\n';
            dashLine();
        }
        _file << std::setw(8) << i+1;
        for (int j = 0; j < _bins; ++j)
            _file << std::setw(11) << std::scientific << std::setprecision(2) 
                  << _tallies.normalizedFissionNeutrons()[i][j] / static_cast<double>(NEUTRONS_PER_CYCLE); 
        _file << std::setw(20) << std::scientific << _tallies.maxRelativeChangeFission()[i] << '\n';
    }  

    _file << "\n\n";

    //print flux
    tableTitle("Flux");
    _file << std::left
    << std::setw(8) << "cycle";
    for (int i = 0; i < cycles; ++i)
    {
        if (i == 0)
        {
            for (int j = 0; j < _bins; ++j)
                _file << std::setw(4) << "bin" << std::setw(7) << j+1;
            _file << '\n';
            dashLine();
        }
        
        _file << '\n' << std::setw(8) << i+1;
        for (int j = 0; j < _bins; ++j)
        {
             _file << std::setw(11) << std::scientific << std::setprecision(2) 
                   << _tallies.flux()[i][j];
        }
 
    } 

    _file << "\n\n";

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
    << "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << '\n';
}

void Finalizer::tableTitle(std::string title)
{
    dashLine(); 
    dashLine();
    _file << title << '\n';
    dashLine();
    dashLine();
}