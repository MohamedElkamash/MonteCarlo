#pragma once

#include "Cell.h"
#include "Domain.h"
#include <vector>

class Neutron
{
    public:

    //constructor
    Neutron(double x, double mu, Cell cell, const Domain & domain);

    //returns the neutron current x-coordinate
    double x();

    //returns the current cosine of the polar angle of the neutron relative to the x-axis
    double mu();

    //returns the current cell of the neutron
    Cell cell();

    //checks direction of travel
    bool isMovingToRight();

    //returns position of the nearst surface in the direction of travel
    double xNearestSurface();

    //returns distance to nearst surface
    double distanceToNearstSurface();

    //returns distance to next collision
    double xNextCollision();

    //checks if the neutron will interact before reach the surface
    bool willInteract();

    //updates the neutron x-coordinate
    void xUpdate();

    //checks if the neutron is absorbed
    bool isAbsorbed();

    //updates the neutron cosine of polar angle
    void muUpdate();

    //checks if the neutron leaked outside the system
    bool isLeaked();

    //simulate neutron
    void simulate();
    
    private:

    //x-coordinate of the neutron
    double _x;

    //cosine the polar angle of the neutron relative to the x-axis
    double _mu;

    //the current cell of the neutron
    Cell _cell;

    //Domain
    Domain _domain;
};