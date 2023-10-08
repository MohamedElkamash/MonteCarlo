#pragma once

#include "Domain.h"

class Simulator
{
    public:
    
    //constructor
    Simulator(Domain & domain);

    void run();

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