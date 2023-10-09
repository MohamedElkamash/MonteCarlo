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

    private:
    
    Domain & _domain;


};

/* class Experiment

{

    public:
        Experiment();

        void Simulate(Domain & domain, int Number_of_cycles);

        Experiment::simulate(Domain & domain, int Number_of_cycles)
        {
            for neutron in neutrons
            distance to next collision //
            distance to next surface
            willcollide

        }






    





} */