#include "Simulator.h"

#include "Constants.h"
#include "Sampling.h"
#include <cmath>
#include <iostream>

Simulator::Simulator(Domain & domain, Tallies & tallies):
_domain(domain),
_tallies(tallies)
{ _tallies.dimensions(_domain.cellCount()); }


std::queue<Neutron> Simulator::neutronBank()
{ return _neutron_bank; }


//std::queue<Neutron> Simulator::unfilteredNeutronBank()
//{ return _unfiltered_neutron_bank; }


void Simulator::generateCycleZero()
{
    for (int id = 0; id < NEUTRONS_PER_CYCLE; ++id)
    {
        double random_x = sampling::x(_domain.xMin(), _domain.xMax());
        double random_mu = sampling::mu();
        Neutron neutron(id, random_x, random_mu);
        int cell = neutronCellIndex(neutron);
        _tallies.incrementFissionNeutrons(cell);
        _neutron_bank.push(neutron);
    }
    _tallies.fillNormalizedFissionNeutrons(0, _domain.cellCount());
}


void Simulator::run()
{
    int neutron_bank_size = _neutron_bank.size();
    int bins = _domain.cellCount();
    
    for (int i = 0; i < INACTIVE_CYCLES - 1; ++i)
    {
        //keep a copy of the current fission neutrons tally before flushing to use it in relative change calculation
        std::vector<int> previous_fission_neutrons = _tallies.fissionNeutrons();


//std::cout << "cycle: " << i << "\n";
/* std::cout << "actual fission neutrons" << '\n';
for (int j = 0; j < bins; ++j)
{
    std::cout  << _tallies.fissionNeutrons()[j] << std::endl;
}
std::cout << '\n'; */ 

        //flush fission neutrons tally to populate with new generation from absorption
        _tallies.flushFissionNeutrons();

        //count number of neutrons simulated in each bin to avoid exceeding normalized number
        std::vector<int> neutrons_simulated_count(bins, 0);

        for (int j = 0; j < neutron_bank_size; ++j)
        {
            Neutron neutron = _neutron_bank.front();
            int bin = neutronCellIndex(neutron);
            ++neutrons_simulated_count[bin];
            //filter neutron if normalized number in the corresponding bin is reached
            if (neutrons_simulated_count[bin] < _tallies.normalizedFissionNeutrons()[i][bin])
                randomWalk(neutron);
            _neutron_bank.pop();
        }   
        _tallies.fillNormalizedFissionNeutrons(i+1, bins);
        _tallies.calculateMaxRelativeChangeFission(previous_fission_neutrons, _tallies.fissionNeutrons(), i);
    }
/*  for (int i = 0; i < INACTIVE_CYCLES - 1; ++i)
 {
    std::cout << _tallies.maxRelativeChangeFission()[i] << std::endl;
 } */      
/*  std::cout << "normalized fission neutrons" << '\n';
for (int j = 0; j < bins; ++j)
{
    std::cout  << _tallies.normalizedFissionNeutrons()[i][j] << std::endl;
}
std::cout << '\n'; 
    } */
}


void Simulator::randomWalk(Neutron & neutron)
{
    bool is_absorbed = false;
    bool is_leaked = false;
    bool will_collide = false;
    bool is_material_constant = true;
    int i_cell = neutronCellIndex(neutron);
    int i_old_material = neutronMaterialIndex(neutron);
    int i_new_material = i_old_material;
    double x_next_collision = xNextCollision(neutron);
    //std::cout << "x next collision: " << x_next_collision << std::endl;

    while(!is_absorbed && !is_leaked)
    {
        //sample new distance to next collision if the neutron is scattered or changed material
        //don't sample new distance to next collision if the neutron enters new cell with the same material
        if (!is_material_constant)
        {
            //std::cout << "material changed" << std::endl;
            x_next_collision = xNextCollision(neutron);
        }
        is_material_constant = false;

        //calculate distance to nearest surface
        double x_nearest_surface = xNearestSurface(neutron);

        //compare distance to next collision and distance to nearest surface
        will_collide = isFirstSmaller(x_next_collision, x_nearest_surface, neutron.mu());
        
        if (will_collide)
            collide(neutron, x_next_collision, is_absorbed);
        else
        {
            //get the material id of the neutron before transporting to the new cell
            i_old_material = neutronMaterialIndex(neutron);
            //transport the neutron to the surface
            neutron.updateX(x_nearest_surface);

            //check if the neutron leaked
            if (isLeaked(neutron.x(), neutron.mu()))
            {
                is_leaked = true;
                //std::cout << "leaked" << std::endl;
            }
            else //cell change
            {
                //transport the neutron inside the cell to avoid boundary problems on the surface
                if(neutron.isDirectionPositive())
                    neutron.updateX(neutron.x() + epilson);
                else
                    neutron.updateX(neutron.x() - epilson);

                //update material index
                i_new_material = neutronMaterialIndex(neutron);
                //if material didn't change update distance to next collision without sampling
                if (i_new_material == i_old_material)
                {
                    is_material_constant = true;
                    //std::cout << "change cell but same material" << std::endl;
                }
            }
        }    
    }
}


int Simulator::neutronCellIndex(Neutron & neutron)
{ return floor(neutron.x() / _domain.cellWidth()); }


int Simulator::neutronMaterialIndex(Neutron & neutron)
{
    int i_cell = neutronCellIndex(neutron);
    return _domain.cells()[i_cell].material().id(); 
}


double Simulator::xNextCollision(Neutron & neutron)
{
    double x = neutron.x();
    double mu = neutron.mu();
    int i = neutronCellIndex(neutron); 
    return x + (- std::log(randomNumber()) / _domain.cells()[i].material().totalXS() * mu);
}


double Simulator::xNearestSurface(Neutron & neutron)
{
    double nearest_surface = 0;
    int i = neutronCellIndex(neutron);

    if (neutron.isDirectionPositive())
        nearest_surface = _domain.cells()[i].xRight();
    else
        nearest_surface = _domain.cells()[i].xLeft();

    return nearest_surface;
} 


bool Simulator::isFirstSmaller(double x, double y, double mu)
{ return x < y && mu > 0 || x > y && mu < 0; }


void Simulator::collide(Neutron & neutron, double x_next_collision, bool & is_absorbed)
{
            //move the neutron to the position of collision
            neutron.updateX(x_next_collision);
            
            //sample type of collision
            if (isAbsorbed(neutron))
            {
                absorb(neutron);
                is_absorbed = true;
            }
            else
            {
                scatter(neutron);
                //std::cout << neutron.mu() << std::endl;
            }
                    
}

bool Simulator::isAbsorbed(Neutron & neutron)
{
    int i_cell = neutronCellIndex(neutron);
    int i_material = _domain.cells()[i_cell].material().id();
    double random_number = randomNumber();
    double absorption_xs = _domain.materials()[i_material].crossSections()["absorption_xs"];
    double total_xs = _domain.materials()[i_material].totalXS();
    double relative_absorption_xs = absorption_xs / total_xs;

    return random_number < relative_absorption_xs;
}

void Simulator::absorb(Neutron & neutron)
{
    //std::cout << "absorbed" << std::endl;
    //get current material id of the neutron
    int id = neutronMaterialIndex(neutron);
    //get cross sections of the material
    double nu_fission_xs = _domain.materials()[id].crossSections()["nu*fission_xs"];
    double absorption_xs = _domain.materials()[id].crossSections()["absorption_xs"];
    //calculate average number of emitted neutrons per absorption
    double eta = nu_fission_xs / absorption_xs;
    //sample number of generated neutrons
    double fission_neutrons_count = sampling::fissionNeutronsCount(eta);
    //std::cout << "fission neutron count: " << fission_neutrons_count << std::endl;
    //position of the new neutrons is the same as the absorbed neutrons
    double x = neutron.x();
    //std::cout << "final x: " << x << std::endl;
    //create fission neutrons and push them in the reserve bank
    for (int i = 0; i < fission_neutrons_count; ++i)
    {
        //isotropic fission
        double random_mu = sampling::mu();
        Neutron neutron(id, x, random_mu);
        _neutron_bank.push(neutron);
        int cell = neutronCellIndex(neutron);
        //tally fission neutrons
        _tallies.incrementFissionNeutrons(cell);
    }
}


void Simulator::scatter(Neutron & neutron)
{
    //std::cout << "scattered" << std::endl;
    //current mu
    double mu = neutron.mu();
    //sample scattering angle
    double mu_0 = sampling::mu();
    //sample azimuthal angle (in radians)
    double phi = sampling::phi();
    double cos_phi = cos(phi);

    //calculate constants of the quadratic equation to solve for new mu
    double a = pow(cos_phi, 2) * (pow(mu, 2) - 1) - 1;
    double b = 2 * mu * mu_0;
    double c = pow(cos_phi, 2) * (1 - pow(mu, 2)) - pow(mu, 2) * pow(mu_0, 2);

    //calculate discriminant
    double d = pow(b, 2) - 4 * a * c;

    //calculate new angle
    //alternate between two roots
    static int i = 0;
    double mu_new = 0;
    
    if (i % 2 == 0)
        mu_new = (-b + sqrt(d)) / (2 * a);
    else
        mu_new = (-b - sqrt(d)) / (2 * a);
    
    ++i;

    //update neutron angle
    neutron.updateMu(mu_new);
}


bool Simulator::isLeaked(double x, double mu)
{ return x >= _domain.xMax() && mu > 0 || x <= _domain.xMin() && mu < 0; }