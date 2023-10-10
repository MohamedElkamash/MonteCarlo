#pragma once

#include "Cell.h"

class Neutron
{
    public:

    //constructor
    Neutron(int id, double x, double mu);

    //returns the id of the neutron
    int id();

    //returns the neutron current x-coordinate
    double x();

    //returns the current cosine of the polar angle of the neutron relative to the x-axis
    double mu();

    //updates the neutron x-coordinate
    void updateX(double x);

    //updates the neutron cosine polar angle
    void updateMu(double mu);

    //checks if neutron is moving in the positive direction
    bool isDirectionPositive();
    
    private:

    //neutron id
    int _id;

    //x-coordinate of the neutron
    double _x;

    //cosine the polar angle of the neutron relative to the x-axis
    double _mu;
};