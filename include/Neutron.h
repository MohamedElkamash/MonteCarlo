#pragma once

#include "Cell.h"

class Neutron
{
    public:

    //constructor
    Neutron(double x, double mu, Cell & cell);

    //returns the neutron current x-coordinate
    double x();

    //returns the current cosine of the polar angle of the neutron relative to the x-axis
    double mu();

    //returns the current cell of the neutron
    Cell cell();

    //checks direction of travel
    bool isMovingForward();

    //returns position of the nearst surface in the direction of travel
    double xNearestSurface();

    //returns distance to nearst surface
    double distanceToNearstSurface(double x_nearest_surface);

    //returns distance to next collision
    double distanceToNextCollision();

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
    
    private:

    //x-coordinate of the neutron
    double _x;

    //cosine the polar angle of the neutron relative to the x-axis
    double _mu;

    //current cell
    Cell & _cell;
};