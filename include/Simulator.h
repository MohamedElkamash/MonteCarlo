#pragma once

#include "Domain.h"

class Simulator
{
    public:
    
    //constructor
    Simulator(Domain & domain);

    //starts the simulator
    void run();

    //simulates the neutron
    void simulate(Neutron & neutron);

    //min two positions
    bool isFirstCloser(double x, double y, double mu);

    //check if reached limits
    bool isLeaked(double x, double mu);

    //scatters the neutron
    void scatter(Neutron & neutron);

    //absorbs the neutron
    void absorb(Neutron & neutron);

    //carrys leakage logic
    void leak(Neutron & neutron);

    //collide routine
    void interact(Neutron & neutron, bool & is_absorbed);



    
    private:
    
    Domain & _domain;


};
