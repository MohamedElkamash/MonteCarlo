#pragma once

#include "Cell.h"
#include <vector>

class Neutron
{
    public:

    //constructor
    Neutron(double x, double mu, int id);

    //returns the neutron current x-coordinate
    double x();

    //returns the current cosine of the polar angle of the neutron relative to the x-axis
    double mu();

    //returns the id of the neutron
    int id();

    /* //checks direction of travel
    bool isMovingToRight();

    //returns position of the nearst surface in the direction of travel
    double xNearestSurface();

    //returns distance to nearst surface
    double distanceToNearstSurface();

    //returns distance to next collision
    double xNextCollision();

    //checks if the neutron will interact before reach the surface
    bool willInteract();
 */
    //updates the neutron x-coordinate
    void xUpdate(double x);

    //checks if the neutron is absorbed
    bool isAbsorbed();

    //updates the neutron cosine of polar angle
    void muUpdate();

    //checks if the neutron leaked outside the system
    bool isLeaked();
    
    private:

    //neutron id
    int _id;

    //x-coordinate of the neutron
    double _x;

    //cosine the polar angle of the neutron relative to the x-axis
    double _mu;
};