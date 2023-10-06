#pragma once

class Neutron
{
    public:

    //constructor
    Neutron();

    //returns the neutron current x-coordinate
    double x();

    //returns the current cosine of the polar angle of the neutron relative to the x-axis
    double mu();

    //checks direction of travel
    bool isMovingForward();

    //returns distance to nearst surface
    double distanceToNearstSurface();

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
};