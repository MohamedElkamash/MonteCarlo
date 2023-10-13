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
    dashLine();  
    _file << "\n\n";

    //print flux
    tableTitle("Flux");
    _file << std::left
    << std::setw(15) << "Active Cycle";
    for (int i = 0; i < ACTIVE_CYCLES; ++i)
    {
        if (i == 0)
        {
            for (int j = 0; j < _bins; ++j)
                _file << std::setw(4) << "bin" << std::setw(7) << j+1;
            _file << '\n';
            dashLine();
        }
        
        _file << '\n' << std::setw(15) << i+1;
        for (int j = 0; j < _bins; ++j)
        {
             _file << std::setw(11) << std::scientific << std::setprecision(2) 
                   << _tallies.flux()[i][j];
        }
    }
        _file << '\n';
        dashLine();
        _file << std::setw(15) << "average";
        for (int j = 0; j < _bins; ++j)
        {
             _file << std::setw(11) << std::scientific << std::setprecision(2) 
                   << _tallies.averageFlux()[j];
        }
        _file << '\n';
        dashLine();

    _file << "\n\n";

    //print criticality
    tableTitle("Criticality");
    _file << std::left
    << std::setw(21) << "Active Cycle" 
    << std::setw(21) << "k_eff"
    << std::setw(21) << "rel_diff_k_eff"
    << std::setw(21) << "k_eff_cumulative"
    << std::setw(21) << "rel_diff_k_cumulative" 
    << '\n';
    dashLine();
    for (int i = 0; i < ACTIVE_CYCLES; ++i)
    {
        _file
        << std::setw(21) << i+1
        << std::setw(21) << std::fixed      << std::setprecision(5) << _tallies.kEff()[i]
        << std::setw(21) << std::scientific << std::setprecision(2) << _tallies.relativeKeff()[i]
        << std::setw(21) << std::fixed      << std::setprecision(5) << _tallies.kEffCumulative()[i]
        << std::setw(21) << std::scientific << std::setprecision(5) << _tallies.relativeKeffCumulative()[i] 
        << '\n';
    }
    dashLine();
    
    //print flux in csv file
    csv();
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

void Finalizer::csv()
{
    std::vector<std::vector<double>> flux = _tallies.flux();
    std::vector<std::vector<double>> flux_transpose;
    std::vector<std::vector<long int>> normalized_fission_source = _tallies.normalizedFissionNeutrons();
    std::vector<std::vector<double>> fission_transpose;
    flux_transpose.resize(_bins, std::vector<double>(ACTIVE_CYCLES, 0));
    fission_transpose.resize(_bins, std::vector<double>(ACTIVE_CYCLES + INACTIVE_CYCLES, 0));
    double n = static_cast<double>(NEUTRONS_PER_CYCLE);
    int cycles = ACTIVE_CYCLES + INACTIVE_CYCLES;

    for (int i = 0; i < _bins; ++i)
        for(int j = 0; j < ACTIVE_CYCLES; ++j)
          flux_transpose[i][j] = flux[j][i];

    for (int i = 0; i < _bins; ++i)
        for(int j = 0; j < cycles; ++j)
            fission_transpose[i][j] = normalized_fission_source[j][i] / n;
 

    std::ofstream out("results.csv");
    out << "normalized_fission_source_neutrons" << '\n' << "y axis is bin number\n";
    for (int i = 0; i < cycles; ++i)
        out << "cycle " << i+1 << ',';
    out << '\n';

    for (auto& row : fission_transpose) 
    {
        for (auto col : row)
            out << col <<',';
        out << '\n';
    }

    out << "\n\n";

    out << "flux" << '\n' << "y axis is bin number\n";
    for (int i = 0; i < ACTIVE_CYCLES; ++i)
        out << "Active Cycle " << i+1 << ',';
    out << '\n';
    for (auto& row : flux_transpose) 
    {
        for (auto col : row)
            out << col <<',';
        out << '\n';
    }
    out.close();
}