#pragma once

#include "Domain.h"
#include "Neutron.h"
#include "RandomNumberGenerator.h"

#include <queue>

class Simulator
{
    public:
    
    //constructor
    Simulator(Domain & domain);

    //returns the neutron bank
    std::queue<Neutron> neutronBank();

    //returns the unfiltered neutron bank
    std::queue<Neutron> unfilteredNeutronBank();

    //populate the neutron bank with cycle zero neutrons
    void generateCycleZero();

    //starts the simulator
    void run();

    //simulates the random walk of a single neutron
    void randomWalk(Neutron & neutron);

    //returns the current cell index of the neutron
    int neutronCellIndex(Neutron & neutron);

    //returns the current material index of the neutron
    int neutronMaterialIndex(Neutron & neutron);

    //returns distance to next collision
    double xNextCollision(Neutron & neutron);

    //returns position of the nearest surface in the direction of travel
    double xNearestSurface(Neutron & neutron);

    //checks if the first entry of the function is the smaller of the first two entries
    bool isFirstSmaller(double x, double y, double mu);

    //collision routine
    void collide(Neutron & neutron, double x_next_collision, bool & is_absorbed);

    //sample reaction type
    bool isAbsorbed(Neutron & neutron);

    //absorbs the neutron
    void absorb(Neutron & neutron);

    //scatters the neutron
    void scatter(Neutron & neutron);

    //check if reached limits
    bool isLeaked(double x, double mu);

    
    private:
    
    //domain 
    Domain & _domain;

    //neutron queue to be simulated
    std::queue<Neutron> _neutron_bank;

    //unfiltered bank contain neutrons of next cycle before filtration
    //after the unfiltered bank is normalized it will be copied into the main neutron bank
    std::queue<Neutron> _unfiltered_neutron_bank;
};
